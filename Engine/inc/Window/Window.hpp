#pragma once
#include <SDL2/SDL.h>
#include <Math/Rect.hpp>
#include <string>
#include <string_view>
class Window 
{
private:
    std::string m_icon_path;
    SDL_Window* m_hwnd;
    SDL_GLContext m_glContext;
    struct {
        int width = 800;
        int height = 600;
    } m_size;
    
    // Static event handlers
    bool m_shouldclose = false;
private:
    static void handleEvent(const SDL_Event& event, Window* window);

public:
    // Constructor and destructor
    Window(std::string_view name, std::string_view icon_path);
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
    virtual void onIconChange();


    void setIcon(std::string_view path);
    
    std::string getIcon() const;
    Rect getClientSize() const;
    Rect getScreenSize() const;
    bool shouldClose() const;
    void pollEvents();

    SDL_Window* getHandle() const;
};
