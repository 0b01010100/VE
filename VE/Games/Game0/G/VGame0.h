#pragma once
#include <Game0/G/VGame0.h>
#include <VWindow/VWindow.hpp>
#include <VGraphics/VGraphics.hpp>
#include <VResourceChief/VResourceChief.hpp>
#include <VInput/VInput.h>

using namespace VE::Window;
using namespace VE::Graphics;
using namespace VE::Resources;
using namespace VE::Input;

class Game0
{
public:

	void Start();

	void Update();

	VWindow* wnd = nullptr;
	VGraphics* ge = nullptr;
	VResourceChief* rc = nullptr;
	VInput* ipt = nullptr;

	Resources::VMesh Mesh0;
	Resources::VMesh Mesh1;
};
