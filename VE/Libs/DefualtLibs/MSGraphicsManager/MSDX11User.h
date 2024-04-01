#pragma once
#include <d3d11.h>
//allows us to be able to the the d3d11 library 
#pragma comment(lib, "d3d11.lib")
struct DX11Devices
{
	//messages swap chain buffers
	IDXGISwapChain* sw;
	//for creation of resources for rendering
	ID3D11Device* dev;
	//Used for rendering. This struct has all the fansy function for rendering 
	ID3D11DeviceContext* context;
	//allows us to view a swapChain buffer, so we do things like render to it
	ID3D11RenderTargetView* rtv;
	/*An IDXGIFactory interface implements methods for generating DXGI objects
	(which handle full screen transitions).*/
	IDXGIFactory* factory;
	//For DXGI objects that produce image data.
	IDXGIDevice* idxgi_dev;
};
//initialize DirectX 11 Api using hwnd
//@param hwnd -> a generic pointer to a HWND__ data type which is an the id of a window in windows.h. 
//We need this id in order to to tell DX11 what window should be set up with a rendered system
void* initDX11(void* hwnd);

//creates a DX11 swap chain
//@param date -> a pointer to DX11Devices struct, which will represent the DX11 rendering devices and swapChain
//@param hwnd -> a pointer to HWND__ struct, which is an id for a window
//We need this id in order to to tell DX11 what window should have the swapchain Buffers
__declspec(noinline) void DX11_createSwapChain(DX11Devices* rs, HWND hwnd);


//clears the color of the window
//@param data -> a pointer to DX11Devices
//@param r -> red channel of the buffer color
//@param g -> green channel of the buffer color
//@param b -> blue channel of the buffer color
//@param a -> alpha channel of the buffer color
__declspec(noinline) void DX11_clearScreenColor(void* rs, float r, float g, float b, float a);

//allows us to present what we drew on the screen
//@param rs -> a pointer to a DX11Devices which will be represented on a hight level as a render system (or rs)
void DX11_present(void* rs);
#include<string>
#include <sstream>
//Used for Error Handling related to windows only.
#define DX11_ERROR(hr, error)\
{\
	if(FAILED(hr)){\
		std::wstringstream ws; \
		ws << L"DX11 ERROR \n" << error<< L"\n"<< L"Error Code: " << hr << "\n"; \
		OutputDebugStringW(ws.str().c_str()); \
		MessageBoxW(0, ws.str().c_str(), L"DX11 ERROR" , 0);\
		\
	}\
\
}
//Used for warrning Handling related to windows only.
#define DX11_WARNING(expr,err_code, details)\
{\
	if(expr != 0){\
		std::wstringstream ws; \
		ws << L"DX11 WARNING \n" << details << "\n" << L"Error Code: " << err_code << "\n"; \
		OutputDebugStringW(ws.str().c_str()); \
		MessageBoxW(0, ws.str().c_str(), L"DX11 WARNING" , 0);\
	}\
\
}

#include <assert.h>
//Assert if value is null
#define NULL_ERROR(arg, error)\
{\
	if(arg == 0){\
		std::wostringstream ws; \
		ws << error<< L"\n"; \
		OutputDebugStringW(ws.str().c_str()); \
		MessageBoxW(0, ws.str().c_str(), L"NULL_ERROR" , 0);\
	}\
}