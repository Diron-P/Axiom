#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

class Image;

namespace ImageUtils
{
	Image* LoadWICTextureFromFilename(const wchar_t* filename);
	Image* LoadWICTextureFromStream(void* data, unsigned int size);
	Image* LoadDDSTextureFromFile(const char* fileName);
}

#endif
