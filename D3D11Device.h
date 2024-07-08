#ifndef D3D11_DEVICE_H
#define D3D11_DEVICE_H

#include <d3d11_4.h>

namespace Axiom
{
	class D3D11Device
	{
	public:
		D3D11Device();

		D3D11Device(const D3D11Device&) = delete;
		D3D11Device operator=(const D3D11Device&) = delete;
		D3D11Device(D3D11Device&&) = delete;
		D3D11Device operator=(D3D11Device&&) = delete;

		~D3D11Device();

		ID3D11Device4* GetDevice() const { return m_device; };
		ID3D11DeviceContext4* GetDeviceContext() const { return m_deviceContext; };

	private:
		ID3D11Device4* m_device{ nullptr };
		ID3D11DeviceContext4* m_deviceContext{ nullptr };
	};
}

#endif // !D3D11_DEVICE_H
