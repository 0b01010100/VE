#include "VGraphics.hpp"
#include <preprocessing.h>
#include<stdio.h>
VE::Graphics::VGraphics::VGraphics(class VE::Window::VWindow* wnd)
{
	this->wnds = wnd;
	switch (wnd->renderingApi)
	{
		case VAPI::WINDOWS:
			renderSystem = initDX11(wnd->phwnd);
			clearScreenColor = DX11_clearScreenColor;
			present = DX11_present;
			break;

		case VAPI::OGL:
			break;

		case VAPI::VULKAN:
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
	this->setFragmentShader(fs);
}

void VE::Graphics::VGraphics::SetVertexShader(void* vs)
{
	this->setVertexShader(vs);
}

void VE::Graphics::VGraphics::ClearScreenColor(float r, float g, float b, float a)
{
	this->clearScreenColor(this->renderSystem, r, g, b, a);
}

void VE::Graphics::VGraphics::Present()
{
	this->present(this->renderSystem);
}



