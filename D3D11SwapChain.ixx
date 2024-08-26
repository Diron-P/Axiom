module;

#include <d3d11_4.h>

export module D3D11GDI:D3D11SwapChain;
import :D3D11Device;

namespace Axiom
{
	class WindowsWindow;

	class D3D11SwapChain
	{
	public:
		D3D11SwapChain(D3D11Device* device, const WindowsWindow* window);

		D3D11SwapChain(const D3D11SwapChain&) = delete;
		D3D11SwapChain operator=(const D3D11SwapChain&) = delete;
		D3D11SwapChain(D3D11SwapChain&&) = delete;
		D3D11SwapChain operator=(D3D11SwapChain&&) = delete;

		~D3D11SwapChain();

		void Present();
		ID3D11Texture2D* GetBuffer(unsigned int index);

		D3D11Device* m_device;
		IDXGISwapChain4* m_swapChain;
	};
}
