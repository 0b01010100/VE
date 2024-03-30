#include <Window/VWindow.h>
int main() 
{
	VE::Window::VWindow* w = new VE::Window::VWindow(L"Scene0", 0, 0, VE::VAPI::WINDOW);
	VE::Window::VWindow* w1 = new VE::Window::VWindow(L"Scene1", 0, 0, VE::VAPI::WINDOW);

	while (true)
	{
		w->Update();
		w1->Update();

	

	}

}