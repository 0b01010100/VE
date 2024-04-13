#include "MSDX11User.hpp"
//Used for Error Handling related to windows only.
#define DX11_ERROR(hr, error, retvalue)\
{\
	if(FAILED(hr)){\
		std::wstringstream ws; \
		ws << L"DX11 ERROR \n" << error<< L"\n"<< L"Error Code: " << hr << "\n"; \
		OutputDebugStringW(ws.str().c_str()); \
		MessageBoxW(0, ws.str().c_str(), L"DX11 ERROR" , 0);\
		retvalue;\
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
#define NULL_ERROR(arg, error, retvalue)\
{\
	if(arg == 0){\
		std::wostringstream ws; \
		ws << error<< L"\n"; \
		OutputDebugStringW(ws.str().c_str()); \
		MessageBoxW(0, ws.str().c_str(), L"NULL_ERROR" , 0);\
		retvalue;\
	}\
}
static enum D3D_DRIVER_TYPE drivers[] =
{
	//Drawing is mainly Executed to the GPU when using this Driver
	D3D_DRIVER_TYPE_HARDWARE,
	//This is a very fast Driver that has the CPU to do most of the Math to get thing draw on the screen.
	D3D_DRIVER_TYPE_WARP,
	//Compatbale with most DirectX Features, but is pretty slow compared the the First two Drivers.
	D3D_DRIVER_TYPE_REFERENCE
};

struct IGraphicsEngine
{
	//will a set a Pixel/Fragment shader for the render system to use 
	void(*setFragmentShader);
	//will a set a Vertex shader for the render system to use 
	void(*setVertexShader);
	//will clear the color of the texture to a given color
	void(*clearScreenColor);
	//will present what was draw on the render texture so we can see it 
	void(*present);
};
void* DX11_init(void* hwnd, void* graphics)
{
	//FAKING INHERITANCE BY REINTERPRET_CASTING 
	IGraphicsEngine* ge_b = reinterpret_cast<IGraphicsEngine*>(graphics);

	//GIVE THE HIGH LEVEL INTERFACE THE LOW LEVEL FUNCTIONS 
	ge_b->setFragmentShader = DX11_setFragmentShader;
	ge_b->setVertexShader = DX11_setVertexShader;
	ge_b->clearScreenColor = DX11_clearScreenColor;
	ge_b->present = DX11_present;

	struct DX11Devices* rs = reinterpret_cast<DX11Devices*>(malloc(sizeof(struct DX11Devices)));

	HRESULT hr;
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
	DX11_ERROR(hr, "Failed to set up DirectX 11 rendering system", return 0);
	//if the creation of devices FAILED throw Error
	DX11_ERROR(hr, L"Faild to get rendering Devices for DirectX 11 ", return 0);
	//else continue on, to get IDXGIDevice struct
	DX11_ERROR(rs->dev->QueryInterface(__uuidof(struct IDXGIDevice), reinterpret_cast<void**>(&rs->idxgi_dev)), L"Faild to get a rendering Device for DirectX 11. Device is IDXGIDevice", return 0);
	
	//Represents your Graphics adapter 
	struct IDXGIAdapter* apdt = __nullptr;

	//else continue on, to get IDXGIAdapter struct
	DX11_ERROR(rs->idxgi_dev->GetAdapter(&apdt), L"Faild to get a rendering Device for DirectX 11. Device is IDXGIAdapter( or Graphics Adapter)", return 0);
	//else continue on, to get IDXGIFactory struct
	DX11_ERROR(apdt->GetParent(__uuidof(struct IDXGIFactory), reinterpret_cast<void**>(&rs->factory)), L"Faild to get a rendering Device for DirectX 11. Device is IDXGIFactory", return 0);
	//now create swapChain
	DX11_createSwapChain(rs, reinterpret_cast<HWND>(hwnd));

	return rs;
}
__declspec(noinline) static
void DX11_createSwapChain(struct DX11Devices* rs, HWND hwnd)
{
	DXGI_SWAP_CHAIN_DESC sw_desc = { 0 };
	sw_desc.BufferCount = 1U;// one extrax buffer so two will be used. 

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
	), L"Faild to Create SwapChain for DirectX 11 in Win32SwapChain class\n", return);

	//get 1 Buffer/Texture from the swapChain
	struct ID3D11Texture2D* TEX = __nullptr;
	DX11_ERROR
	(
		rs->sw->GetBuffer(0U,
		__uuidof(struct ID3D11Texture2D),
		reinterpret_cast<void**>(&TEX)
	), L"Faild to get a buffer from the swap chain in Win32SwapChain class\n", return);

	//create render target view and give it the TEX variable, so we can draw to the Buffer/Texture
	DX11_ERROR
	(
		rs->dev->CreateRenderTargetView(
		TEX,
		__nullptr,
		&rs->rtv
		), L"Faild to create render target view in Win32SwapChain class", return);
	D3D11_VIEWPORT vp = { 0 };
	vp.Width = wr.right - wr.left;
	vp.Height = wr.bottom - wr.top;
	vp.MinDepth = 0b0;
	vp.MaxDepth = 0b1;
	rs->context->RSSetViewports(1, &vp);
	//Release ref to resource when done using it
	TEX->Release();
}
__declspec(noinline) static
void DX11_clearScreenColor(void* rs, float r, float g, float b, float a)
{
	struct DX11Devices* s = reinterpret_cast<struct DX11Devices*>(rs);
	float color[4U] = { r,g,b,a };
	//clear the color of the wholl render target to the color reprsented as [r] [g] [b] [a]
	s->context->ClearRenderTargetView(s->rtv, color);
	s->context->OMSetRenderTargets(1, &s->rtv, 0);
}
__declspec(noinline) static
void DX11_present(void* rs) 
{
	struct DX11Devices* s = reinterpret_cast<struct DX11Devices*>(rs);
	
	s->context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	s->context->Draw(3, 0);
	//present to make make the render target seeable to human eyes
	s->sw->Present(1U, 0U);
}
__declspec(noinline) static
void DX11_setVertexShader(void* rs, struct V_VertexShaderInfo* vsInfo)
{
	struct DX11Devices* s = reinterpret_cast<struct DX11Devices*>(rs);

	//CREATE VERTEX SHADER
	struct ID3D10Blob* shaderCode = reinterpret_cast<ID3D10Blob*>(vsInfo->vsCode);
	NULL_ERROR(shaderCode, "Failed to set succesfully vertex shader for use. Your vertex Shader was null. Check your V_VertexShaderInfo struct", return);
	struct ID3D11VertexShader* outVertexShader = __nullptr;
	//use the byte code to create a DX11 vertex shader 
	DX11_ERROR(s->dev->CreateVertexShader(shaderCode->GetBufferPointer(), shaderCode->GetBufferSize(), 0L, &outVertexShader), "Failed to set succesfully vertex shader for use. Check your shader code", return);
	NULL_ERROR(outVertexShader, "Failed to set succesfully vertex shader for use. Check your V_VertexShaderInfo struct and or your vertex shader code", return);
	//Set the Vertex Shader to be used in the input assembly stage of rendering 
	s->context->VSSetShader(outVertexShader, __nullptr, 0U);
	
	//CREATE VERTEX BUFFER
	D3D11_BUFFER_DESC desc = { 0 };
	//Size of the data 
	desc.ByteWidth = vsInfo->size_vertex * vsInfo->len_list;
	//the resource will be read and wirten to by the GPU
	desc.Usage = D3D11_USAGE_DEFAULT;
	//Bind to Input l Assembly as a Vertex buffer
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//0 for no CPU access is necessary
	desc.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA srd = 
	{
		vsInfo->vtm,
		0U,
		0U
	};
	ID3D11Buffer* vertexBuffer = __nullptr;
	DX11_ERROR(s->dev->CreateBuffer(&desc, &srd, &vertexBuffer), "Failed to set succesfully vertex shader for use. Check your V_VertexShaderInfo struct's Vertex Mesh data", return);
	unsigned int stride = vsInfo->size_vertex;
	unsigned int offset = 0b0U;
	s->context->IASetVertexBuffers(0U, 1U, &vertexBuffer, &stride, &offset);

	//SET UP INPUT LAYOUT 
	//DXGI_FORMAT_R32G32B32A32_FLOAT = 2U 
	//DXGI_FORMAT_R32G32B32_FLOAT = 6U 
	//DXGI_FORMAT_R32G32_FLOAT = 16U 		
	unsigned int AlignedByteOffset = 0U;
	if (vsInfo->inputLayoutsElementCount != 0U) 
	{
		struct D3D11_INPUT_ELEMENT_DESC* desc = reinterpret_cast<struct D3D11_INPUT_ELEMENT_DESC*>(malloc(sizeof(struct D3D11_INPUT_ELEMENT_DESC) * vsInfo->inputLayoutsElementCount));
		//init the memory to zero
		ZeroMemory(desc, sizeof(struct D3D11_INPUT_ELEMENT_DESC) * vsInfo->inputLayoutsElementCount);

		for (int i = 0; i < vsInfo->inputLayoutsElementCount;)
		{
			if (vsInfo->inputLayouts[i] >= 2U && vsInfo->inputLayouts[i] <= 4U)
			{
				desc[i].Format = static_cast<DXGI_FORMAT>(vsInfo->inputLayouts[i]);
				desc[i].AlignedByteOffset = AlignedByteOffset;
				//Size of (unsigned int, int, or float) = sizeof(int), amount of them used = 4
				AlignedByteOffset += static_cast<unsigned int>(sizeof(int) * 4ULL);
			}
			else if (vsInfo->inputLayouts[i] >= 6U && vsInfo->inputLayouts[i] <= 8U)
			{
				desc[i].Format = static_cast<DXGI_FORMAT>(vsInfo->inputLayouts[i]);
				desc[i].AlignedByteOffset = AlignedByteOffset;
				//Size of (unsigned int, int, or float) = sizeof(int), amount of them used = 3
				AlignedByteOffset += static_cast<unsigned int>(sizeof(int) * 3ULL);
			}
			else if (vsInfo->inputLayouts[i] >= 16U && vsInfo->inputLayouts[i] <= 18U)
			{
				desc[i].Format = static_cast<DXGI_FORMAT>(vsInfo->inputLayouts[i]);
				desc[i].AlignedByteOffset = AlignedByteOffset;
				//Size of (unsigned int, int, or float) = sizeof(int), amount of them used = 2
				AlignedByteOffset += static_cast<unsigned int>(sizeof(int) * 2ULL);
			}
			desc[i].SemanticName = vsInfo->inputLayoutElementNames[i];

			i++;
		}
		//create DX11 InputLayout using non Api specific input Layout
		ID3D11InputLayout* input_layout = __nullptr;
		DX11_ERROR(s->dev->CreateInputLayout(desc, vsInfo->inputLayoutsElementCount, shaderCode->GetBufferPointer(), shaderCode->GetBufferSize(), &input_layout), "Failed to fully set vertex shader for use. Check your V_VertexShaderInfo struct's input layout and or your vertex shader code", return);
		NULL_ERROR(outVertexShader, "Failed to fully set vertex shader for use. Check your V_VertexShaderInfo struct's input layout and or your vertex shader code", return);


		//release allocated memory
		free(desc);
		if (input_layout) {
			s->context->IASetInputLayout(input_layout);
			input_layout->Release();
		}
	}
	
	//CREATE CONSTANT BUFFER
	if (vsInfo->cbSize != 0U)
	{
		D3D11_BUFFER_DESC desc = { 0 };
		//Size of the data 
		desc.ByteWidth = vsInfo->cbSize;
		//the resource will be read and wirten to by the GPU
		desc.Usage = D3D11_USAGE_DEFAULT;
		//Bind to Input l Assembly as a Vertex buffer
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		//0 for no CPU access is necessary
		desc.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA srd =
		{
			vsInfo->cb,
			0U,
			0U
		};
		ID3D11Buffer* constantBuffer = __nullptr;
		DX11_ERROR(s->dev->CreateBuffer(&desc, &srd, &constantBuffer), "Failed to set succesfully constant buffer for vertex shader. Check your V_VertexShaderInfo struct's cb and csSize data", return);
		s->context->VSSetConstantBuffers(0U, 1U, &constantBuffer);
	}
}
__declspec(noinline) static
void DX11_setFragmentShader(void* rs, void* fs)
{
	struct DX11Devices* s = reinterpret_cast<struct DX11Devices*>(rs);
	struct ID3D10Blob* shaderCode = reinterpret_cast<struct ID3D10Blob*>(fs);
	struct ID3D11PixelShader* outPixelShader = __nullptr;
	//use the byte code to create a DX11 pixel shader 
	s->dev->CreatePixelShader(shaderCode->GetBufferPointer(), shaderCode->GetBufferSize(), 0L, &outPixelShader);
	//Set the Pixel Shader to be used in the input assembly stage of rendering 
	s->context->PSSetShader(outPixelShader, 0, 0U);
}