#include <Window/Window.hpp>
#include <stdexcept>

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    win->onSize(width, height);
}

void Window::focusCallback(GLFWwindow* window, int focused) {
    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (focused)
        win->onFocus();
    else
        win->onKillFocus();
}

void Window::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    win->onMouseWheel(static_cast<int>(yoffset));
}

Window::Window() {
    // GLFW Init
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    // Create window
    m_window = glfwCreateWindow(m_size.width, m_size.height, 
                              "GLFW Window", nullptr, nullptr);
    if (!m_window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create window");
    }

    // Set window user pointer to this instance
    glfwSetWindowUserPointer(m_window, this);

    // Set callbacks
    glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);
    glfwSetWindowFocusCallback(m_window, focusCallback);
    glfwSetScrollCallback(m_window, scrollCallback);

    // Make OpenGL context current
    glfwMakeContextCurrent(m_window);
}

Window::~Window() {
    if (m_window) {
        glfwDestroyWindow(m_window);
    }
    glfwTerminate();
}

void Window::onSize(int width, int height) {
    m_size.width = width;
    m_size.height = height;
}

void Window::onFocus() {}

void Window::onKillFocus() {}

void Window::onMouseWheel(int delta) {}

void Window::onDestroy() {}

Window::Rect Window::getClientSize() const {
    int width, height;
    glfwGetFramebufferSize(m_window, &width, &height);
    return {0, 0, width, height};
}

Window::Rect Window::getScreenSize() const {
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    return {0, 0, mode->width, mode->height};
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(m_window);
}

void Window::pollEvents() {
    glfwPollEvents();
}

GLFWwindow* Window::getHandle() const {
    return m_window;
}