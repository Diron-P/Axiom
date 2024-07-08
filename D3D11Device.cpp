#include "D3D11Device.h"

Axiom::D3D11Device::D3D11Device()
{
	unsigned int dxgiFlags = 0;
	D3D11_CREATE_DEVICE_FLAG deviceFlags;
#ifdef _DEBUG
	dxgiFlags = DXGI_CREATE_FACTORY_DEBUG;
	deviceFlags = D3D11_CREATE_DEVICE_DEBUG;
#endif

	IDXGIFactory2* dxgiFactory;
	HRESULT hr = CreateDXGIFactory2(dxgiFlags, IID_PPV_ARGS(&dxgiFactory));

	if (FAILED(hr))
	{
		return;
	}

	IDXGIAdapter1* adapter;
    for (unsigned int i = 0; dxgiFactory->EnumAdapters1(i, &adapter) != DXGI_ERROR_NOT_FOUND; ++i)
    {
        DXGI_ADAPTER_DESC1 desc;
        adapter->GetDesc1(&desc);

        // Skip the software adapter.
        if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
        {
            continue;
        }

        if (SUCCEEDED(D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_12_0, _uuidof(ID3D12Device), nullptr)))
        {
            break;
        }

        adapter->Release();
    }

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1
	};

	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;

	// Create the device and the immediate context.
	hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, deviceFlags, featureLevels,
		1, D3D11_SDK_VERSION, &device, nullptr, &deviceContext);

	if (SUCCEEDED(hr))
	{
		device->QueryInterface(IID_PPV_ARGS(&m_device));
		deviceContext->QueryInterface(IID_PPV_ARGS(&m_deviceContext));
	}

	device->Release();
	deviceContext->Release();
}

Axiom::D3D11Device::~D3D11Device()
{
	if (m_device)
	{
		m_device->Release();
		m_device = nullptr;
	}
}
