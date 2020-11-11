#include "ConstantBuffer.h"

HRESULT ConstantBuffer::Initialise(UINT size)
{
	return Buffer::Initialise(size, D3D11_USAGE_DEFAULT, D3D11_BIND_CONSTANT_BUFFER, 0, 0, 0, nullptr);
}

void ConstantBuffer::Bind(Shader* shader, UINT slot)
{
	shader->SetConstantBuffers(slot, 1, &_pBuffer);
}

void ConstantBuffer::Update(const void* pData)
{
	DeviceManager::GetContext()->UpdateSubresource(_pBuffer, 0, nullptr, pData, 0, 0);
}
