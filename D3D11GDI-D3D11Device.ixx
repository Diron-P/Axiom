module;

#include <d3d11_4.h>
#include "RefCountPtr.h"

export module D3D11GDI:D3D11Device;

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

		/*ID3D11Device4* GetDevice() const { return m_device; };
		ID3D11DeviceContext4* GetDeviceContext() const { return m_deviceContext; };*/

		RefCountPtr<ID3D11Device4> m_device;
		RefCountPtr<ID3D11DeviceContext4> m_deviceContext;
	};
}