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

struct SubResourceData
{
	~SubResourceData()
	{
		delete[] initData;
	}

	void* initData;
	unsigned int memPitch;
	unsigned int memSlicePitch;
};

class Texture
{
public:
	Texture();
	Texture(unsigned int width, unsigned int height, unsigned int depth, unsigned int mipLevels, unsigned int arraySize, TextureType type, SubResourceData* subResources);

	~Texture();

	SubResourceData* GetSubResources() const;
	void SetProperties(unsigned int width, unsigned int height, unsigned int depth, unsigned int mipLevels, unsigned int arraySize, TextureType type);

private:
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_depth;
	unsigned int m_mipLevels;
	unsigned int m_arraySize;
	TextureType m_type;

	unsigned int m_numSubResources;
	SubResourceData* m_subResources;
};

#endif
