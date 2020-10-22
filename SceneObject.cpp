#include "SceneObject.h"

SceneObject::SceneObject(XMFLOAT3 position, XMFLOAT3 angle, XMFLOAT3 scale, XMFLOAT3 tScale, SceneObject* parent, Mesh* mesh, bool startInWireFrame, Shader* shader,
    ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, ID3D11Buffer* pLocalConstantBuffer, ID3D11Buffer* pGlobalConstantBuffer) :
	_position(position), _angle(angle), _scale(scale), _tScale(tScale), _parent(parent), _mesh(mesh), _shader(shader),
    _pd3dDevice(pd3dDevice), _pImmediateContext(pImmediateContext), _t(0.0f), _pLocalConstantBuffer(pLocalConstantBuffer), _pGlobalConstantBuffer(pGlobalConstantBuffer),
    _rasterKeyDown(false), _yDirState(false), _xDirState(false)
{
    InitVertexBuffer();
    InitIndexBuffer();
    InitRasterState(startInWireFrame);
}

void SceneObject::Draw()
{
    InitDraw();

    DirectX::XMMATRIX mWorld = GetWorldMatrix();

    LocalConstantBuffer cb;
    cb.WorldMatrix = XMMatrixTranspose(mWorld);

    _pImmediateContext->UpdateSubresource(_pLocalConstantBuffer, 0, nullptr, &cb, 0, 0);


    _shader->SetShader();
    _shader->SetConstantBuffers(cLocalConstantBufferSlot, 1, &_pLocalConstantBuffer);

    _pImmediateContext->DrawIndexed(_mesh->GetIndexCount(), 0, 0);
}



void SceneObject::Update(float deltaTime)
{
    if (_xDirState)
        _angle.x += _tScale.x * deltaTime;
    else
        _angle.x -= _tScale.x * deltaTime;

    if (_yDirState)
        _angle.y += _tScale.y * deltaTime;
    else
        _angle.y -= _tScale.y * deltaTime;

    _angle.z += _tScale.z * deltaTime;

    if (GetAsyncKeyState(VK_UP) && !_rasterKeyDown)
    {
        _rasterKeyDown = true;

        if (_rasterState == _wireframeRasterState)
            _rasterState = _solidRasterState;
        else
            _rasterState = _wireframeRasterState;

    }
    else if (GetAsyncKeyState(VK_DOWN) && _rasterKeyDown)
    {
        _rasterKeyDown = false;

        if (_rasterState == _wireframeRasterState)
            _rasterState = _solidRasterState;
        else
            _rasterState = _wireframeRasterState;

    }

    if (GetAsyncKeyState('A') && !_xDirState)
        _xDirState = true;
    else if (GetAsyncKeyState('D') && _xDirState)
        _xDirState = false;

    if (GetAsyncKeyState('W') && !_yDirState)
        _yDirState = true;
    else if (GetAsyncKeyState('S') && _yDirState)
        _yDirState = false;
}

XMMATRIX SceneObject::GetWorldMatrix()
{
    DirectX::XMMATRIX world =
        DirectX::XMMatrixScalingFromVector(XMLoadFloat3(&_scale)) *
        DirectX::XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&_angle)) *
        DirectX::XMMatrixTranslationFromVector(XMLoadFloat3(&_position)) *
        DirectX::XMMatrixIdentity();

    if (_parent != nullptr)
    {
        world = world * _parent->GetWorldMatrix();
    }

    return world;
}

HRESULT SceneObject::InitVertexBuffer()
{
    HRESULT hr;    

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = _mesh->GetVertices()->GetSize();
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory(&InitData, sizeof(InitData));
    InitData.pSysMem = _mesh->GetVertices()->GetData();

    hr = _pd3dDevice->CreateBuffer(&bd, &InitData, &_pVertexBuffer);

    if (FAILED(hr))
        return hr;

    return S_OK;
}

HRESULT SceneObject::InitIndexBuffer()
{
    HRESULT hr;    

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));

    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(WORD) * _mesh->GetIndexCount();
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory(&InitData, sizeof(InitData));
    InitData.pSysMem = _mesh->GetIndices();
    hr = _pd3dDevice->CreateBuffer(&bd, &InitData, &_pIndexBuffer);

    if (FAILED(hr))
        return hr;

    return S_OK;
}

void SceneObject::InitDraw()
{
    // Set vertex buffer
    UINT stride = _mesh->GetVertices()->GetStride();
    UINT offset = 0;
    _pImmediateContext->IASetVertexBuffers(0, 1, &_pVertexBuffer, &stride, &offset);

    // Set the input layout
    _shader->SetInputLayout();

    // Set index buffer
    _pImmediateContext->IASetIndexBuffer(_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

    //Set the raster state
    _pImmediateContext->RSSetState(_rasterState);
}

void SceneObject::InitRasterState(bool startInWireFrame)
{
    HRESULT hr;
    D3D11_RASTERIZER_DESC desc;
    ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));

    desc.FillMode = D3D11_FILL_WIREFRAME;
    desc.CullMode = D3D11_CULL_NONE;
    hr = _pd3dDevice->CreateRasterizerState(&desc, &_wireframeRasterState);

    desc.FillMode = D3D11_FILL_SOLID;
    desc.CullMode = D3D11_CULL_BACK;
    hr = _pd3dDevice->CreateRasterizerState(&desc, &_solidRasterState);

    if (startInWireFrame)
        _rasterState = _wireframeRasterState;
    else
        _rasterState = _solidRasterState;
}
