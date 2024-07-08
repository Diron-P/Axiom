#ifndef D3D11_SWAP_CHAIN_H
#define D3D11_SWAP_CHAIN_H

#include "D3D11Device.h"

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

		D3D11Device* m_device;
		IDXGISwapChain4* m_swapChain;
	};
}

#endif // !D3D11_SWAP_CHAIN_H
