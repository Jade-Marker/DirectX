#include "VertexBuffer.h"

VertexBuffer::VertexBuffer() :
   _pMesh(nullptr)
{
}

HRESULT VertexBuffer::Initialise(Mesh* mesh)
{
    _pMesh = mesh;
    HRESULT hr = Buffer::Initialise(_pMesh->GetVertices()->GetSize(), D3D11_USAGE_DEFAULT, D3D11_BIND_VERTEX_BUFFER, 0, 0, 0, _pMesh->GetVertices()->GetData());
    if (FAILED(hr))
        return hr;

    return S_OK;
}

void VertexBuffer::Bind(Shader* shader, UINT slot)
{
    UINT stride = _pMesh->GetVertices()->GetStride();
    UINT offset = 0;
    DeviceManager::GetContext()->IASetVertexBuffers(0, 1, &_pBuffer, &stride, &offset);
}
