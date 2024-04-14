#pragma once
#include "req.h"
// filesystem standard header by MICROSOFT
#include <filesystem>
// filesystem standard header by MICROSOFT
#include <iostream>
// fstream standard header by MICROSOFT
#include <fstream>
// string standard header by MICROSOFT
#include <string>
// sstream standard header by MICROSOFT
#include <sstream>
//allows us to be able to the the d3dcompiler library my MICROSOFT
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")
//allows us to be able to the the d3d11 library 
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
struct DX11Devices
{
	//messages swap chain buffers
	struct IDXGISwapChain* sw;
	//for creation of resources for rendering
	struct ID3D11Device* dev;
	//Used for rendering. This struct has all the fansy function for rendering 
	struct ID3D11DeviceContext* context;
	//allows us to view a swapChain buffer, so we do things like render to it
	struct ID3D11RenderTargetView* rtv;
	/*An IDXGIFactory interface implements methods for generating DXGI objects
	(which handle full screen transitions).*/
	struct IDXGIFactory* factory;
	//For DXGI objects that produce image data.
	struct IDXGIDevice* idxgi_dev;
};
//initialize DirectX 11 Api using hwnd
//@param hwnd -> a generic pointer to a HWND__ data type which is an the id of a window in windows.h. 
//@param hwnd -> a generic pointer to a HIGH LEVEL VERSION OF THE GRAPHICS ENGINE(for example VGraphics from Virtuniy Engine Standard)
//We need this id in order to to tell DX11 what window should be set up with a rendered system

void* DX11_init(void* hwnd, void* graphics);
//////////////////////////////////////////////////RESOURCE MANAGER

// //creates a DX11 swap chain
//@param date -> a pointer to DX11Devices struct, which will represent the DX11 rendering devices and swapChain
//@param hwnd -> a pointer to HWND__ struct, which is an id for a window
//We need this id in order to to tell DX11 what window should have the swapchain Buffers
__declspec(noinline) static void DX11_createSwapChain(struct DX11Devices* rs, HWND hwnd);

//create a Vertex Shader the DX11 way
//@param rs -> a pointer to DX11Devices struct, which will represent the DX11 rendering devices and swapChain
//@param file_path -> location in the project to acces the Vertex in a file
//@param entry_point -> the name of the shader programs;s entry point 
__declspec(noinline) static void* DX11_createVertexShader(void* rs, const wchar_t* file_path, const char* entry_point, VE::Graphics::Resources::VInputLayout* inputLayout);

//create a Pixel Shader the DX11 way
//@param rs -> a pointer to DX11Devices struct, which will represent the DX11 rendering devices and swapChain
//@param file_path -> location in the project to acces the FragmentShader in a file
//@param entry_point -> the name of the shader programs;s entry point 
__declspec(noinline) static void* DX11_createFragmentShader(void* rs, const wchar_t* file_path, const char* entry_point);


//////////////////////////////////////////////////DEVICE CONTEXT


//clears the color of the window
//@param data -> a pointer to DX11Devices
//@param r -> red channel of the buffer color
//@param g -> green channel of the buffer color
//@param b -> blue channel of the buffer color
//@param a -> alpha channel of the buffer color
__declspec(noinline) static void DX11_clearScreenColor(void* rs, float r, float g, float b, float a);

//allows us to present what we drew on the screen
//@param rs -> a pointer to a DX11Devices which will be represented on a hight level as a render system (or rs)
__declspec(noinline) static void DX11_present(void* rs);

//allows us to Set the Vertex Shader to be used in the input assembly stage of rendering 
//@param rs -> a pointer to a DX11Devices which will be represented on a hight level as a render system (or rs)
//@param vertexShaderAttribs -> a generic pointer to VertexShader data (like inputLayout, VertexShader btye Code, And Samatics)
//__declspec(noinline) static void DX11_setVertexShader(void* rs, struct V_VertexShaderInfo* vsInfo);
__declspec(noinline) static void DX11_setVertexShader(void* rs, void* vsCode);

//allows us to Set the Vertex Shader to be used in the input assembly stage of rendering
//@param rs -> a pointer to a DX11Devices which will be represented on a hight level as a render system (or rs)
//@param vs -> a generic pointer to Fagment/Pixel Shader btye code and meta data  
__declspec(noinline) static void DX11_setFragmentShader(void* rs, void* fs);


__declspec(noinline) static void DX11_setMesh(void* rs, VE::Graphics::Resources::VMesh* mesh);

void DX11_uninit(void* rs, void* graphics);

