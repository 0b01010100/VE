#include <Game0/G/VGame0.h>
#include <VWindow/VWindow.hpp>
#include <VGraphics/VGraphics.hpp>
#include <VResourceChief/VResourceChief.hpp>
#include <VInput/VInput.h>


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
	VInput* ipt = nullptr;
}self = {};
__declspec(align(16))
struct constant
{
	float x = 0.2;
	float y = 0.2;
	float z = 0.2;
}cc;
void G0Start()
{
	////INIT WINDOW
	self.wnd = new VWindow(L"I LOVE C++",0, 0, VAPI::WINDOWS);
	//////INIT GRAPHICS ENGINE
	self.ge = new VGraphics(self.wnd);
	//////INIT RESOURCE MANAGER
	self.rc = new VResourceChief();
	//////INIT RESOURCE MANAGER
	self.ipt = new VInput();

}

void G0Update()
{

	/////INIT VERTEX SHADER
	VertexShader vs = self.rc->LoadResourceFromFileAuto(L"..\\..\\..\\Games\\Game0\\Resources\\VertexShader.hlsl", "vsmain");
	/////INIT VERTEX SHADER
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
		{-1, -1, 0, 1,1,1},
		{0, 1, 0, 1,1,1},
		{1, -1, 0, 1,1,1}
	};

	V_VertexShaderInfo vsI = {};
	vsI.inputLayoutsElementCount = 2;
	V_INPUT_LAYOUT_FORMAT formats[2] =
	{
		//for position
		V_INPUT_LAYOUT_FORMAT::V_INPUT_LAYOUT_FORMAT_R32G32B32_FLOAT,
		//for color
		V_INPUT_LAYOUT_FORMAT::V_INPUT_LAYOUT_FORMAT_R32G32B32_FLOAT,
	};
	vsI.inputLayouts = formats;
	vsI.inputLayoutElementNames = new const char* [2] {
		"POSITION", "COLOR"
		};
	vsI.vsCode = vs;
	vsI.vtm = t;
	vsI.len_list = 3;
	vsI.size_vertex = sizeof(Vertex);

	vsI.cb = &cc;
	vsI.cbSize = sizeof(constant);

	self.ge->SetVertexShader(&vsI);
	self.ge->SetFragmentShader(fs);
	//get input 
	if (self.ipt->isKey(VKeyCode::_A, VKeyState::Down))
	{
		cc.x -= 0.1;
	}
	if (self.ipt->isKey(VKeyCode::_D, VKeyState::Down))
	{
		cc.x += 0.1;
	}
	if (self.ipt->isKey(VKeyCode::_W, VKeyState::Down))
	{
		cc.y += 0.1;
	}
	if (self.ipt->isKey(VKeyCode::_S, VKeyState::Down))
	{
		cc.y -= 0.1;
	}
	self.wnd->Update();
	self.ge->ClearScreenColor(0, 0, 0, 0);
	self.ge->Present();
}
