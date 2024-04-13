#include <Game0/G/VGame0.h>


using namespace VE::Window;
using namespace VE::Graphics;
using namespace VE::Resources;
using namespace VE::Input;
class GameData0
{
public:
	VWindow* wnd = nullptr;
	VGraphics* ge = nullptr;
	VResourceChief* rc = nullptr;
	VE::Input::VInput* ipt = nullptr;
}self = {};

void G0Start()
{
	////INIT WINDOW
	self.wnd = new VWindow(L"I LOVE C++",0, 0, VE::VAPI::WINDOWS);
	////INIT GRAPHICS ENGINE
	self.ge = new VGraphics(self.wnd);
	////INIT RESOURCE MANAGER
	self.rc = new VResourceChief();
	////INIT RESOURCE MANAGER
	self.ipt = new VInput();
	///INIT VERTEX SHADER
	VertexShader vs =  self.rc->LoadResourceFromFileAuto(L"..\\..\\..\\Games\\Game0\\Resources\\VertexShader.hlsl", "vsmain");
	///INIT VERTEX SHADER
	FragmentShader fs = self.rc->LoadResourceFromFileAuto(L"..\\..\\..\\Games\\Game0\\Resources\\PixelShader.hlsl", "psmain");

	struct vec3 
	{
		float x, y, z;
	};

	struct Vertex
	{
		vec3 v[3];
	}; 

	Vertex t[3] =
	{
		{-1, -1, 0},
		{0, 1, 0},
		{1, -1, 0}
	};

	V_VertexShaderInfo vsI = {};
	vsI.inputLayoutsElementCount = 1;
	V_INPUT_LAYOUT_FORMAT formats[1] =
	{
		//for position
		V_INPUT_LAYOUT_FORMAT::V_INPUT_LAYOUT_FORMAT_R32G32B32_FLOAT,
	};
	vsI.inputLayouts = formats;
	vsI.inputLayoutElementNames = new const char* [1] {
		"POSITION"
	};
	vsI.vsCode = vs;
	vsI.vtm = t;
	vsI.len_list = 3;
	vsI.size_vertex = sizeof(Vertex);

	self.ge->SetVertexShader(&vsI);
	self.ge->SetFragmentShader(fs);
}

void G0Update()
{
	if (self.ipt->isKey(VKeyCode::_A, VKeyState::Up))
	{
		printf("A");
	}
	if (self.ipt->isKey(VKeyCode::_D, VKeyState::Down))
	{
		printf("D");
	}
	self.wnd->Update();
	self.ge->ClearScreenColor(0, 0, 0, 0);
	self.ge->Present();
}
