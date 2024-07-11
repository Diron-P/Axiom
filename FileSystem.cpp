#include "FileSystem.h"

HANDLE Axiom::Open(char* filename, OpenMode mode) noexcept
{
	if (filename == nullptr)
	{
		return nullptr;
	}

	DWORD desiredAccess;
	switch (mode)
	{
	case OpenMode::Read:
		desiredAccess = GENERIC_READ;
		break;
	case OpenMode::Write:
		desiredAccess = GENERIC_WRITE;
		break;
	default:
		desiredAccess = GENERIC_READ;
	}

	HANDLE fh = CreateFileA(filename, desiredAccess, 0, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (fh == INVALID_HANDLE_VALUE)
	{
		return nullptr;
	}

	return fh;
}

void Axiom::Read(HANDLE fh, void* const buffer, const DWORD size) noexcept
{
	if (fh == nullptr || buffer == nullptr)
	{
		return;
	}

	DWORD numBytesRead = 0ul;
	ReadFile(fh, buffer, size, &numBytesRead, nullptr);
}

void Axiom::Seek(HANDLE fh, int offset, Position location) noexcept
{
	if (fh == nullptr)
	{
		return;
	}

	DWORD moveMethod;
	switch (location)
	{
	case Position::Begin:
		moveMethod = FILE_BEGIN;
		break;
	case Position::Current:
		moveMethod = FILE_CURRENT;
		break;
	case Position::End:
		moveMethod = FILE_END;
		break;
	default:
		moveMethod = FILE_BEGIN;
	}

	DWORD currPos = SetFilePointer(fh, offset, nullptr, moveMethod);
	if (currPos == INVALID_SET_FILE_POINTER || currPos < 0)
	{
		return;
	}
}

unsigned long Axiom::GetFileSize(HANDLE fh)
{
	if (fh == nullptr)
	{
		return 0;
	}

	LARGE_INTEGER fileSize;
	GetFileSizeEx(fh, &fileSize);

	return fileSize.QuadPart;
}
