#ifndef D3D11_BUFFER_H
#define D3D11_BUFFER_H

#include "D3D11Device.h"

namespace Axiom
{
	class D3D11Buffer
	{
	public:
		D3D11Buffer(D3D11Device* device, D3D11_BIND_FLAG type, const void* data, unsigned int bufferSize, bool isStaging = false);
		~D3D11Buffer();

		ID3D11Buffer* m_buffer;
		D3D11Device* m_device;
	};
}

#endif // !D3D11_BUFFER_H

