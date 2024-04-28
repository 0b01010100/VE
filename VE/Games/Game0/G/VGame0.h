#pragma once
class EEntity;
class ESqr;
#include <VWindow/VWindow.hpp>
#include <VGraphics/VGraphics.hpp>
#include <VInput/VInput.h>
#define _Vec3 
#define _Mat4x4 
#define _Vertex 
#include <VMath/VMath.h>

using namespace VE::Window;
using namespace VE::Graphics;
using namespace VE::Input;
using namespace VE::Math;

class Game0
{
public:

	//starts the game
	Game0();

	void Update();

	class VWindow* wnd = nullptr;
	class VGraphics* ge = nullptr;
	class VInput* ipt = nullptr;

	class ESqr* entity;
};
