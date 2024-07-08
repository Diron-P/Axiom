#include "Win32Window.h"

Win32Window::Win32Window(HINSTANCE hInstance)
	: mInstanceHandle{ hInstance }
{
	Initialize();
}

Win32Window::Win32Window(HINSTANCE hInstance, int width, int height) 
	: mInstanceHandle{ hInstance }
	, mWidth{ width }
	, mHeight{ height }
{
	Initialize();
}

void Win32Window::Initialize()
{
	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Spectra Window Class";

	WNDCLASS wc = { 0 };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = mInstanceHandle;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	mWindowHandle = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"Spectra Engine",                // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, mWidth, mHeight,

		NULL,       // Parent window    
		NULL,       // Menu
		mInstanceHandle, // Instance handle
		this        // Additional application data
	);

	ShowWindow(mWindowHandle, 1);
}

LRESULT Win32Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Win32Window* window;
	if (uMsg == WM_CREATE)
	{
		CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		window = reinterpret_cast<Win32Window*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
	}
	else
	{
		LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window = reinterpret_cast<Win32Window*>(ptr);
	}

	if (window)
	{
		window->HandleMessage(uMsg, wParam, lParam);
	}
	else
	{
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

void Win32Window::HandleResize()
{
}

void Win32Window::HandlePaint()
{
}

LRESULT Win32Window::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_SIZE:
		HandleResize();
		break;

	case WM_PAINT:
		HandlePaint();
		break;

	default:
		return DefWindowProc(mWindowHandle, uMsg, wParam, lParam);
	}

	return TRUE;
}
