#ifndef WIN32_WINDOW_H
#define WIN32_WINDOW_H

#include <windows.h>

class Win32Window
{
public:
	Win32Window(HINSTANCE hInstance);
	Win32Window(HINSTANCE hInstance, int width, int height);
	void Initialize();

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND GetHwnd() { return mWindowHandle; }
	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }

private:
	void HandleResize();
	void HandlePaint();
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND mWindowHandle;
	HINSTANCE mInstanceHandle;

	int mWidth{ 600 };
	int mHeight{ 600 };
};

#endif // !WIN32_WINDOW_H