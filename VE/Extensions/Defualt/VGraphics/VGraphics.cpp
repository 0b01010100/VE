#include "VGraphics.hpp"
#include<stdio.h>
VE::Graphics::VGraphics::VGraphics(class VE::Window::VWindow* wnd)
{
	this->wnds = wnd;
	switch (wnd->renderingApi)
	{
#ifdef _WIN32
	case VE::Window::VAPI::WINDOWS:
			this->renderSystem = DX11_init(wnd->phwnd, this);
			break;
#endif
		case  VE::Window::VAPI::OGL:
			break;

		case  VE::Window::VAPI::VULKAN:
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

void VE::Graphics::VGraphics::SetFragmentShader(void* fs)
{
	this->setFragmentShader(this->renderSystem, fs);
}

void VE::Graphics::VGraphics::SetVertexShader(struct V_VertexShaderInfo* vsInfo)
{
	this->setVertexShader(this->renderSystem, vsInfo);
}
void VE::Graphics::VGraphics::ClearScreenColor(float r, float g, float b, float a)
{
	this->clearScreenColor(this->renderSystem, r, g, b, a);
}

void VE::Graphics::VGraphics::Present()
{
	this->present(this->renderSystem);
}



