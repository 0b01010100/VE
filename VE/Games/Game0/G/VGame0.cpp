#include "VGame0.h"

__declspec(align(16))
struct constant
{
	float x = 0;
	float y = 0;
	float z = 0;
}cc, cc1;

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
template<class T, class ...Arg> 
T* New(Arg... args)
{
	return new T(args);
}
void Game0::Start()
{
	////INIT WINDOW
	wnd = new VWindow(L"I LOVE C++", 0, 0, VAPI::WINDOWS);
	//////INIT GRAPHICS ENGINE
	ge = new VGraphics(wnd);
	//////INIT RESOURCE MANAGER
	rc = new VResourceChief();
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

	//get user input 
	if (ipt->isKey(VKeyCode::_A, VKeyState::Down))
	{
		cc.x -= 0.02;
	}
	if (ipt->isKey(VKeyCode::_D, VKeyState::Down))
	{
		cc.x += 0.02;
	}
	if (ipt->isKey(VKeyCode::_W, VKeyState::Down))
	{
		cc.y += 0.02;
	}
	if (ipt->isKey(VKeyCode::_S, VKeyState::Down))
	{
		cc.y -= 0.02;
	}

	//update window's input system
	wnd->Update();

	//render scene on window 
	ge->ClearScreenColor(0, 1, 0, 0);

	ge->SetMesh(Mesh0);

	ge->SetMesh(Mesh1);

	ge->Present();
}
