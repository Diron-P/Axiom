#ifndef RENDERER_COMMON_H
#define RENDERER_COMMON_H

enum class TextureType
{
	Texture1D,
	Texture2D,
	Texture3D
};

struct TextureDesc
{
	unsigned int width;
	unsigned int height;
	unsigned int depth;
	unsigned int mipLevels;
	unsigned int arraySize;
	TextureType type;
};

#endif
