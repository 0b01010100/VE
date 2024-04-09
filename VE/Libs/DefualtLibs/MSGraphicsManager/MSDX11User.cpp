#include "MSDX11User.hpp"

static enum D3D_DRIVER_TYPE drivers[] =
{
	//Drawing is mainly Executed to the GPU when using this Driver
	D3D_DRIVER_TYPE_HARDWARE,
	//This is a very fast Driver that has the CPU to do most of the Math to get thing draw on the screen.
	D3D_DRIVER_TYPE_WARP,
	//Compatbale with most DirectX Features, but is pretty slow compared the the First two Drivers.
	D3D_DRIVER_TYPE_REFERENCE
};

void* DX11_init(void* hwnd, void* in_ge_b)
{
	//FAKING INHERITANCE BY REINTERPRET_CASTING 
	struct IGraphicsEngine_Base* ge_b = (struct IGraphicsEngine_Base*)in_ge_b;
	//GIVE THE HIGH LEVEL INTERFACE THE LOW LEVEL FUNCTIONS 
	ge_b->setFragmentShader = DX11_setFragmentShader;
	ge_b->setVertexShader = DX11_setVertexShader;
	ge_b->clearScreenColor = DX11_clearScreenColor;
	ge_b->present = DX11_present;

	struct DX11Devices* rs = (struct DX11Devices*)malloc(sizeof(struct DX11Devices));

	HRESULT hr = { 0 };
	for (unsigned char index = 0; index < ARRAYSIZE(drivers);)
	{
		hr = D3D11CreateDevice(0, drivers[index], 0, 0, 0, 0, D3D11_SDK_VERSION, &rs->dev, 0, &rs->context);
		//if the creation of devices SUCCEEDED exit the loop
		if (SUCCEEDED(hr))
		{
			break;
		}
		index++;
	}
	//check for errors
	DX11_ERROR(hr, "Failed to set up DirectX 11 rendering system");
	//if the creation of devices FAILED throw Error
	DX11_ERROR(hr, L"Faild to get rendering Devices for DirectX 11 ");
	//else continue on, to get IDXGIDevice struct
	DX11_ERROR(rs->dev->QueryInterface(__uuidof(struct IDXGIDevice), (void**)&rs->idxgi_dev), L"Faild to get a rendering Device for DirectX 11. Device is IDXGIDevice");
	
	//Represents your Graphics adapter 
	struct IDXGIAdapter* apdt = 0;

	//else continue on, to get IDXGIAdapter struct
	DX11_ERROR(rs->idxgi_dev->GetAdapter(&apdt), L"Faild to get a rendering Device for DirectX 11. Device is IDXGIAdapter( or Graphics Adapter)");
	//else continue on, to get IDXGIFactory struct
	DX11_ERROR(apdt->GetParent(__uuidof(struct IDXGIFactory), (void**)&rs->factory), L"Faild to get a rendering Device for DirectX 11. Device is IDXGIFactory");
	//now create swapChain
	DX11_createSwapChain(rs, (HWND)hwnd);

	return rs;
}

__declspec(noinline) static
void DX11_createSwapChain(struct DX11Devices* rs, HWND hwnd)
{
	DXGI_SWAP_CHAIN_DESC sw_desc = { 0 };
	sw_desc.BufferCount = 1;// one extrax buffer so two will be used. 

	//Get client size of the window 
	RECT wr = { 0 };
	GetClientRect(hwnd, &wr);
	//Adjust the Width of the window based on the Width of the client of the window 
	sw_desc.BufferDesc.Width = wr.right - wr.left;
	//Adjust the Height of the window based on the Height of the client of the window 
	sw_desc.BufferDesc.Height = wr.bottom - wr.top;
	//Set window to present frame buffers on
	sw_desc.OutputWindow = hwnd;
	//Yes output should be in windowed mode. 
	sw_desc.Windowed = 1;//true
	//Allows us to change the size of the swapchain buffer and swicth from Windowed mode to another mode
	sw_desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	//How to format the color channels of each the pixel 
	sw_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//Setting RefreshRate
	DXGI_RATIONAL RefreshRate = { 10U, 0U };
	sw_desc.BufferDesc.RefreshRate = RefreshRate;
	//How well to sample colors from a texture on to each pixel
	DXGI_SAMPLE_DESC SampleDesc = { 1U, 0U };
	sw_desc.SampleDesc = SampleDesc;
	//Yes the buffer will be used a Render target view to draw on them 
	sw_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//discard the contents of the back buffer after we call IDXGISwapChain::Present.
	sw_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	//finally try to create swap Chain and do Error checking to make sure creation was ok
	DX11_ERROR(rs->factory->CreateSwapChain
	(
		rs->dev,
		&sw_desc,
		&rs->sw
	), L"Faild to Create SwapChain for DirectX 11 in Win32SwapChain class\n");

	//get 1 Buffer/Texture from the swapChain view
	struct ID3D11Texture2D* TEX = 0;
	DX11_ERROR
	(
		rs->sw->GetBuffer(0,
		__uuidof(struct ID3D11Texture2D),
		(void**)&TEX
	), L"Faild to get a buffer from the swap chain in Win32SwapChain class\n");

	//create render target view and give it the TEX variable, so we can draw to the Buffer/Texture
	DX11_ERROR
	(
		rs->dev->CreateRenderTargetView(
		TEX,
		0,
		&rs->rtv
		), L"Faild to create render target view in Win32SwapChain class");

	//Release ref to resource when done using it
	TEX->Release();
}
__declspec(noinline) static
void DX11_clearScreenColor(void* rs, float r, float g, float b, float a)
{
	struct DX11Devices* s = (struct DX11Devices*)rs;
	float color[4] = { r,g,b,a };
	//clear the color of the wholl render target to the color reprsented as [r] [g] [b] [a]
	s->context->ClearRenderTargetView(s->rtv, color);
}
__declspec(noinline) static
void DX11_present(void* rs) 
{
	struct DX11Devices* s = (struct DX11Devices*)rs;
	//present to make make the render target seeable to human eyes
	s->sw->Present(1, 0);
}
__declspec(noinline) static
void DX11_setVertexShader(void* rs, void* vs) 
{
	struct DX11Devices* s = (struct DX11Devices*)rs;
	struct ID3D10Blob* shaderCode = (struct ID3D10Blob*)vs;
	struct ID3D11VertexShader* outVertexShader = __nullptr;
	//use the byte code to create a DX11 vertex shader 
	s->dev->CreateVertexShader(shaderCode->GetBufferPointer(), shaderCode->GetBufferSize(), 0, &outVertexShader);
	//Set the Vertex Shader to be used in the input assembly stage of rendering 
	s->context->VSSetShader(outVertexShader, 0, 0);
}
__declspec(noinline) static
void DX11_setFragmentShader(void* rs, void* fs)
{
	struct DX11Devices* s = (struct DX11Devices*)rs;
	struct ID3D10Blob* shaderCode = (struct ID3D10Blob*)fs;
	struct ID3D11PixelShader* outPixelShader = __nullptr;
	//use the byte code to create a DX11 pixel shader 
	s->dev->CreatePixelShader(shaderCode->GetBufferPointer(), shaderCode->GetBufferSize(), 0, &outPixelShader);
	//Set the Pixel Shader to be used in the input assembly stage of rendering 
	s->context->PSSetShader(outPixelShader, 0, 0);
}
