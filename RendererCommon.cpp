#include "RendererCommon.h"

Image::Image()
{
}

Image::Image(unsigned int width, unsigned int height, unsigned int depth, unsigned int mipLevels, unsigned int arraySize, TextureType type, SubResourceData* subResources)
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

Image::~Image()
{
	delete[] m_subResources;
}

SubResourceData* Image::GetSubResources() const
{
	return m_subResources;
}

void Image::SetProperties(unsigned int width, unsigned int height, unsigned int depth, unsigned int mipLevels, unsigned int arraySize, TextureType type)
{
	m_width = width;
	m_height = height;
	m_depth = depth;
	m_mipLevels = mipLevels;
	m_arraySize = arraySize;
	m_type = type;
}
