#include "VGraphics.hpp"
#include <VGraphics/MSGraphicsManager/MSDX11.hpp>
#include<stdio.h>

VE::Graphics::VGraphics::VGraphics(void* WindowHandle, unsigned int RenderingApi)
{
	resourceManager = new VGraphicsResourceChief(); 
	this->WindowHandle = WindowHandle;
	this->RenderingApi = RenderingApi;
	switch (RenderingApi)
	{
#ifdef _WIN32
	case 0 : //VE::Window::VAPI::WINDOWS:
			this->renderSystem = DX11_init(WindowHandle, this);
			break;
#endif
	case  1: //VE::Window::VAPI::OGL:
			break;

	case 2:// VE::Window::VAPI::VULKAN:
			break;

		default:
			break;
	}
	//check if phwnd in nullptr if so there was a problem creating the window
	if (renderSystem == nullptr)
	{
		printf("VGraphics creation didn't go so well in File: %ls", __FILEW__);
	}

}
VE::Graphics::VGraphics::~VGraphics()
{
	DX11_uninit(this->renderSystem, this);
}
void VE::Graphics::VGraphics::SetFragmentShader(void* fs)
{
	this->setFragmentShader(this->renderSystem, fs);
}
void VE::Graphics::VGraphics::SetVertexShader(void* vs)
{
	this->setVertexShader(this->renderSystem, vs);
}
void VE::Graphics::VGraphics::SetMesh(VE::Graphics::Resources::VMesh mesh)
{
	this->setMesh(this->renderSystem, mesh);
}
void VE::Graphics::VGraphics::ClearScreenColor(float r, float g, float b, float a)
{
	this->clearScreenColor(this->renderSystem, r, g, b, a);
}
void VE::Graphics::VGraphics::Present()
{
	this->present(this->renderSystem);
}

unsigned int VE::Graphics::VGraphics::GetRenderingAPi() const noexcept
{
	return this->RenderingApi;
}



