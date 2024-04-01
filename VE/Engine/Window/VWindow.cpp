#include "VWindow.hpp"
#include <preprocessing.h>
#include <stdio.h>
//a window that wiill encapsulate the complexity of window managment
VE::Window::VWindow::VWindow(const wchar_t* Name, long SizeX, long SizeY, VAPI Api)
{
	this->renderingApi = Api;
	//selection of which api to use the create the window
	switch (Api)
	{
		case VAPI::WINDOWS:
			this->phwnd = MS_CreateWindow(Name, SizeX, SizeY);
			update = MS_UpdateWindow;
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
