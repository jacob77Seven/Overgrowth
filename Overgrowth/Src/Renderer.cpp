#include "Renderer.h"
#include "Helpers.h"
#include "d3dx12.h"
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include "WICTextureLoader.h"
#include "ResourceUploadBatch.h" // For simpler upload


ORenderer::ORenderer(eSpriteMode mode)
    : LSpriteRenderer(mode) {
    //SheetSpriteSectionIndex = 0;
    //ImageFilesSectionNum = 0;
    //SheetSpriteSectionNum = 0;
}


void ORenderer::Draw(const LSpriteDesc3D* sd) {
    UINT SpriteIndex = sd->m_nSpriteIndex; // By default, the SpriteIndex is the m_nSpriteIndex of the sprite descriptor.
    auto it = SheetToFirstIndex.find(sd->m_nSpriteIndex);
    if (it != SheetToFirstIndex.end())
        SpriteIndex = it->second + sd->m_nCurrentFrame;

    LTextureDesc& td = m_pSprite[SpriteIndex]->GetTextureDesc(0);

    const float xscale = sd->m_fXScale * td.m_nWidth;
    const float yscale = sd->m_fYScale * td.m_nHeight;

    const XMVECTORF32 scale = { xscale, yscale, 1.0f };

    const XMVECTORF32 translate = { sd->m_vPos.x, sd->m_vPos.y, sd->m_vPos.z };

    const Quaternion q = Quaternion::CreateFromYawPitchRoll(
        sd->m_fYaw, sd->m_fPitch, sd->m_fRoll);

    const XMMATRIX world = XMMatrixTransformation(
        g_XMZero, Quaternion::Identity, scale, g_XMZero, q, translate);

    m_pSpriteEffect->SetTexture(
        m_pDescriptorHeap->GetGpuHandle(td.m_nResourceDescIndex),
        m_pStates->PointClamp());

    m_pSpriteEffect->SetAlpha(sd->m_fAlpha);

    m_pSpriteEffect->SetWorld(world);
    m_pSpriteEffect->SetView(XMLoadFloat4x4(&m_view));

    m_pSpriteEffect->Apply(m_pCommandList);

    m_pCommandList->IASetVertexBuffers(0, 1, m_pVBufView.get());
    m_pCommandList->IASetIndexBuffer(m_pIBufView.get());
    m_pCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    m_pCommandList->DrawIndexedInstanced(4, 1, 0, 0, 0);
} //Draw

