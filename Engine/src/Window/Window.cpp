#include <Window/Window.hpp>
#include <stdexcept>
#include <glad/glad.h>
#include <SDL_image.h>
void Window::handleEvent(const SDL_Event& event, Window* window) {
    switch (event.type) {
        case SDL_WINDOWEVENT:
            switch (event.window.event) {
                case SDL_WINDOWEVENT_RESIZED:
                    window->onSize(event.window.data1, event.window.data2);
                    break;
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                    window->onFocus();
                    break;
                case SDL_WINDOWEVENT_FOCUS_LOST:
                    window->onKillFocus();
                    break;
            }
            break;
        case SDL_MOUSEWHEEL:
            window->onMouseWheel(event.wheel.y);
            break;
        case SDL_QUIT:
            window->onDestroy();
            window->m_shouldclose = true;
            break;
    }
}

Window::Window(std::string_view name, std::string_view icon_path) {
    // SDL Init
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("Failed to initialize SDL");
    }

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0){
        throw std::runtime_error("Failed to initialize SDL::image");
    }

    // Set OpenGL attributes before window creation
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Create SDL Window
    m_hwnd = SDL_CreateWindow
    (
        name.data(), 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        m_size.width, m_size.height, 
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    if (!m_hwnd) {
        SDL_Quit();
        throw std::runtime_error("Failed to create SDL window");
    }

    // Load icons for the window
    if (!icon_path.empty()){
        SDL_Surface* icon = IMG_Load(icon_path.data());
        if (icon){
            SDL_SetWindowIcon(m_hwnd, icon);
            SDL_FreeSurface(icon);
            onIconChange(); // first call
        }else{
            SDL_Log("Failed to load icon: %s", IMG_GetError());
        }
    }

    // Create OpenGL context
    m_glContext = SDL_GL_CreateContext(m_hwnd);
    if (!m_glContext) {
        SDL_DestroyWindow(m_hwnd);
        SDL_Quit();
        throw std::runtime_error("Failed to create OpenGL context");
    }

    // Initialize GLAD
    if (!gladLoadGL()) {
        SDL_GL_DeleteContext(m_glContext);
        SDL_DestroyWindow(m_hwnd);
        SDL_Quit();
        throw std::runtime_error("Failed to initialize GLAD");
    }
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Set up OpenGL viewport
    int width, height;
    SDL_GetWindowSize(m_hwnd, &width, &height);
    glViewport(0, 0, width, height);
}

Window::~Window() {
    if (m_glContext) {
        SDL_GL_DeleteContext(m_glContext);
    }
    if (m_hwnd) {
        SDL_DestroyWindow(m_hwnd);
    }
    SDL_Quit();
}

void Window::onSize(int width, int height) {
    m_size.width = width;
    m_size.height = height;
}

void Window::onFocus() {}

void Window::onKillFocus() {}

void Window::onMouseWheel(int delta) {}

void Window::onDestroy() {}

void Window::onIconChange() {}

void Window::setIcon(std::string_view path)
{
    
}

std::string Window::getIcon() const
{
    return this->m_icon_path;
}

Rect Window::getClientSize() const {
    int width, height;
    SDL_GetWindowSize(m_hwnd, &width, &height);
    return {0, 0, width, height};
}

Rect Window::getScreenSize() const {
    SDL_DisplayMode mode;
    SDL_GetCurrentDisplayMode(0, &mode);
    return {0, 0, mode.w, mode.h};
}

bool Window::shouldClose() const {
    return this->m_shouldclose;
}

void Window::pollEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        handleEvent(event, this);
    }
}

SDL_Window* Window::getHandle() const {
    return m_hwnd;
}
