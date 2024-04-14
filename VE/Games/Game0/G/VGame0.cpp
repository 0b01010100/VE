#include "VGame0.h"
#include "VGame0.h"
__declspec(align(16))
struct constant
{
	float x = 0;
	float y = 0;
	float z = 0;
}cc;

struct vec3
{
	float x, y, z;
};

struct Vertex
{
	vec3 pos;
	vec3 color;
};

Vertex t[3] =
{
		{-1, -1, 0, 1,.2,1},
		{0, 1, 0, .7,1,.5},
		{1, -1, 0, 0.1,1,.6}
};

void Game0::Start()
{
	////INIT WINDOW
	wnd = new VWindow(L"I LOVE C++", 0, 0, VAPI::WINDOWS);
	//////INIT GRAPHICS ENGINE
	ge = new VGraphics(wnd);
	//////INIT RESOURCE MANAGER
	rc = new VResourceChief();
	//////INIT RESOURCE MANAGER
	ipt = new VInput();

	tri.vertexCount = 3;
	tri.vertexSize = sizeof(Vertex);
	tri.verties = &t;
	tri.cb = &cc;
	tri.cbSize = sizeof(cc);
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
		cc.x -= 0.1;
	}
	if (ipt->isKey(VKeyCode::_D, VKeyState::Down))
	{
		cc.x += 0.1;
	}
	if (ipt->isKey(VKeyCode::_W, VKeyState::Down))
	{
		cc.y += 0.1;
	}
	if (ipt->isKey(VKeyCode::_S, VKeyState::Down))
	{
		cc.y -= 0.1;
	}

	wnd->Update();
	ge->ClearScreenColor(0, 1, 0, 0);


	ge->SetMesh(&tri);


	ge->Present();
}
