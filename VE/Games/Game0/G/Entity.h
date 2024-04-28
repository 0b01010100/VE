#pragma once
class Game0;
#include <VGraphics/VGraphics.hpp>
#define _Vec3 
#define _Mat4x4 
#define _Vertex 
#include <VMath/VMath.h>
#include "VGame0.h"
using namespace VE::Graphics;
using namespace VE::Math;

__declspec(align(16))
static struct Transform
{
	Vmat4x4 world;
	Vmat4x4 view;
	Vmat4x4 proj;
};
class Entity
{
public:
	Entity();
	Entity(class Game0* game);
	void Update();
	Resources::VMesh Mesh0;
	class Game0* game;
	Transform transform;
};