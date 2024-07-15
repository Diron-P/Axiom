#ifndef D3D11_GDI_H
#define D3D11_GDI_H

#include "D3D11Device.h"
#include "D3D11SwapChain.h"
#include <vector>

namespace Axiom
{
	enum class BufferType
	{
		VertexBuffer,
		IndexBuffer,
		ConstantBuffer,
		StructuredBuffer
	};

	class D3D11GHI
	{
	public:
		D3D11GHI(const WindowsWindow* window);

		void Initialize();
		void Shutdown();

		void CreateBuffer(BufferType type, const void* data, unsigned int size);

		void Render();

	private:
		D3D11Device m_device;
		D3D11SwapChain m_swapChain;
		ID3D11RenderTargetView* m_rtv;
		ID3D11Texture2D* m_depthStencilBuffer;
		ID3D11DepthStencilState* m_depthStencilState;
		ID3D11DepthStencilView* m_dsv;
		std::vector<D3D11Buffer*>m_buffers;
	};
}

#endif // !D3D11_GDI_H
