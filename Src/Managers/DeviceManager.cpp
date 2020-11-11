#include "DeviceManager.h"

DeviceManager::DeviceManager():
	_pDevice(nullptr), _pImmediateContext(nullptr)
{   
	
}

DeviceManager::~DeviceManager()
{
	if (_pImmediateContext) _pImmediateContext->ClearState();
	if (_pImmediateContext) _pImmediateContext->Release();
	if (_pDevice) _pDevice->Release();
}

DeviceManager* DeviceManager::GetInstance()
{
	static DeviceManager instance;

	return &instance;
}

void DeviceManager::Initialise(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext)
{
	DeviceManager* instance = GetInstance();

	instance->_pDevice = pDevice;
	instance->_pImmediateContext = pImmediateContext;
}

ID3D11Device* const DeviceManager::GetDevice()
{
	return GetInstance()->_pDevice;
}

ID3D11DeviceContext* const DeviceManager::GetContext()
{
	return GetInstance()->_pImmediateContext;
}
