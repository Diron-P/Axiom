#ifndef TEST_APP
#define TEST_APP

#include "BaseWin32Application.h"
#include "D3D11GHI.h"

namespace Axiom
{
	class TestApp : public BaseWindowsApplication
	{
	public:
		TestApp(HINSTANCE hInstance);

		void OnInit() override;
		void OnUpdate() override;
		void OnRender() override;

		D3D11GHI gdi;
	};
}

#endif // !TEST_APP
