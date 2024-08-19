#ifndef PLATFORM_H
#define PLATFORM_H

#ifdef _DEBUG

#define ASSERT(x) if (x == false) __debugbreak();

#endif

#endif
