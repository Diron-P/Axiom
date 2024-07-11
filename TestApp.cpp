#include "TestApp.h"

Axiom::TestApp::TestApp(HINSTANCE hInstance)
	: BaseWindowsApplication{ hInstance }
	, gdi{ window }
{
}

void Axiom::TestApp::OnInit()
{
}

void Axiom::TestApp::OnUpdate()
{
}

void Axiom::TestApp::OnRender()
{
	gdi.Render();
}
