#include <VInput/VInput.h>

bool VE::Input::VInput::isKey(VKeyCode key, VKeyState state)
{
	//add the list of key to check for 
	mkeys.emplace(key, VKeyState::Null);
#if defined (WIN32) || defined (_WIN32) || defined (__WIN32)
	//check if key is down 
	if (GetAsyncKeyState((int)key))
	{
		//set the current key state to down
		mkeys[key] = VKeyState::Down;
	}
	else
	{
		//if the key was down before but this time not down
		//Set the current state to key up
		if (mkeys[key] == VKeyState::Down)
		{
			mkeys[key] = VKeyState::Up;	
		}
		//else if the key was not down set the key state to null
		else
		{
			mkeys[key] = VKeyState::Null;
		}
	}
	//check if the user's desired key state is equal to the current state of the key
	return (mkeys[key] == state);
#endif
}

