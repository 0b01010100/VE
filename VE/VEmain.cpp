#include <Window/VWindow.h>
#include <DefualtLibs/VDebug/VDebug.h>
int main()
{
	//CREATE WINDOWS
	VE::Window::VWindow* w = new VE::Window::VWindow(L"Scene0", 0U, 0U, VE::VAPI::WINDOWS);
	VE::Window::VWindow* w1 = new VE::Window::VWindow(L"Scene1", 300U, 300U, VE::VAPI::WINDOWS);
	VE::VDebuging::VConsole::VLOGf(L"THE ", L"GAME ENGINE");

	//UPDATE WINDOWS
	while (true)
	{
		w->Update();
		w1->Update();

	}

}