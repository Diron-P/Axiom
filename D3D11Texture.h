#ifndef D3D11_TEXTURE_H
#define D3D11_TEXTURE_H

#include "D3D11Device.h"

namespace Axiom
{
	enum class D3D11TextureType
	{
		Texture1D,
		Texture2D,
		Texture3D
	};

	struct D3D11TextureDesc
	{
		unsigned int width;
		unsigned int height;
		unsigned int depth;
		unsigned int mipLevels;
		unsigned int arraySize;
		D3D11TextureType type;
	};

	class D3D11Texture
	{
	public:
		D3D11Texture(D3D11Device* device, const D3D11TextureDesc& textureDesc, D3D11_SUBRESOURCE_DATA* initData);
		~D3D11Texture();

	private:
		D3D11Device* m_device;
		ID3D11Resource* m_texture;
	};
}

#endif // !D3D11_TEXTURE_H
