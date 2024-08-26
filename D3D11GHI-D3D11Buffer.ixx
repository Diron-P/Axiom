export module D3D11GHI:D3D11Buffer;	// Module partition interface
import :D3D11Device;	// Import partition

struct ID3D11Buffer;
class D3D11Device;

namespace Axiom
{
	class D3D11Buffer
	{
	public:
		D3D11Buffer(D3D11Device* device, const void* data, unsigned int bufferSize, bool isStaging = false);
		~D3D11Buffer();

		ID3D11Buffer* m_buffer;
		D3D11Device* m_device;
	};
}
