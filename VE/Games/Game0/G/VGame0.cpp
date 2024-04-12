#include <Game0/G/VGame0.h>


using namespace VE::Window;
using namespace VE::Graphics;
using namespace VE::Resources;
class GameData0
{
public:
	VWindow* wnd = nullptr;
	VGraphics* ge = nullptr;
	VResourceChief* rc = nullptr;
}self = {};

void G0Start()
{
	////INIT WINDOW
	self.wnd = new VWindow(L"I LOVE C++", 0, 0, VE::VAPI::WINDOWS);
	////INIT GRAPHICS ENGINE
	self.ge = new VGraphics(self.wnd);
	////INIT RESOURCE MANAGER
	self.rc = new VResourceChief();
	///INIT VERTEX SHADER
	VertexShader vs =  self.rc->LoadResourceFromFileAuto(L"..\\..\\..\\Games\\Game0\\Resources\\VertexShader.hlsl", "vsmain");
	///INIT VERTEX SHADER
	FragmentShader fs = self.rc->LoadResourceFromFileAuto(L"..\\..\\..\\Games\\Game0\\Resources\\PixelShader.hlsl", "psmain");

	float tri[9]{
		1, -1, 0, // position 1
		1, 1, 0,// position 2
		1, -1, 0,// position 3
	};

	VertexMesh vtm = tri;

	V_VertexShaderInfo vsI = {};
	vsI.inputLayoutsElementCount = 2;
	V_INPUT_LAYOUT_FORMAT formats[2] =
	{
		//for position
		V_INPUT_LAYOUT_FORMAT::V_INPUT_LAYOUT_FORMAT_R32G32B32_FLOAT,
		//for color
		V_INPUT_LAYOUT_FORMAT::V_INPUT_LAYOUT_FORMAT_R32G32B32_FLOAT
	};
	vsI.inputLayouts = formats;
	vsI.inputLayoutElementNames = new const char* [2] {
		"POSITION","COLOR"
	};
	vsI.vsCode = vs;
	vsI.vtm = vtm;
	self.ge->SetVertexShader(&vsI);
	self.ge->SetFragmentShader(fs);
}

void G0Update()
{
	self.wnd->Update();
	self.ge->ClearScreenColor(1, 0, 0, 1);
	self.ge->Present();
}
