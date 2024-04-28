#include "Entity.h"

Entity::Entity()
{
}

Entity::Entity(Game0* game)
{
	this->game = game;

	#define arrayItemCount(array) sizeof(array) / sizeof(array[0]);


	int sqrvertexCount = arrayItemCount(VE::Math::Shapes::indexSqr);

	std::vector<unsigned int> sqrindices = { 0, 1, 2, 0, 2, 3 };
	
	Vmat4x4 mat;
	mat.setScale(1.f, 1.f, 1.f);
	transform.world = transform.world * mat;
	mat.setPosition(-0.5f, 0.f, 0.f);
	transform.world = transform.world * mat;
	mat.setRotationZd(20.f);
	transform.world = transform.world * mat;
	this->Mesh0 = game->ge->resourceManager->createMesh(VE::Math::Shapes::indexSqr, sizeof(Vvertex), sqrvertexCount, sqrindices, &transform, sizeof(transform));

}


void Entity::Update()
{
	Vmat4x4 temp;
	Vvec3 temp1;
	//get user input 
	if (game->ipt->isKey(VKeyCode::_A, VKeyState::Down))
	{
		temp.arr[0][3] -= 0.02;

	}
	if (game->ipt->isKey(VKeyCode::_D, VKeyState::Down))
	{
		temp.arr[0][3] += 0.02;

	}
	if (game->ipt->isKey(VKeyCode::_W, VKeyState::Down))
	{
		temp.arr[1][3] += 0.02;
	
	}
	if (game->ipt->isKey(VKeyCode::_S, VKeyState::Down))
	{
		temp.arr[1][3] -= 0.02;


	}

	Vmat4x4 proj;
	Vmat4x4 view;
	VWRect wr = game->wnd->GetClientWindowRect();
	proj.setOrthoLH(
		((static_cast<float>(wr.right) - wr.left) / 300),
		((static_cast<float>(wr.bottom) - wr.top) / 300),
		-4.0f,
		4.0f
	);
	transform.view = view;
	
	transform.world = transform.world * temp;
	transform.proj = proj;
	printf("%ws", transform.world.__str__().c_str());
	this->game->ge->SetMesh(Mesh0);

}
