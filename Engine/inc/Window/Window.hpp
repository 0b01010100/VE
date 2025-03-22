#pragma once
#include <SDL2/SDL.h>
#include <Math/Rect.hpp>

class Window {
private:
    SDL_Window* m_hwnd;
    SDL_GLContext m_glContext;
    struct {
        int width = 800;
        int height = 600;
    } m_size;

    // Static event handlers
    static void handleEvent(const SDL_Event& event, Window* window);
    bool m_shouldclose = false;
public:
    // Constructor and destructor
    Window();
    ~Window();

    // Prevent copying
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    // Event handlers that can be overridden
    virtual void onSize(int width, int height);
    virtual void onFocus();
    virtual void onKillFocus();
    virtual void onMouseWheel(int delta);
    virtual void onDestroy();

    Rect getClientSize() const;
    Rect getScreenSize() const;
    bool shouldClose() const;
    void pollEvents();
    SDL_Window* getHandle() const;
};
