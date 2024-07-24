#ifndef DDS_READER_H
#define DDS_READER_H

#define MAKEFOURCC(ch0, ch1, ch2, ch3) \
((unsigned int) ch3 << 24 | (unsigned int) ch2 << 16 | (unsigned int) ch1 << 8 | (unsigned int) ch0)

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

struct DDSHeader;
struct DDSHeaderDX10;
struct DDSPixelFormat;
class Texture;

namespace DDSTextureUtils
{
	Texture* LoadDDSTextureFromFile(const char* fileName);
}

#endif
