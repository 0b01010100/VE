#if _WIN32 
#include <Windows.h>

#endif

#include <Input/Input.h>

bool Input::isKey(KeyCode key, KeyState state)
{
	//add key to the list of key to check for if key is not already added
	mkeys.emplace(key, KeyState::Null);
#if defined (WIN32) || defined (_WIN32) || defined (__WIN32)
	//check if key is down 
	if (GetAsyncKeyState((int)key))
	{
		//set the current key state to down
		mkeys[key] = KeyState::Down;
	}
	else
	{
		//if the key was down before but this time not down
		//Set the current state to key up
		if (mkeys[key] == KeyState::Down)
		{
			mkeys[key] = KeyState::Up;	
		}
		//else if the key was not down set the key state to null
		else
		{
			mkeys[key] = KeyState::Null;
		}
	}
	//check if the user's desired key state is equal to the current state of the key
	return (mkeys[key] == state);
#endif
}
