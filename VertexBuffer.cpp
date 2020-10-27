#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext) :
    _pd3dDevice(pd3dDevice), _pImmediateContext(pImmediateContext), _pVertexBuffer(nullptr), _pMesh(nullptr)
{
}

HRESULT VertexBuffer::Initialise(Mesh* mesh)
{
    HRESULT hr;

    _pMesh = mesh;

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = _pMesh->GetVertices()->GetSize();
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory(&InitData, sizeof(InitData));
    InitData.pSysMem = _pMesh->GetVertices()->GetData();

    hr = _pd3dDevice->CreateBuffer(&bd, &InitData, &_pVertexBuffer);

    if (FAILED(hr))
        return hr;

    return S_OK;
}

void VertexBuffer::Bind()
{
    UINT stride = _pMesh->GetVertices()->GetStride();
    UINT offset = 0;
    _pImmediateContext->IASetVertexBuffers(0, 1, &_pVertexBuffer, &stride, &offset);
}
