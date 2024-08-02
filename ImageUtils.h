#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

class Texture;

namespace ImageUtils
{
	Texture* LoadWICTextureFromFilename(const wchar_t* filename);
	Texture* LoadWICTextureFromStream(void* data, unsigned int size);
	Texture* LoadDDSTextureFromFile(const char* fileName);
}

#endif
