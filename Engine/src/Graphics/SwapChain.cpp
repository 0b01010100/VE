#include <Graphics/SwapChain.hpp>
#include <Graphics/RenderSystem.hpp>
#include <exception>
#include <SDL2/SDL.h>
#include <glad/glad.h>

SwapChain::SwapChain(void* hwnd, unsigned int width, unsigned int height, RenderSystem* system) 
: m_hwnd(hwnd), m_system(system)
{
}

void SwapChain::setFullScreen(bool fullscreen, unsigned int width, unsigned int height)
{
    if (fullscreen) {
        SDL_SetWindowFullscreen(reinterpret_cast<SDL_Window*>(m_hwnd), SDL_WINDOW_FULLSCREEN);
    } else {
        SDL_SetWindowFullscreen(reinterpret_cast<SDL_Window*>(m_hwnd), 0);
        SDL_SetWindowSize(reinterpret_cast<SDL_Window*>(m_hwnd), width, height);
    }
}

void SwapChain::resize(unsigned int width, unsigned int height)
{
    SDL_SetWindowSize(reinterpret_cast<SDL_Window*>(m_hwnd), width, height);
    glViewport(0, 0, width, height);
}

bool SwapChain::present(bool vsync)
{
	SDL_GL_SetSwapInterval(vsync ? 1 : 0); // Enable or disable VSync
    SDL_GL_SwapWindow(reinterpret_cast<SDL_Window*>(m_hwnd));
    return true;
}

void SwapChain::reloadBuffers(unsigned int width, unsigned int height)
{
    resize(width, height);
}

SwapChain::~SwapChain()
{

}