void ORenderer::LoadSpriteSheet(UINT index, const char* name, int sizex, int sizey, int numSprites) {

    if (m_pXmlSettings == nullptr)
        ABORT("Cannot access gamesettings.xml.");

    XMLElement* pSpritesTag = m_pXmlSettings->FirstChildElement("sprites"); //sprites tag

    if (pSpritesTag == nullptr)
        ABORT("Cannot find <sprites> tag in gamesettings.xml");

    std::string filepath = "";
    std::string path(pSpritesTag->Attribute("path")); //get path

    XMLElement* pSpriteTag = pSpritesTag->FirstChildElement("sprite");

    while (pSpriteTag != nullptr && strcmp(name, pSpriteTag->Attribute("name")))
        pSpriteTag = pSpriteTag->NextSiblingElement("sprite");

    if (pSpriteTag == nullptr)
        ABORT("Cannot find <sprite> tag with name \"%s\".\n", name);

    LSprite* pSprite = nullptr;

    if (pSpriteTag->Attribute("file")) { //from single-frame file
        filepath = (std::string)(path + "\\" + pSpriteTag->Attribute("file"));
        const char* extension = pSpriteTag->Attribute("ext");
        //const int frames = std::max(1, pSpriteTag->IntAttribute("frames"));
        //m_mapNameToIndex.insert(std::pair<std::string, UINT>(name, index));
    } //if

    std::vector<LTextureDesc*> out_textures;

    wchar_t* wfilename = nullptr;
    MakeWideFileName(filepath.c_str(), wfilename);

    std::ifstream file(filepath.c_str());
    if (!file) {
        std::cout << "Failed to open file.\n";
    }

    // Decode image into RAM
    // batch for this function's upload tasks
    DirectX::ResourceUploadBatch resourceUpload(m_pD3DDevice);
    resourceUpload.Begin();

    ComPtr<ID3D12Resource> sourceTexture; // This is the full texture on the GPU
    std::unique_ptr<uint8_t[]> decodedData;
    D3D12_SUBRESOURCE_DATA subresourceData;

    HRESULT hr = DirectX::LoadWICTextureFromFile(
        m_pD3DDevice,
        wfilename,
        sourceTexture.ReleaseAndGetAddressOf(),
        decodedData,
        subresourceData);

    if (FAILED(hr))
    {
        ABORTW(L"Couldn't decode WIC texture file \"%s\".", wfilename);
        delete[] wfilename;
    }
    delete[] wfilename;

    const D3D12_RESOURCE_DESC sourceDesc = sourceTexture->GetDesc();

    if (sourceDesc.Width % sizex != 0 || sourceDesc.Height % sizey != 0)
    {
        ABORT("Texture dimensions are not evenly divisible by split counts.");
    }
    int numCols = sourceDesc.Width / sizex;
    int numRows = sourceDesc.Height / sizey;
    const UINT sub_width = sourceDesc.Width / numCols;
    const UINT sub_height = sourceDesc.Height / numRows;

    // bytesPerPixel calculation
    const size_t bytesPerPixel = subresourceData.RowPitch / sourceDesc.Width;

    const size_t source_row_pitch = subresourceData.RowPitch;
    const size_t sub_image_row_pitch = sub_width * bytesPerPixel;

    uint8_t* pSrcData = decodedData.get();
    int importedSoFar = 0;
    // Create a smaller GPU resource for each tile and copy data
    for (int y = 0; y < numRows; ++y)
    {
        for (int x = 0; x < numCols; ++x)
        {
            if (importedSoFar == numSprites)
                break;
            LTextureDesc* tDesc = new LTextureDesc(); // Create temporary descriptor

            D3D12_RESOURCE_DESC tileDesc = sourceDesc;
            tileDesc.Width = sub_width;
            tileDesc.Height = sub_height;

            ComPtr<ID3D12Resource> pTileTexture;
            CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_DEFAULT);
            m_pD3DDevice->CreateCommittedResource(
                &heapProps,
                D3D12_HEAP_FLAG_NONE,
                &tileDesc,
                D3D12_RESOURCE_STATE_COPY_DEST, // Start in copy-destination state
                nullptr,
                IID_PPV_ARGS(&pTileTexture));

            // Create tile upload buffer
            D3D12_SUBRESOURCE_DATA tileSubresourceData = {};
            // buffer is local - waits for resourceUpload.End()
            std::unique_ptr<uint8_t[]> uploadBufferData(new uint8_t[sub_height * sub_image_row_pitch]);

            // Manually copy the pixel data
            for (UINT row = 0; row < sub_height; ++row)
            {
                size_t src_x_offset = x * sub_width;
                size_t src_y_offset = (y * sub_height) + row;
                uint8_t* pSrcRowStart = pSrcData + (src_y_offset * source_row_pitch) + (src_x_offset * bytesPerPixel);

                uint8_t* pDestRowStart = uploadBufferData.get() + (row * sub_image_row_pitch);

                memcpy(pDestRowStart, pSrcRowStart, sub_image_row_pitch);
            }

            tileSubresourceData.pData = uploadBufferData.get();
            tileSubresourceData.RowPitch = sub_image_row_pitch;
            tileSubresourceData.SlicePitch = sub_height * sub_image_row_pitch;

            // Schedule the upload
            // This queues the copy and the resource transition to PIXEL_SHADER_RESOURCE
            resourceUpload.Upload(pTileTexture.Get(), 0, &tileSubresourceData, 1);

            // Store the completed texture resource
            // This function (from LRenderer3D) adds to m_pTexture,
            // creates the SRV, and fills in the tDesc.
            ProcessTexture(pTileTexture, *tDesc);
            out_textures.push_back(tDesc);
            importedSoFar++;
        }
    }

    // Execute all uploads and wait
    // End batch and wait for GPU to finish
    auto finished = resourceUpload.End(m_pDeviceResources->GetCommandQueue());
    finished.wait();

    // Ensure the sprite array has been allocated by calling Initialize() first.
    if (!m_pSprite || m_nNumSprites < out_textures.size() + 5) { // Check against offset
        ABORT("Sprite renderer is not initialized or doesn't have enough space for new textures.");
        return;
    }
    int numTex = out_textures.size();

    for (size_t j = 0; j < out_textures.size(); ++j) {
        size_t i = j + SheetSpriteSectionIndex; // hardcoded offset (TODO: Replace with last spriteSheet index)

        if (m_pSprite[i] != nullptr) {
            delete m_pSprite[i];
        }

        // Create LSprite - allocates a tex descript
        m_pSprite[i] = new LSprite(1);

        // Get a reference to the LSprite's descriptor
        LTextureDesc& destDesc = m_pSprite[i]->GetTextureDesc(0);

        // copy from and delete temp descriptor
        destDesc = *out_textures[j];
        delete out_textures[j];
    }
    SheetToFirstIndex[index] = SheetSpriteSectionIndex; // Link the index of the sprite sheet to the first corresponding sprite index
    SheetSpriteSectionIndex += numTex;
}
