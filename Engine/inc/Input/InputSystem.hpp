#pragma once
#include <Prerequisites.hpp>
#include <SDL2/SDL.h>
#include <Math/Vector2D.hpp>
#include <Math/Rect.hpp>

class InputSystem
{
public:
    InputSystem();
    ~InputSystem();

    // Key state checking
    bool isKeyDown(const Key& key);
    bool isKeyUp(const Key& key);
    
    // Mouse handling
    Vector2D getDeltaMousePosition();
    void lockCursor(bool lock);
    void SetlockArea(const Rect<float>& area);
    
    // Frame update
    void update();

private:
    // Key state storage
    short m_keys_state[256] = { 0 };
    short m_old_keys_state[256] = { 0 };
    short m_final_keys_state[256] = { 0 };
    
    // Mouse state
    Vector2D m_old_mouse_pos;
    Vector2D m_deltaMousePos;
    Rect<float> m_lockArea;
    Vector2D m_lockAreaCenter;
    bool m_cursorLocked;
    
    // Helper methods
    short getInternalKeyCode(const Key& key);
    SDL_Scancode getSDLScancode(short keyCode);
    void updateMouseButtonState(const Key& key, bool isPressed);
};