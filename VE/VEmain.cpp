#include <d3d11.h>
#include <Window/VWindow.hpp>
#include <Graphics/VGraphics.hpp>
#include <DefualtLibs/VDebug/VDebug.h>
using namespace VE::Window;
using namespace VE::Graphics;
int main()
{	
	//INIT WINDOWS
	VWindow* w = new VWindow(L"Scene", 0L, 0L, VE::VAPI::WINDOWS);
	VWindow* w1 = new VWindow(L"Scene1", 300L, 300L, VE::VAPI::WINDOWS);
	//INIT GRAPHICS ENGINE
	VGraphics* g = new VGraphics(w);
	VGraphics* g1 = new VGraphics(w1);
	//UPDATE WINDOWS AND GRAPHICS ENGINE
	while (true)
	{
		
		w->Update();
		g->ClearScreenColor(1, 1, 0, 0);
		g->Present();

		w1->Update();
		g1->ClearScreenColor(1, 0, 0, 0);
		g1->Present();
	}
	
}