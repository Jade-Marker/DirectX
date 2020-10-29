#include "Shader.h"

HRESULT Shader::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
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

Shader::Shader(WCHAR* shaderSource, D3D11_INPUT_ELEMENT_DESC* layout, UINT numLayoutElements, ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext) :
    _pd3dDevice(pd3dDevice), _pImmediateContext(pImmediateContext)
{
    HRESULT hr;

    // Compile the vertex shader
    ID3DBlob* pVSBlob = nullptr;
    hr = CompileShaderFromFile(shaderSource, "VS", "vs_4_0", &pVSBlob);

    if (FAILED(hr))
    {
        MessageBox(nullptr,
            L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
    }
    else
    {

        // Create the vertex shader
        hr = _pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &_pVertexShader);

        if (FAILED(hr))
        {
            pVSBlob->Release();
            MessageBox(nullptr,
                L"Unable to create the vertex shader", L"Error", MB_OK);
        }
        else
        {

            // Compile the pixel shader
            ID3DBlob* pPSBlob = nullptr;
            hr = CompileShaderFromFile(shaderSource, "PS", "ps_4_0", &pPSBlob);

            if (FAILED(hr))
            {
                MessageBox(nullptr,
                    L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
            }
            else
            {


                // Create the pixel shader
                hr = _pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &_pPixelShader);
                pPSBlob->Release();

                if (FAILED(hr))
                    MessageBox(nullptr,
                        L"Unable to create the pixel shader", L"Error", MB_OK);
                else
                {
                    // Create the input layout
                    hr = _pd3dDevice->CreateInputLayout(layout, numLayoutElements, pVSBlob->GetBufferPointer(),
                        pVSBlob->GetBufferSize(), &_pVertexLayout);
                    pVSBlob->Release();

                    if (FAILED(hr))
                        MessageBox(nullptr,
                            L"Unable to create the layout", L"Error", MB_OK);
                }
            }
        }
    }
}

void Shader::SetInputLayout()
{
    _pImmediateContext->IASetInputLayout(_pVertexLayout);
}

void Shader::SetShader()
{
    _pImmediateContext->VSSetShader(_pVertexShader, nullptr, 0);   
    _pImmediateContext->PSSetShader(_pPixelShader, nullptr, 0);
}

void Shader::SetConstantBuffers(UINT startSlot, UINT numBuffers, ID3D11Buffer* const* constantBuffers)
{
    _pImmediateContext->VSSetConstantBuffers(startSlot, numBuffers, constantBuffers);
    _pImmediateContext->PSSetConstantBuffers(startSlot, numBuffers, constantBuffers);
}

void Shader::SetShaderResources(UINT startSlot, UINT numViews, ID3D11ShaderResourceView* const* ppShaderResourceViews)
{
    _pImmediateContext->VSSetShaderResources(startSlot, numViews, ppShaderResourceViews);
    _pImmediateContext->PSSetShaderResources(startSlot, numViews, ppShaderResourceViews);
}

void Shader::SetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
{
    _pImmediateContext->VSSetSamplers(StartSlot, NumSamplers, ppSamplers);
    _pImmediateContext->PSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}
