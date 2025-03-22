#pragma once
#include <Prerequisites.hpp>

class SwapChain
{
public:
	//Initialize SwapChain for a window
	SwapChain(void* hwnd, unsigned int width, unsigned int height, RenderSystem* system);
	~SwapChain();
	void setFullScreen(bool fullscreen, unsigned int width, unsigned int height);
	void resize(unsigned int width, unsigned int height);
	bool present(bool vsync);

private:
	void reloadBuffers(unsigned int width, unsigned int height);
private:

	RenderSystem* m_system = nullptr;
	void* m_hwnd;
private:
	friend class DeviceContext;
	friend class RenderSystem;
};
