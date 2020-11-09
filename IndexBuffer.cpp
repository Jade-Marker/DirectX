#include "IndexBuffer.h"

IndexBuffer::IndexBuffer():
	_pIndexBuffer(nullptr)
{

}

HRESULT IndexBuffer::Initialise(Mesh* mesh)
{
    HRESULT hr;

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));

    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(WORD) * mesh->GetIndexCount();
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory(&InitData, sizeof(InitData));
    InitData.pSysMem = mesh->GetIndices();
    hr = DeviceManager::GetDevice()->CreateBuffer(&bd, &InitData, &_pIndexBuffer);

    if (FAILED(hr))
        return hr;

    return S_OK;
}

void IndexBuffer::Bind()
{
    DeviceManager::GetContext()->IASetIndexBuffer(_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
}
