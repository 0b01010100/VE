#include "VWindow.hpp"
#include "VWindow.hpp"
#include "VWindow.hpp"
#include <MSWindowManager/MSWinUser.h>
#include <stdio.h>
//a window that wiill encapsulate the complexity of window managment
VE::Window::VWindow::VWindow(const wchar_t* Name, long SizeX, long SizeY, VAPI Api)
{
	this->RenderingApi = Api;
	//selection of which api to use the create the window
	switch (Api)
	{
		case VAPI::WINDOWS:
			this->phwnd = MSW_init(this, Name, SizeX, SizeY);
			break;
		case VAPI::OGL:
			break;
		case VAPI::VULKAN:
			break;
		default:
			break;
	}
	//check if phwnd in nullptr if so there was a problem creating the window
	if (phwnd == nullptr) 
	{
		printf("Window creation didn't go so well in File: %ls", __FILEW__);
	}
}
//update the window
void VE::Window::VWindow::Update()
{
	this->update(this->phwnd);
}

VE::Window::VWRect VE::Window::VWindow::GetClientWindowRect()
{
	long rect[4] = {};
	this->getClientWindowRect(this->phwnd, rect);
	return VWRect(rect[0],rect[1], rect[2], rect[3]);
}

unsigned int VE::Window::VWindow::GetRenderingApi() const noexcept
{
	return (unsigned int)this->RenderingApi;
}

void* VE::Window::VWindow::GetWindowHandle() const noexcept
{
	return this->phwnd;
}

