#include "Shader.h"

HRESULT Shader::CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
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

    ShaderInclude include;

    ID3DBlob* pErrorBlob;
    hr = D3DCompileFromFile(szFileName, nullptr, &include, szEntryPoint, szShaderModel,
        dwShaderFlags, 0, ppBlobOut, &pErrorBlob);

    if (FAILED(hr))
    {
        if (hr != HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
        {
            if (pErrorBlob != nullptr)
                OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());

            if (pErrorBlob) pErrorBlob->Release();
        }

        return hr;
    }

    if (pErrorBlob) pErrorBlob->Release();

    return S_OK;
}

Shader::Shader(const WCHAR* shaderSource, D3D11_INPUT_ELEMENT_DESC* layout, UINT numLayoutElements) :
    _pVertexShader(nullptr), _pPixelShader(nullptr), _pVertexLayout(nullptr)
{
    HRESULT hr;

    // Compile the vertex shader
    ID3DBlob* pVSBlob = nullptr;
    hr = CompileShaderFromFile(shaderSource, "VS", "vs_5_0", &pVSBlob);

    if (FAILED(hr))
    {
        if (hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
            MessageBox(nullptr, L"The FX file cannot be found.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        else
            MessageBox(nullptr, L"The shader cannot be compiled. ", L"Error", MB_OK);
        return;
    }

    // Create the vertex shader
    hr = DeviceManager::GetDevice()->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &_pVertexShader);

    if (FAILED(hr))
    {
        pVSBlob->Release();
        MessageBox(nullptr,
            L"Unable to create the vertex shader", L"Error", MB_OK);
        return;
    }


    // Compile the pixel shader
    ID3DBlob* pPSBlob = nullptr;
    hr = CompileShaderFromFile(shaderSource, "PS", "ps_5_0", &pPSBlob);

    if (FAILED(hr))
    {
        MessageBox(nullptr,
            L"The shader cannot be compiled. ", L"Error", MB_OK);
        return;
    }

    // Create the pixel shader
    hr = DeviceManager::GetDevice()->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &_pPixelShader);
    pPSBlob->Release();

    if (FAILED(hr))
    {
        MessageBox(nullptr,
            L"Unable to create the pixel shader", L"Error", MB_OK);
        return;
    }

    // Create the input layout
    hr = DeviceManager::GetDevice()->CreateInputLayout(layout, numLayoutElements, pVSBlob->GetBufferPointer(),
        pVSBlob->GetBufferSize(), &_pVertexLayout);
    pVSBlob->Release();

    if (FAILED(hr))
    {
        MessageBox(nullptr,
            L"Unable to create the layout", L"Error", MB_OK);
        return;
    }
}

Shader::~Shader()
{
    if (_pVertexShader) _pVertexShader->Release();
    if (_pPixelShader) _pPixelShader->Release();
    if (_pVertexLayout) _pVertexLayout->Release();
}

void Shader::SetInputLayout()
{
    DeviceManager::GetContext()->IASetInputLayout(_pVertexLayout);
}

void Shader::SetShader()
{
    DeviceManager::GetContext()->VSSetShader(_pVertexShader, nullptr, 0);
    DeviceManager::GetContext()->PSSetShader(_pPixelShader, nullptr, 0);
}

void Shader::SetConstantBuffers(UINT startSlot, UINT numBuffers, ID3D11Buffer* const* constantBuffers)
{
    DeviceManager::GetContext()->VSSetConstantBuffers(startSlot, numBuffers, constantBuffers);
    DeviceManager::GetContext()->PSSetConstantBuffers(startSlot, numBuffers, constantBuffers);
}

void Shader::SetShaderResources(UINT startSlot, UINT numViews, ID3D11ShaderResourceView* const* ppShaderResourceViews)
{
    DeviceManager::GetContext()->VSSetShaderResources(startSlot, numViews, ppShaderResourceViews);
    DeviceManager::GetContext()->PSSetShaderResources(startSlot, numViews, ppShaderResourceViews);
}

void Shader::SetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
{
    DeviceManager::GetContext()->VSSetSamplers(StartSlot, NumSamplers, ppSamplers);
    DeviceManager::GetContext()->PSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}
