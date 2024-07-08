#include "WindowsWindow.h"

Axiom::WindowsWindow::WindowsWindow(HINSTANCE hInstance)
	: m_instanceHandle{ hInstance }
{
	Initialize();
}

Axiom::WindowsWindow::WindowsWindow(const HINSTANCE hInstance, const int width, const int height) 
	: m_instanceHandle{ hInstance }
	, m_width{ width }
	, m_height{ height }
{
	Initialize();
}

void Axiom::WindowsWindow::Initialize()
{
	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Spectra Window Class";

	WNDCLASS wc = { 0 };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = m_instanceHandle;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	m_windowHandle = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"Spectra Engine",                // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, m_width, m_height,

		NULL,       // Parent window    
		NULL,       // Menu
		m_instanceHandle, // Instance handle
		this        // Additional application data
	);

	ShowWindow(m_windowHandle, 1);
}

LRESULT Axiom::WindowsWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	WindowsWindow* window;
	if (uMsg == WM_CREATE)
	{
		CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		window = reinterpret_cast<WindowsWindow*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
	}
	else
	{
		LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window = reinterpret_cast<WindowsWindow*>(ptr);
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

void Axiom::WindowsWindow::HandleResize()
{
}

void Axiom::WindowsWindow::HandlePaint()
{
}

LRESULT Axiom::WindowsWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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
		return DefWindowProc(m_windowHandle, uMsg, wParam, lParam);
	}

	return TRUE;
}
