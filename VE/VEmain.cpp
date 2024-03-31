#include <d3d11.h>
#include <Window/VWindow.hpp>
#include <DefualtLibs/VDebug/VDebug.h>
using namespace VE::Window;
int main()
{	
	VWindow* w = new VWindow(L"Scene0", 0L, 0L, VE::VAPI::WINDOWS);
	VWindow* w1 = new VWindow(L"Scene1", 300L, 300L, VE::VAPI::WINDOWS);
	VE::VDebuging::VConsole::VLOGf("EVERY THING WENT ", "WELL");
	//UPDATE WINDOWS
	while (true)
	{
		w->Update();
		w1->Update();

	}
	
}