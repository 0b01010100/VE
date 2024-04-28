#pragma once
#include "../VGame0.h"
#include <VGraphics/VGraphics.hpp>

__declspec(align(16))
struct Transform
{
	VE::Math::Vmat4x4 world;
	VE::Math::Vmat4x4 view;
	VE::Math::Vmat4x4 proj;
};
class EEntity
{

public:
	EEntity();
	EEntity(class Game0* game);
	void Update();
	class VE::Graphics::Resources::VMesh Mesh0;
	class Game0* game;
	struct Transform transform;
};