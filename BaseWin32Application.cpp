#include "BaseWin32Application.h"

BaseWin32Application::BaseWin32Application(HINSTANCE hInstance)
	: window{ hInstance }
{
}

BaseWin32Application::~BaseWin32Application()
{
}

void BaseWin32Application::Run()
{
	MSG msg;
	while (PeekMessage(&msg, window.GetHwnd(), 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);

		OnUpdate();
		OnRender();
	}
}
