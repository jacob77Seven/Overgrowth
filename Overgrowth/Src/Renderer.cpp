#include "Renderer.h"
#include "Helpers.h"
#include "d3dx12.h"
#include <vector>
#include <memory>
#include "WICTextureLoader.h"
#include "ResourceUploadBatch.h" // For a simpler upload experience

void ORenderer::LoadTextureDescriptors(const std::vector<LTextureDesc*>& in_textures)
{
    // Ensure the sprite array has been allocated by calling Initialize() first.
    // This also assumes the number of textures in the vector is not more than
    // the number of sprites you initialized.
    if (!m_pSprite || m_nNumSprites < in_textures.size()) {
        ABORT("Sprite renderer is not initialized or doesn't have enough space for new textures.");
        return;
    }

    for (size_t i = 0; i < in_textures.size(); ++i) {
        // If a sprite already exists at this index, delete it to prevent a memory leak.
        if (m_pSprite[i] != nullptr) {
            delete m_pSprite[i];
        }
        m_pSprite[i] = new LSprite(1);
        m_pSprite[i]->SetTextureDescPtr(in_textures[i]);

        // Create a new LSprite object using the frame(s).
        // NOTE: This assumes LSprite has a constructor that accepts a std::vector<LTextureDesc>.
        // If it has a different interface, you will need to adjust this line.
        
    }
}



ORenderer::ORenderer(eSpriteMode mode)
    : LSpriteRenderer(mode) {
    SheetSpriteSectionIndex = (UINT)m_nNumSprites;
}

// Assuming LTextureDesc can now hold a single texture resource
// You will likely need a vector of these to manage the split textures.

void ORenderer::SplitTextureFile(
    const char* filename,
    std::vector<LTextureDesc*>& out_textures,
    int split_cols,
    int split_rows)
{
    wchar_t* wfilename = nullptr;
    MakeWideFileName(filename, wfilename);

    // ***************************************************************
    // 1. Decode the entire image into system memory (RAM)
    // ***************************************************************
    DirectX::ResourceUploadBatch resourceUpload(m_pD3DDevice);
    resourceUpload.Begin();

    ComPtr<ID3D12Resource> sourceTexture;
    std::unique_ptr<uint8_t[]> decodedData;
    D3D12_SUBRESOURCE_DATA subresourceData;

    // Use the version of LoadWICTextureFromFile that returns data in memory
    HRESULT hr = DirectX::LoadWICTextureFromFile(
        m_pD3DDevice,
        wfilename,
        sourceTexture.ReleaseAndGetAddressOf(), // This will be the full texture resource
        decodedData,
        subresourceData);

    if (FAILED(hr))
    {
        delete[] wfilename;
        ABORTW(L"Couldn't decode WIC texture file \"%s\".", wfilename);
    }
    delete[] wfilename;

    const D3D12_RESOURCE_DESC sourceDesc = sourceTexture->GetDesc();

    // Ensure the image can be split evenly
    if (sourceDesc.Width % split_cols != 0 || sourceDesc.Height % split_rows != 0)
    {
        ABORT("Texture dimensions are not evenly divisible by split counts.");
    }

    const UINT sub_width = sourceDesc.Width / split_cols;
    const UINT sub_height = sourceDesc.Height / split_rows;
    const size_t bytesPerPixel = sourceDesc.Width/ sourceDesc.Height / 8;

    // The "pitch" is the number of bytes in one row of the image data.
    const size_t source_row_pitch = subresourceData.RowPitch;
    const size_t sub_image_row_pitch = sub_width * bytesPerPixel;

    uint8_t* pSrcData = decodedData.get();

    // ***************************************************************
    // 2. Create a smaller GPU resource for each tile and copy data
    // ***************************************************************
    for (int y = 0; y < split_rows; ++y)
    {
        for (int x = 0; x < split_cols; ++x)
        {
            LTextureDesc *tDesc = new LTextureDesc(); // Your texture descriptor struct

            // Create the destination texture for this tile on the GPU
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

            // Set a debug name for tools like PIX
            // wchar_t debugName[256];
            // swprintf_s(debugName, L"Tile_%d_%d", x, y);
            // pTileTexture->SetName(debugName);

            // Create an upload buffer for this tile
            D3D12_SUBRESOURCE_DATA tileSubresourceData = {};
            std::unique_ptr<uint8_t[]> uploadBufferData(new uint8_t[sub_height * sub_image_row_pitch]);

            // ***************************************************************
            // 3. This is the core "parsing" logic you asked for
            // ***************************************************************
            // Manually copy the pixel data for the current tile from the source buffer
            // to our temporary upload buffer.
            for (UINT row = 0; row < sub_height; ++row)
            {
                // Calculate the starting point in the source data
                size_t src_x_offset = x * sub_width;
                size_t src_y_offset = (y * sub_height) + row;
                uint8_t* pSrcRowStart = pSrcData + (src_y_offset * source_row_pitch) + (src_x_offset * bytesPerPixel);

                // Calculate the destination pointer in our tile's upload buffer
                uint8_t* pDestRowStart = uploadBufferData.get() + (row * sub_image_row_pitch);

                // Copy one row of pixel data for the sub-image
                memcpy(pDestRowStart, pSrcRowStart, sub_image_row_pitch);
            }

            tileSubresourceData.pData = uploadBufferData.get();
            tileSubresourceData.RowPitch = sub_image_row_pitch;
            tileSubresourceData.SlicePitch = sub_height * sub_image_row_pitch;

            // Upload the data for this one tile
            // UpdateSubresources(m_pCommandList, pTileTexture.Get(), resourceUpload, 0, 1, &tileSubresourceData);

            // Transition the tile texture to be readable by shaders
            CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
                pTileTexture.Get(),
                D3D12_RESOURCE_STATE_COPY_DEST,
                D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
            m_pCommandList->ResourceBarrier(1, &barrier);

            // Store the completed texture resource
            ProcessTexture(pTileTexture, *tDesc); // Your function to create SRV, etc.
            out_textures.push_back(tDesc);
        }
    }
}