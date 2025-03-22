#pragma once
#include <Prerequisites.hpp>
#include <Math/Vector2D.hpp>
#include <Math/Rect.hpp>

class InputSystem
{
public:
	InputSystem();
	~InputSystem();
public:
	bool isKeyDown ( const Key& key );
	bool isKeyUp ( const Key& key );
	Vector2D getDeltaMousePosition ( );

	void lockCursor ( bool lock );
	void SetlockArea( const Rect& area );

	void update();
private:
	short getInternalKeyCode ( const Key& key );
private:

	short m_keys_state[256] = {};
	short m_old_keys_state[256] = {};
	short m_final_keys_state[256] = {};

	bool m_cursorLocked = false;
	Rect m_lockArea;
	Vector2D m_lockAreaCenter;

	Vector2D m_deltaMousePos;
	Vector2D m_old_mouse_pos;
};