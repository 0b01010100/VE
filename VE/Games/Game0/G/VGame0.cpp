#include "VGame0.h"
#include <string>
#include <iostream>
#include "Entity/ESqr.h"
#include "Entity/EEntity.h"

Game0::Game0()
{
	////INIT WINDOW
	wnd = new VWindow(L"Scene", 0, 0, VAPI::WINDOWS);
	//////INIT GRAPHICS ENGINE
	ge = new VGraphics(wnd->GetWindowHandle(), wnd->GetRenderingApi());
	//////INIT INPUT MANAGER
	ipt = new VInput();
	//////INIT ENTITY
	entity = new ESqr(this);

	
}

void Game0::Update()
{
	//update window's input system
	wnd->Update();
	
	//render scene on window and update Entity
	ge->ClearScreenColor(0, 0, 0, 0);

	entity->Update();

	ge->Present();
}
