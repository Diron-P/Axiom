#include "D3D11Device.h"

Axiom::D3D11Device::D3D11Device()
{
	D3D11_CREATE_DEVICE_FLAG createFlags;
#ifdef _DEBUG
	createFlags = D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevels[] = 
	{
		D3D_FEATURE_LEVEL_11_1
	};

	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;

	HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createFlags, featureLevels, 
		1, D3D11_SDK_VERSION, &device, nullptr, &deviceContext);

	if (SUCCEEDED(hr))
	{
		device->QueryInterface(IID_PPV_ARGS(&m_device));
		deviceContext->QueryInterface(IID_PPV_ARGS(&m_deviceContext));
	}


}

Axiom::D3D11Device::~D3D11Device()
{
	if (m_device)
	{
		m_device->Release();
		m_device = nullptr;
	}
}
