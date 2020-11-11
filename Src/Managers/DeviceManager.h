#pragma once
#include <d3d11.h>
class DeviceManager
{
private:
	ID3D11Device* _pDevice;
	ID3D11DeviceContext* _pImmediateContext;

	DeviceManager();
	~DeviceManager();
	static DeviceManager* GetInstance();

public:
	static void Initialise(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext);
	static ID3D11Device* const GetDevice();
	static ID3D11DeviceContext* const GetContext();
	
};