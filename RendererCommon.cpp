#include "RendererCommon.h"

Texture::Texture()
{
}

Texture::Texture(unsigned int width, unsigned int height, unsigned int depth, unsigned int mipLevels, unsigned int arraySize, TextureType type, SubResourceData* subResources)
	: m_width{ width }
	, m_height{ height }
	, m_depth{ depth }
	, m_mipLevels{ mipLevels }
	, m_arraySize{ arraySize }
	, m_type{ type }
	, m_numSubResources{m_mipLevels * m_arraySize}
	, m_subResources{subResources}
{
}

Texture::~Texture()
{
	delete[] m_subResources;
}

SubResourceData* Texture::GetSubResources() const
{
	return m_subResources;
}

void Texture::SetProperties(unsigned int width, unsigned int height, unsigned int depth, unsigned int mipLevels, unsigned int arraySize, TextureType type)
{
	m_width = width;
	m_height = height;
	m_depth = depth;
	m_mipLevels = mipLevels;
	m_arraySize = arraySize;
	m_type = type;
}
