#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext):
	_pd3dDevice(pd3dDevice), _pImmediateContext(pImmediateContext), _pIndexBuffer(nullptr)
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
    hr = _pd3dDevice->CreateBuffer(&bd, &InitData, &_pIndexBuffer);

    if (FAILED(hr))
        return hr;

    return S_OK;
}

void IndexBuffer::Bind()
{
    _pImmediateContext->IASetIndexBuffer(_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
}
