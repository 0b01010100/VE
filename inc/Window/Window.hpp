#pragma once
#include <GLFW/glfw3.h>
#include <Prerequisities.h>

class Window {
private:
    GLFWwindow* m_window;
    struct {
        i32 width = 800;
        i32 height = 600;
    } m_size;

    // Static callback functions
    static void framebufferSizeCallback(GLFWwindow* window, i32 width, i32 height);
    static void focusCallback(GLFWwindow* window, i32 focused);
    static void scrollCallback(GLFWwindow* window, f64 xoffset, f64 yoffset);

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
    GLFWwindow* getHandle() const;
};