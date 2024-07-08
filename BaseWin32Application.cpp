#include "BaseWin32Application.h"

Axiom::BaseWindowsApplication::BaseWindowsApplication(HINSTANCE hInstance)
	: window{ new WindowsWindow(hInstance) }
{
}

Axiom::BaseWindowsApplication::~BaseWindowsApplication()
{
	if (window)
	{
		delete window;
	}
}

void Axiom::BaseWindowsApplication::Run()
{
	MSG msg;
	while (PeekMessage(&msg, window->GetHwnd(), 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);

		OnUpdate();
		OnRender();
	}
}
