#pragma once
class Entity;
#include <VWindow/VWindow.hpp>
#include <VGraphics/VGraphics.hpp>
#include <VInput/VInput.h>
#include "Entity.h"

using namespace VE::Window;
using namespace VE::Graphics;
using namespace VE::Input;

class Game0
{
public:

	//starts the game
	Game0();

	void Update();

	VWindow* wnd = nullptr;
	VGraphics* ge = nullptr;
	VInput* ipt = nullptr;

	class Entity* entity;
};
