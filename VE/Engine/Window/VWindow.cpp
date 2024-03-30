#include "VWindow.h"
#include <LibsList.h>

//a window that wiill encapsulate the complexity of window managment
VE::Window::VWindow::VWindow(const wchar_t* Name, unsigned int SizeX, unsigned int SizeY, VAPI Api)
{
	//selection of which api to use the create the window
	switch (Api)
	{
		case VAPI::WINDOW:
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

}
//update the window
void VE::Window::VWindow::Update()
{
	this->update(this->phwnd);
}
