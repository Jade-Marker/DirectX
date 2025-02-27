#include "Texture.h"

Texture::Texture(const WCHAR* filePath):
    _pTexture(nullptr), _pSamplerLinear(nullptr)
{
    Load(filePath);
}

Texture::Texture():
    _pTexture(nullptr), _pSamplerLinear(nullptr)
{
}

Texture::~Texture()
{
    if (_pTexture) _pTexture->Release();
    if (_pSamplerLinear) _pSamplerLinear->Release();
}

void Texture::Load(const WCHAR* filePath)
{
    DirectX::CreateDDSTextureFromFile(DeviceManager::GetDevice(), filePath, nullptr, &_pTexture);

    D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory(&sampDesc, sizeof(sampDesc));
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

    DeviceManager::GetDevice()->CreateSamplerState(&sampDesc, &_pSamplerLinear);
}

void Texture::Bind(Shader* shader, UINT slot)
{
    if (_pTexture && _pSamplerLinear)
    {
        shader->SetShaderResources(slot, 1, &_pTexture);
        shader->SetSamplers(slot, 1, &_pSamplerLinear);
    }
}

void Texture::Unbind(Shader* shader, UINT slot)
{
    if (_pTexture && _pSamplerLinear)
    {
        shader->SetShaderResources(slot, 0, nullptr);
        shader->SetSamplers(slot, 0, nullptr);
    }
}

Texture* const Texture::GetDefault()
{
    static Texture DefaultTexture = Texture(L"Res\\Textures\\DefaultTexture.dds");

    return &DefaultTexture;
}
