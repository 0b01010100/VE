#include "ESqr.h"
#include "../VGame0.h"
ESqr::ESqr(class Game0 * game) : EEntity(game)
{
	#define arrayItemCount(array) sizeof(array) / sizeof(array[0]);

	using namespace VE::Math::Primitives;
	int sqrvertexCount = arrayItemCount(INDEXED_SQUARE);

	Vmat4x4 mat;
	transform.world.setIdentity();
	mat.setIdentity();
	mat.setRotationZr(4.3);
	transform.world = transform.world * mat;
	mat.setIdentity();
	mat.setScale(.10f, 1.f, 1.f);	
	mat.setPosition(-0.5f, 0.f, 0.f);
	transform.world = transform.world * mat;
	
	this->Mesh0 = game->ge->resourceManager->createMesh(INDEXED_SQUARE, sizeof(Vvertex), sqrvertexCount, INDEXED_SQUARE_INDIES, 6, &transform, sizeof(transform));
}

void ESqr::Update()
{
	Vmat4x4 temp;
	temp.setIdentity();
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
	view.setIdentity();
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
	printf("%ws", transform.world.getPosition().__str__().c_str());

	this->game->ge->SetMesh(Mesh0);
}
