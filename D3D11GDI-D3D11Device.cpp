module;	// Beginning of the global module fragment

// This is the global module fragment where you can use preprocessor directives such as #include.

#include <d3d11_4.h>
#include "RefCountPtr.h"

module D3D11GDI:D3D11Device;

Axiom::D3D11Device::D3D11Device()
{
	//unsigned int dxgiFlags = 0;
	D3D11_CREATE_DEVICE_FLAG deviceFlags;

#ifdef _DEBUG
	//dxgiFlags = DXGI_CREATE_FACTORY_DEBUG;
	deviceFlags = D3D11_CREATE_DEVICE_DEBUG;
#endif

	IDXGIFactory2* dxgiFactory;
	HRESULT hr = CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory));

	// D3D11_SDK supports D3D_FEATURE_LEVEL_12_1 and D3D_FEATURE_LEVEL_12_0. 
	// For these feature levels, the system needs Direct3D 11.3 or Direct3D 12 runtimes. 
	// Support for these levels will be added in Direct3D 12 RHI.

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	RefCountPtr<IDXGIAdapter1> adapter;
	D3D_FEATURE_LEVEL highestSupportedLevel = D3D_FEATURE_LEVEL_9_1;
	int adapterIndex = 0;

    for (unsigned int i = 0; dxgiFactory->EnumAdapters1(i, &adapter) != DXGI_ERROR_NOT_FOUND; ++i)
    {
        DXGI_ADAPTER_DESC1 desc;
        adapter->GetDesc1(&desc);

        // Skip the software adapter.
        if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
        {
            continue;
        }

		D3D_FEATURE_LEVEL supportedLevel;

		// If the GPU does not support the requested feature level, but the required runtimes are present, 
		// the system will create a device for the highest feature level supported by the GPU from the list provided.

		hr = D3D11CreateDevice(adapter.Get(), D3D_DRIVER_TYPE_UNKNOWN, nullptr, 0, featureLevels, sizeof(featureLevels) / sizeof(D3D_FEATURE_LEVEL), D3D11_SDK_VERSION, nullptr, &supportedLevel, nullptr);

		// If Direct3D 11.1 runtime is not installed, recreate the device using the next available feature level.
        if (hr == E_INVALIDARG)
        {
            hr = D3D11CreateDevice(adapter.Get(), D3D_DRIVER_TYPE_UNKNOWN, nullptr, 0, featureLevels + 1, (sizeof(featureLevels) / sizeof(D3D_FEATURE_LEVEL)) - 1, D3D11_SDK_VERSION, nullptr, &supportedLevel, nullptr);
        }

		if (supportedLevel > highestSupportedLevel)
		{
			highestSupportedLevel = supportedLevel;
			adapterIndex = i;
		}
    }	

	RefCountPtr<ID3D11Device> device;
	RefCountPtr<ID3D11DeviceContext> deviceContext;

	dxgiFactory->EnumAdapters1(adapterIndex, &adapter);

	// Create the device and the immediate context.
	hr = D3D11CreateDevice(adapter.Get(), D3D_DRIVER_TYPE_UNKNOWN, nullptr, deviceFlags, featureLevels,
		sizeof(featureLevels) / sizeof(D3D_FEATURE_LEVEL), D3D11_SDK_VERSION, &device, nullptr, &deviceContext);

	if (SUCCEEDED(hr))
	{
		device.As(m_device);
		deviceContext.As(m_deviceContext);
	}

	dxgiFactory->Release();
}

Axiom::D3D11Device::~D3D11Device()
{
	// RefCountPtr will handle the resource deallocation of m_device and m_deviceContext
	/*if (m_device != nullptr)
	{
		m_device->Release();
		m_device = nullptr;
	}

	if (m_deviceContext != nullptr)
	{
		m_deviceContext->Release();
		m_deviceContext = nullptr;
	}*/
}
