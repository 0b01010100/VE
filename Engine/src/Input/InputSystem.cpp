#include <Input/InputSystem.hpp>
#include <SDL2/SDL.h>
#include <math.h>

InputSystem::InputSystem()
{
    // Initialize key state arrays
    memset(m_keys_state, 0, sizeof(m_keys_state));
    memset(m_old_keys_state, 0, sizeof(m_old_keys_state));
    memset(m_final_keys_state, 2, sizeof(m_final_keys_state)); // Default to KEY_UP state

    m_cursorLocked = false;
    m_old_mouse_pos = Vector2D(0, 0);
    m_deltaMousePos = Vector2D(0, 0);
    m_lockAreaCenter = Vector2D(0, 0);
}

InputSystem::~InputSystem()
{
    // No specific cleanup needed for SDL
}

bool InputSystem::isKeyDown(const Key& key)
{
    return (m_final_keys_state[getInternalKeyCode(key)] == 0);
}

bool InputSystem::isKeyUp(const Key& key)
{
    return (m_final_keys_state[getInternalKeyCode(key)] == 1);
}

Vector2D InputSystem::getDeltaMousePosition()
{
    return m_deltaMousePos;
}

void InputSystem::lockCursor(bool lock)
{
    m_cursorLocked = lock;
    SDL_ShowCursor(lock ? SDL_DISABLE : SDL_ENABLE);
    
    if (lock) {
        SDL_SetRelativeMouseMode(SDL_TRUE);
    } else {
        SDL_SetRelativeMouseMode(SDL_FALSE);
    }
}

void InputSystem::SetlockArea(const Rect<float>& area)
{
    m_lockArea = area;
    m_lockAreaCenter = Vector2D(
        floor(area.left + (float)area.width / 2.0f), 
        floor(area.top + (float)area.height / 2.0f)
    );
}

void InputSystem::update()
{
    // Get mouse position and movement
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    Vector2D current_mouse_pos(mouseX, mouseY);

    if (current_mouse_pos.x != m_old_mouse_pos.x || current_mouse_pos.y != m_old_mouse_pos.y)
    {
        m_deltaMousePos = Vector2D(
            (float)current_mouse_pos.x - (float)m_old_mouse_pos.x,
            (float)current_mouse_pos.y - (float)m_old_mouse_pos.y
        );
    }
    else
    {
        m_deltaMousePos = Vector2D(0, 0);
    }

    if (!m_cursorLocked)
    {
        m_old_mouse_pos = Vector2D(current_mouse_pos.x, current_mouse_pos.y);
    }
    else
    {
        SDL_WarpMouseInWindow(NULL, (int)m_lockAreaCenter.x, (int)m_lockAreaCenter.y);
        m_old_mouse_pos = m_lockAreaCenter;
    }

    // Get keyboard state
    const Uint8* sdlKeyState = SDL_GetKeyboardState(NULL);
    
    // Process keyboard state
    for (unsigned int i = 0; i < 256; i++)
    {
        // Store previous state
        m_old_keys_state[i] = m_keys_state[i];
        
        // Get current state for this key (if mappable)
        short keyState = 0;
        SDL_Scancode scancode = getSDLScancode(i);
        if (scancode != SDL_SCANCODE_UNKNOWN) {
            keyState = sdlKeyState[scancode] ? 0x8001 : 0;
        }
        
        m_keys_state[i] = keyState;
        
        // KEY IS DOWN
        if (m_keys_state[i] & 0x8001)
        {
            m_final_keys_state[i] = 0;
        }
        else // KEY IS UP
        {
            if (m_keys_state[i] != m_old_keys_state[i])
            {
                m_final_keys_state[i] = 1;
            }
            else
            {
                m_final_keys_state[i] = 2;
            }
        }
    }
    
    // Process mouse buttons
    Uint32 mouseState = SDL_GetMouseState(NULL, NULL);
    
    // Update left mouse button state
    updateMouseButtonState(Key::LeftMouseButton, mouseState & SDL_BUTTON(SDL_BUTTON_LEFT));
    
    // Update middle mouse button state
    updateMouseButtonState(Key::MiddleMouseButton, mouseState & SDL_BUTTON(SDL_BUTTON_MIDDLE));
    
    // Update right mouse button state
    updateMouseButtonState(Key::RightMouseButton, mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT));
}

void InputSystem::updateMouseButtonState(const Key& key, bool isPressed)
{
    short keyCode = getInternalKeyCode(key);
    m_old_keys_state[keyCode] = m_keys_state[keyCode];
    m_keys_state[keyCode] = isPressed ? 0x8001 : 0;
    
    if (m_keys_state[keyCode] & 0x8001)
    {
        m_final_keys_state[keyCode] = 0; // DOWN
    }
    else
    {
        if (m_keys_state[keyCode] != m_old_keys_state[keyCode])
        {
            m_final_keys_state[keyCode] = 1; // JUST RELEASED
        }
        else
        {
            m_final_keys_state[keyCode] = 2; // UP
        }
    }
}

short InputSystem::getInternalKeyCode(const Key& key)
{
    short keyCode = 0;

    if (key >= Key::A && key <= Key::Z)
        keyCode = 'A' + ((short)key - (short)Key::A);
    else if (key >= Key::_0 && key <= Key::_9)
        keyCode = '0' + ((short)key - (short)Key::_0);
    else if (key == Key::Shift)
        keyCode = SDL_SCANCODE_LSHIFT;
    else if (key == Key::Escape)
        keyCode = SDL_SCANCODE_ESCAPE;
    else if (key == Key::Space)
        keyCode = SDL_SCANCODE_SPACE;
    else if (key == Key::Enter)
        keyCode = SDL_SCANCODE_RETURN;
    else if (key == Key::LeftMouseButton)
        keyCode = 0xF0; // Custom code for mouse buttons
    else if (key == Key::MiddleMouseButton)
        keyCode = 0xF1;
    else if (key == Key::RightMouseButton)
        keyCode = 0xF2;

    return keyCode;
}

SDL_Scancode InputSystem::getSDLScancode(short keyCode)
{
    // Handle letters
    if (keyCode >= 'A' && keyCode <= 'Z')
        return (SDL_Scancode)(SDL_SCANCODE_A + (keyCode - 'A'));
    
    // Handle numbers
    if (keyCode >= '0' && keyCode <= '9')
        return (SDL_Scancode)(SDL_SCANCODE_0 + (keyCode - '0'));
    
    // Handle special keys
    switch (keyCode)
    {
        case SDL_SCANCODE_LSHIFT: return SDL_SCANCODE_LSHIFT;
        case SDL_SCANCODE_ESCAPE: return SDL_SCANCODE_ESCAPE;
        case SDL_SCANCODE_SPACE: return SDL_SCANCODE_SPACE;
        case SDL_SCANCODE_RETURN: return SDL_SCANCODE_RETURN;
        default: return SDL_SCANCODE_UNKNOWN;
    }
}