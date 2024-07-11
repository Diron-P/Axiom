#include "TestApp.h"

using namespace Axiom;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	// Refactor the BaseWin32Application class so that it works without passing an instance handle to it.
	TestApp app(hInstance);
	app.Run();

    return 0;
}