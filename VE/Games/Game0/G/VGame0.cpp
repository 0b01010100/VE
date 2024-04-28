#include "VGame0.h"
#include <string>
#include <iostream>


struct vec3
{
	float x, y, z;
};

struct Vertex
{
	vec3 pos;
	vec3 color;
};

Vertex tri[3] =
{
	{{-0.5,-0.5,0}, {1,0,0},},
	{{0,0.5,0}, {0,1,0},},
	{{0.5,-0.5,0}, {0,0,1}},
};
Vertex sqr[] =
{
	{{-0.5, 0.5, 0}, {1,0,0} },
	{{0.5, 0.5, 0}, {0,1,0} },
	{{0.5, -0.5, 0}, {0,0,1} },
	{{-0.5, -0.5, 0}, {0,1,0} },
	{{-0.5, 0.5, 0}, {1,0,0} },
};
Vertex index_sqr[4]
{
	{{-0.5, 0.5, 0}, {1,0,1} },
	{{0.5, 0.5, 0}, {1,1,0} },
	{{0.5, -0.5, 0}, {0,1,1} },
	{{-0.5, -0.5, 0}, {1,1,1} },
};

struct Transform
{
	Vmat4x4 world;
	Vmat4x4 view;
	Vmat4x4 proj;
};
__declspec(align(16))
struct constant
{
	Transform transform;
}cc, cc1;

Game0::Game0()
{
	////INIT WINDOW
	wnd = new VWindow(L"I LOVE C++", 300, 300, VAPI::WINDOWS);
	//////INIT GRAPHICS ENGINE
	ge = new VGraphics(wnd);
	//////INI INPUT MANAGER
	ipt = new VInput();


#define arrayItemCount(array) sizeof(array) / sizeof(array[0]);


	int sqrvertexCount = arrayItemCount(index_sqr)

		std::vector<unsigned int> sqrindices = { 0, 1, 2, 0, 2, 3 };


	Vertex* sqr = new Vertex[4]
	{
		{{-0.5, 0.5, 0}, {1,0,1} },//index 0
		{{0.5, 0.5, 0}, {1,1,0} },//index 1
		{{0.5, -0.5, 0}, {0,1,1} },//index 2
		{{-0.5, -0.5, 0}, {1,1,1} },//index 3
	};

	this->Mesh0 = ge->resourceManager->createMesh(sqr, sizeof(Vertex), sqrvertexCount, sqrindices, &cc, sizeof(cc));

	std::vector<unsigned int> null;
	this->Mesh1 = ge->resourceManager->createMesh(tri, sizeof(Vertex), 3, null, &cc1, sizeof(cc1));


}

void Game0::Update()
{
	///INIT VERTEX SHADER
	//VertexShader vs = self.rc->LoadResourceFromFileAuto(L"..\\..\\..\\Games\\Game0\\Resources\\VertexShader.hlsl", "vsmain");
	///INIT VERTEX SHADER
	//FragmentShader fs = self.rc->LoadResourceFromFileAuto(L"..\\..\\..\\Games\\Game0\\Resources\\PixelShader.hlsl", "psmain");
	Vmat4x4 temp;
	Vvec3 temp1;
	//get user input 
	if (ipt->isKey(VKeyCode::_A, VKeyState::Down))
	{
		temp.arr[0][3] -= 0.02;
		std::wstring f = temp.__str__();
		std::wcout << f;
	}
	if (ipt->isKey(VKeyCode::_D, VKeyState::Down))
	{
		temp.arr[0][3] += 0.02;
		std::wstring f = temp.__str__();
		std::wcout << f;
	}
	if (ipt->isKey(VKeyCode::_W, VKeyState::Down))
	{
		temp.arr[1][3] += 0.02;
		std::wstring f = temp.__str__();
		std::wcout << f;
	}
	if (ipt->isKey(VKeyCode::_S, VKeyState::Down))
	{
		temp.arr[1][3] -= 0.02;
		std::wstring f = temp.__str__();
		std::wcout << f;
	}//

	cc.transform.world = cc.transform.world *= temp;
	Vmat4x4 proj;
	VWRect wr = wnd->GetClientWindowRect();
	proj.setOrthoLH(
		((static_cast<float>(wr.right) - wr.left) / 300),
		((static_cast<float>(wr.bottom) - wr.top) / 300),
		-4.0f,
		4.0f
	);
	cc.transform.proj = proj;
	cc1.transform.proj = proj;
	//update window's input system
	wnd->Update();



	//render scene on window 
	ge->ClearScreenColor(0, 0, 0, 0);

	ge->SetMesh(Mesh0);

	ge->SetMesh(Mesh1);

	ge->Present();
}
