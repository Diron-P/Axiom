#ifndef WIC_TEXTURE_LOADER_H
#define WIC_TEXTURE_LOADER_H

namespace Axiom
{
	void LoadTextureFromFilename(const wchar_t* filename);
	void LoadTextureFromStream(const void* buffer, unsigned int size);
}

#endif
