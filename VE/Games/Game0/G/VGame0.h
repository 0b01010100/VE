#pragma once
#include <Game0/G/VGame0.h>
#include <VWindow/VWindow.hpp>
#include <VGraphics/VGraphics.hpp>
#include <VInput/VInput.h>
#define Vec3 
#define Mat4x4 
#include <VMath/VMath.h>


using namespace VE::Window;
using namespace VE::Graphics;
using namespace VE::Input;
using namespace VE::VMath;


class Game0
{
public:

	//starts the game
	Game0();

	void Update();

	VWindow* wnd = nullptr;
	VGraphics* ge = nullptr;
	VInput* ipt = nullptr;

	Resources::VMesh Mesh0;
	Resources::VMesh Mesh1;
};
