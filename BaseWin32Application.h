#ifndef BASE_WIN32_APPLICATION_H
#define BASE_WIN32_APPLICATION_H

#include "Win32Window.h"

class BaseWin32Application
{
public:
	BaseWin32Application(HINSTANCE hInstance);
	virtual ~BaseWin32Application();

	void Run();

protected:
	virtual void OnInit() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnRender() = 0;

	WindowsWindow window;
};

#endif // !BASE_WIN32_APPLICATION_H
