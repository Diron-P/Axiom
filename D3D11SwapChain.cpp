module;

#include <d3d11_4.h>

module D3D11GDI:D3D11SwapChain;
import :D3D11SwapChain;

#define SAFE_RELEASE(p) if (p != nullptr) { p->Release(); }

Axiom::D3D11SwapChain::D3D11SwapChain(D3D11Device* device, const WindowsWindow* window)
	: m_device{ device }
	, m_swapChain{ nullptr }
{
	IDXGIDevice4* dxgiDevice;
	HRESULT hr = device->m_device->QueryInterface(__uuidof(IDXGIDevice4), reinterpret_cast<void**>(&dxgiDevice));

	IDXGIAdapter* dxgiAdapter;
	hr = dxgiDevice->GetAdapter(&dxgiAdapter);

	IDXGIFactory2* dxgiFactory;
	hr = dxgiAdapter->GetParent(__uuidof(IDXGIDevice4), reinterpret_cast<void**>(&dxgiFactory));

	DXGI_SWAP_CHAIN_DESC1 desc = {};
	desc.Width = window->GetWidth();
	desc.Height = window->GetHeight();
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// TODO - Read more about buffer formats.
	desc.Stereo = false;

	// Disable anti-aliasing.
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;

	// Use the back buffer as an output render target.
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.BufferCount = 2;
	desc.Scaling = DXGI_SCALING_NONE;

	/*
	* In the BitBlt model, used with DXGI_SWAP_EFFECT_DISCARD and DXGI_SWAP_EFFECT_SEQUENTIAL values, 
	* the back buffer contents are copied into the redirection surface every time IDXGISwapChain1::Present1 is called. 
	* On the other hand, in the Flip model, which uses the DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL value, 
	* all back buffers are shared with the DWM, allowing it to compose directly from those back buffers, 
	* eliminating the need for extra copy operations. 
	* Generally, the Flip model is more efficient and offers additional features like enhanced present statistics.
	*/

	desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

	IDXGISwapChain1* swapChain;
	hr = dxgiFactory->CreateSwapChainForHwnd(device->m_device.Get(), window->GetHwnd(), &desc, nullptr, nullptr, &swapChain);

	if (SUCCEEDED(hr))
	{
		swapChain->QueryInterface(IID_PPV_ARGS(&m_swapChain));
	}

	// TODO - Need to analyze the performance cost of smart ptrs

	SAFE_RELEASE(swapChain);
	SAFE_RELEASE(dxgiFactory);
	SAFE_RELEASE(dxgiAdapter);
	SAFE_RELEASE(dxgiDevice);
}

Axiom::D3D11SwapChain::~D3D11SwapChain()
{
	if (m_swapChain)
	{
		m_swapChain->Release();
		m_swapChain = nullptr;
	}
}

void Axiom::D3D11SwapChain::Present()
{
	m_swapChain->Present(0, 0);
}

ID3D11Texture2D* Axiom::D3D11SwapChain::GetBuffer(const unsigned int index)
{
	ID3D11Texture2D* buffer = nullptr;
	const HRESULT hr = m_swapChain->GetBuffer(index, IID_PPV_ARGS(&buffer));
	return buffer;
}
