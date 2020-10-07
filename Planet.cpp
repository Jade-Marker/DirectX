#include "Planet.h"

static SimpleVertex vertices[] =
{
    { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },     //0
    { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },      //1
    { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },    //2
    { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },     //3

    { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },      //4
    { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },       //5
    { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT4(0.5f, 0.5f, 5.0f, 1.0f) },     //6
    { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },      //7
};

static WORD indices[] =
{
    0,1,2,
    2,1,3,

    1,5,3,
    3,5,7,

    5,4,7,
    7,4,6,

    4,0,6,
    6,0,2,

    4,5,0,
    0,5,1,

    6,2,3,
    7,6,3
};

static SimpleVertex pyramidVertices[] =
{
    { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT4(0.2f, 0.1f, 0.5f, 1.0f) },      //0
    { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT4(0.5f, 0.9f, 1.0f, 1.0f) },       //1
    { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(0.9f, 1.0f, 0.5f, 1.0f) },     //2
    { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT4(0.1f, 0.5f, 0.2f, 1.0f) },      //3

    { XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT4(1.0f, 0.6f, 0.3f, 1.0f) },       //4
};

static WORD pyramidIndices[] =
{
    0,2,1,
    1,2,3,

    0,1,4,
    1,3,4,
    3,2,4,
    2,0,4
};

Planet::Planet(XMFLOAT3 position, XMFLOAT3 angle, XMFLOAT3 scale, XMFLOAT3 tScale, Planet* parent,
    ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, ID3D11Buffer* pConstantBuffer):
	_position(position), _angle(angle), _scale(scale), _tScale(tScale), _parent(parent),
    _pd3dDevice(pd3dDevice), _pImmediateContext(pImmediateContext), _t(0.0f), _pConstantBuffer(pConstantBuffer)
{
    if (position.x == 0 && position.y == 0)
    {
        vertexSource = vertices;
        vertexCount = 8;
        indexSource = indices;
        indexCount = 36;
    }
    else
    {
        vertexSource = pyramidVertices;
        vertexCount = 5;
        indexSource = pyramidIndices;
        indexCount = 18;
    }

    InitVertexBuffer();
    InitIndexBuffer();
    InitShadersAndInputLayout();
}

void Planet::Draw(DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 projection)
{
    BindBuffersAndLayout();

    DirectX::XMMATRIX mWorld = GetWorldMatrix();

    DirectX::XMMATRIX mView = XMLoadFloat4x4(&view);
    DirectX::XMMATRIX mProjection = XMLoadFloat4x4(&projection);
    //
    // Update variables
    //
    ConstantBuffer cb;
    cb.mWorld = XMMatrixTranspose(mWorld);
    cb.mView = XMMatrixTranspose(mView);
    cb.mProjection = XMMatrixTranspose(mProjection);

    _pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &cb, 0, 0);

    //
    // Renders a triangle
    //
    _pImmediateContext->VSSetShader(_pVertexShader, nullptr, 0);
    _pImmediateContext->VSSetConstantBuffers(0, 1, &_pConstantBuffer);
    _pImmediateContext->PSSetConstantBuffers(0, 1, &_pConstantBuffer);
    _pImmediateContext->PSSetShader(_pPixelShader, nullptr, 0);
    _pImmediateContext->DrawIndexed(indexCount, 0, 0);
}



void Planet::Update()
{
    static DWORD dwTimeStart = 0;
    DWORD dwTimeCur = GetTickCount();

    if (dwTimeStart == 0)
        dwTimeStart = dwTimeCur;

    _t = (dwTimeCur - dwTimeStart) / 1000.0f;

    _angle.x = _t * _tScale.x;
    _angle.y = _t * _tScale.y;
    _angle.z = _t * _tScale.z;
}

XMMATRIX Planet::GetWorldMatrix()
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

HRESULT Planet::InitVertexBuffer()
{
    HRESULT hr;    

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(SimpleVertex) * vertexCount;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory(&InitData, sizeof(InitData));
    InitData.pSysMem = vertexSource;

    hr = _pd3dDevice->CreateBuffer(&bd, &InitData, &_pVertexBuffer);

    if (FAILED(hr))
        return hr;

    return S_OK;
}

HRESULT Planet::InitIndexBuffer()
{
    HRESULT hr;    

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));

    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(WORD) * indexCount;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory(&InitData, sizeof(InitData));
    InitData.pSysMem = indexSource;
    hr = _pd3dDevice->CreateBuffer(&bd, &InitData, &_pIndexBuffer);

    if (FAILED(hr))
        return hr;

    return S_OK;
}

HRESULT Planet::InitShadersAndInputLayout()
{
    HRESULT hr;

    // Compile the vertex shader
    ID3DBlob* pVSBlob = nullptr;
    hr = CompileShaderFromFile(L"DX11 Framework.fx", "VS", "vs_4_0", &pVSBlob);

    if (FAILED(hr))
    {
        MessageBox(nullptr,
            L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return hr;
    }

    // Create the vertex shader
    hr = _pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &_pVertexShader);

    if (FAILED(hr))
    {
        pVSBlob->Release();
        return hr;
    }

    // Compile the pixel shader
    ID3DBlob* pPSBlob = nullptr;
    hr = CompileShaderFromFile(L"DX11 Framework.fx", "PS", "ps_4_0", &pPSBlob);

    if (FAILED(hr))
    {
        MessageBox(nullptr,
            L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return hr;
    }

    // Create the pixel shader
    hr = _pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &_pPixelShader);
    pPSBlob->Release();

    if (FAILED(hr))
        return hr;

    // Define the input layout
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    UINT numElements = ARRAYSIZE(layout);

    // Create the input layout
    hr = _pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
        pVSBlob->GetBufferSize(), &_pVertexLayout);
    pVSBlob->Release();

    if (FAILED(hr))
        return hr;

    return hr;
}

HRESULT Planet::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* pErrorBlob;
    hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
        dwShaderFlags, 0, ppBlobOut, &pErrorBlob);

    if (FAILED(hr))
    {
        if (pErrorBlob != nullptr)
            OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());

        if (pErrorBlob) pErrorBlob->Release();

        return hr;
    }

    if (pErrorBlob) pErrorBlob->Release();

    return S_OK;
}

void Planet::BindBuffersAndLayout()
{
    // Set vertex buffer
    UINT stride = sizeof(SimpleVertex);
    UINT offset = 0;
    _pImmediateContext->IASetVertexBuffers(0, 1, &_pVertexBuffer, &stride, &offset);

    // Set the input layout
    _pImmediateContext->IASetInputLayout(_pVertexLayout);

    // Set index buffer
    _pImmediateContext->IASetIndexBuffer(_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
}
