#include "VGame0.h"
#include <string>
#include <iostream>

Game0::Game0()
{
	////INIT WINDOW
	wnd = new VWindow(L"Scene", 300, 300, VAPI::WINDOWS);
	//////INIT GRAPHICS ENGINE
	ge = new VGraphics(wnd);
	//////INIT INPUT MANAGER
	ipt = new VInput();

	entity = new Entity(this);

}

void Game0::Update()
{
	//update window's input system
	wnd->Update();
	
	//render scene on window 
	ge->ClearScreenColor(0, 0, 0, 0);
	entity->Update();
	ge->Present();
}
