#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <Windows.h>

namespace Axiom
{
	enum class OpenMode
	{
		Read,
		Write
	};

	enum class Position
	{
		Begin,
		Current,
		End
	};

	HANDLE Open(char* filename, OpenMode mode) noexcept;
	void Read(HANDLE fh, void* const buffer, const DWORD size) noexcept;
	void Seek(HANDLE fh, int offset, Position location) noexcept;
	unsigned long GetFileSize(HANDLE fh);
}

#endif // !FILE_SYSTEM_H
