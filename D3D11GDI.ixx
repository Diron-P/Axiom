export module D3D11GDI;

export import :D3D11Device;
export import :D3D11SwapChain;

export namespace Axiom
{
	//class D3D11Buffer;

	enum class BufferType
	{
		VertexBuffer,
		IndexBuffer,
		ConstantBuffer,
		StructuredBuffer
	};

	class D3D11GDI
	{
	public:
		D3D11GDI();

		void Initialize();
		void Shutdown();

		void CreateBuffer(BufferType type, const void* data, unsigned int size);
		void CreateTexture();

		void Render();

	private:
		D3D11Device m_device;
		D3D11SwapChain m_swapChain;
		/*ID3D11RenderTargetView* m_rtv;
		ID3D11Texture2D* m_depthStencilBuffer;
		ID3D11DepthStencilState* m_depthStencilState;
		ID3D11DepthStencilView* m_dsv;
		std::vector<D3D11Buffer*>m_buffers;*/
	};
}