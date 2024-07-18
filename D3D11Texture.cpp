#include "D3D11Texture.h"

Axiom::D3D11Texture::D3D11Texture(D3D11Device* device, const D3D11TextureDesc& textureDesc, D3D11_SUBRESOURCE_DATA* initData)
	: m_device{device}
{
	// Currently supports shader resources only.
	if (textureDesc.type == D3D11TextureType::Texture1D)
	{
		// Texture1D
		D3D11_TEXTURE1D_DESC desc = {};
		desc.Width = textureDesc.width;
		desc.MipLevels = textureDesc.mipLevels;
		desc.ArraySize = textureDesc.arraySize;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

		m_device->GetDevice()->CreateTexture1D(&desc, nullptr, (ID3D11Texture1D**)(&m_texture));
	}
	else if (textureDesc.type == D3D11TextureType::Texture2D)
	{
		// Texture2D
		D3D11_TEXTURE2D_DESC desc = {};

		m_device->GetDevice()->CreateTexture2D(&desc, nullptr, (ID3D11Texture2D**)(&m_texture));
	}
	else
	{
		// Texture3D
		D3D11_TEXTURE3D_DESC desc = {};

		m_device->GetDevice()->CreateTexture3D(&desc, nullptr, (ID3D11Texture3D**)(&m_texture));
	}
}

Axiom::D3D11Texture::~D3D11Texture()
{
	if (m_texture != nullptr)
	{
		m_texture->Release();
		m_texture = nullptr;
	}
}
