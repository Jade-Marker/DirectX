#include "IndexBuffer.h"

HRESULT IndexBuffer::Initialise(Mesh* mesh)
{
    HRESULT hr = Buffer::Initialise(sizeof(WORD) * mesh->GetIndexCount(), D3D11_USAGE_DEFAULT, D3D11_BIND_INDEX_BUFFER, 0, 0, 0, mesh->GetIndices());

    if (FAILED(hr))
        return hr;

    return S_OK;
}

void IndexBuffer::Bind(Shader* shader, UINT slot)
{
    DeviceManager::GetContext()->IASetIndexBuffer(_pBuffer, DXGI_FORMAT_R16_UINT, 0);
}
