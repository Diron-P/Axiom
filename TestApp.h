#ifndef TEST_APP
#define TEST_APP

#include "BaseWin32Application.h"

namespace Axiom
{
	class TestApp : public BaseWindowsApplication
	{
	public:
		void OnInit() override;
		void OnUpdate() override;
		void OnRender() override;
	};
}

#endif // !TEST_APP
