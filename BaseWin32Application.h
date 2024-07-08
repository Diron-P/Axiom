#ifndef BASE_WIN32_APPLICATION_H
#define BASE_WIN32_APPLICATION_H

#include "WindowsWindow.h"

namespace Axiom
{
	class BaseWindowsApplication
	{
	public:
		BaseWindowsApplication(HINSTANCE hInstance);
		virtual ~BaseWindowsApplication();

		void Run();

	protected:
		virtual void OnInit() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnRender() = 0;

		WindowsWindow* window;
	};
}

#endif // !BASE_WIN32_APPLICATION_H
