#include <SDL2/SDL.h>
#include <Game/Game.hpp>

void Game::run()
{
    onCreate();
    
    SDL_Event event;
    while (m_isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                m_isRunning = false;
            }
        }
        onInternalUpdate();
    }
    
    onQuit();
}
