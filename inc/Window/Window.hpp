#pragma once
#include <SDL2/SDL.h>
#include <Prerequisities.h>

class Window {
private:
    SDL_Window* m_window;
    SDL_GLContext m_glContext;
    struct {
        i32 width = 800;
        i32 height = 600;
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
    virtual void onSize(i32 width, i32 height);
    virtual void onFocus();
    virtual void onKillFocus();
    virtual void onMouseWheel(i32 delta);
    virtual void onDestroy();

    // Utility structs and methods
    struct Rect {
        i32 left, top, width, height;
    };

    Rect getClientSize() const;
    Rect getScreenSize() const;
    bool shouldClose() const;
    void pollEvents();
    SDL_Window* getHandle() const;
};
