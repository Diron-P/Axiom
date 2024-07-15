#include "D3D11GHI.h"
#include "WindowsWindow.h"
#include "D3D11Buffer.h"

Axiom::D3D11GHI::D3D11GHI(const WindowsWindow* window)
	: m_swapChain{ &m_device, window }
{
	ID3D11Texture2D* buffer = m_swapChain.GetBuffer(0);
	HRESULT hr = m_device.GetDevice()->CreateRenderTargetView(buffer, nullptr, &m_rtv);

	buffer->Release();
	buffer = nullptr;

	D3D11_TEXTURE2D_DESC depthBufferDesc = {};
	depthBufferDesc.Width = window->GetWidth();
	depthBufferDesc.Height = window->GetHeight();
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	hr = m_device.GetDevice()->CreateTexture2D(&depthBufferDesc, nullptr, &m_depthStencilBuffer);

	// Create depth stencil state.
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	hr = m_device.GetDevice()->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);

	m_device.GetDeviceContext()->OMSetDepthStencilState(m_depthStencilState, 1);

	// Create the depthe stencil view.
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;

	hr = m_device.GetDevice()->CreateDepthStencilView(m_depthStencilBuffer, &dsvDesc, &m_dsv);

	// Bind the render target view and depth stencil buffer to the output render pipeline.
	m_device.GetDeviceContext()->OMSetRenderTargets(1, &m_rtv, m_dsv);

	D3D11_VIEWPORT vp = {};
	vp.Width = (float)window->GetWidth();
	vp.Height = (float)window->GetHeight();
	vp.MinDepth = 0.0;
	vp.MaxDepth = 1.0;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;

	m_device.GetDeviceContext()->RSSetViewports(1, &vp);
}

void Axiom::D3D11GHI::Initialize()
{
}

void Axiom::D3D11GHI::Shutdown()
{
}

void Axiom::D3D11GHI::CreateBuffer(BufferType type, const void* data, const unsigned int size)
{
	D3D11_BIND_FLAG bindLocation;
	switch (type)
	{
	case BufferType::IndexBuffer:
		bindLocation = D3D11_BIND_INDEX_BUFFER;
		break;
	case BufferType::ConstantBuffer:
		bindLocation = D3D11_BIND_CONSTANT_BUFFER;
		break;
	default:
		bindLocation = D3D11_BIND_VERTEX_BUFFER;
	};

	m_buffers.push_back(new D3D11Buffer(&m_device, bindLocation, data, size));
}

void Axiom::D3D11GHI::Render()
{
	float clearColor[4] = { 1.0, 1.0, 0.0, 1.0 };
	m_device.GetDeviceContext()->ClearRenderTargetView(m_rtv, clearColor);
	m_swapChain.Present();
}
