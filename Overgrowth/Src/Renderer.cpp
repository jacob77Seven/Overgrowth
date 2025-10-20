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
    SheetSpriteSectionIndex = (UINT)m_nNumSprites;
}

void ORenderer::LoadTextureDescriptors(const std::vector<LTextureDesc*>& in_textures)
{
    // Ensure the sprite array has been allocated by calling Initialize() first.
    if (!m_pSprite || m_nNumSprites < in_textures.size() + 5) { // Check against offset
        ABORT("Sprite renderer is not initialized or doesn't have enough space for new textures.");
        return;
    }

    for (size_t j = 0; j < in_textures.size(); ++j) {
        size_t i = j + 5; // hardcoded offset (TODO: Replace with last spriteSheet index)

        if (m_pSprite[i] != nullptr) {
            delete m_pSprite[i];
        }

        // Create LSprite - allocates a tex descript
        m_pSprite[i] = new LSprite(1);

        // Get a reference to the LSprite's descriptor
        LTextureDesc& destDesc = m_pSprite[i]->GetTextureDesc(0);

        // copy from and delete temp descriptor
        destDesc = *in_textures[j];
        delete in_textures[j];
    }
}


void ORenderer::SplitTextureFile(
    const char* filename,
    std::vector<LTextureDesc*>& out_textures,
    int split_cols,
    int split_rows)
{
    wchar_t* wfilename = nullptr;
    MakeWideFileName(filename, wfilename);

    std::ifstream file(filename);
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

    if (sourceDesc.Width % split_cols != 0 || sourceDesc.Height % split_rows != 0)
    {
        ABORT("Texture dimensions are not evenly divisible by split counts.");
    }

    const UINT sub_width = sourceDesc.Width / split_cols;
    const UINT sub_height = sourceDesc.Height / split_rows;

    // bytesPerPixel calculation
    const size_t bytesPerPixel = subresourceData.RowPitch / sourceDesc.Width;

    const size_t source_row_pitch = subresourceData.RowPitch;
    const size_t sub_image_row_pitch = sub_width * bytesPerPixel;

    uint8_t* pSrcData = decodedData.get();

    // Create a smaller GPU resource for each tile and copy data
    for (int y = 0; y < split_rows; ++y)
    {
        for (int x = 0; x < split_cols; ++x)
        {
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
        }
    }

    // Execute all uploads and wait
    // End batch and wait for GPU to finish
    auto finished = resourceUpload.End(m_pDeviceResources->GetCommandQueue());
    finished.wait();
}