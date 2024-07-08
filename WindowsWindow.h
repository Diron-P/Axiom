#ifndef WINDOWS_WINDOW_H
#define WINDOWS_WINDOW_H

#include <windows.h>

namespace Axiom
{
	class WindowsWindow
	{
	public:
		WindowsWindow(HINSTANCE hInstance);
		WindowsWindow(HINSTANCE hInstance, int width, int height);
		void Initialize();

		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		HWND GetHwnd() const { return m_windowHandle; }
		int GetWidth() const { return m_width; }
		int GetHeight() const { return m_height; }

	private:
		void HandleResize();
		void HandlePaint();
		LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

		HWND m_windowHandle;
		HINSTANCE m_instanceHandle;	// TODO - Remove if unnecessary.

		int m_width{ 600 };
		int m_height{ 600 };
	};
}

#endif // !WINDOWS_WINDOW_H