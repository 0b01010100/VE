#pragma once
#include<map>

//The numeric code of keyboards keys
enum KeyCode : short
{
	null = 0,
	//Numbers

	_0 = '0',
	_1,
	_2,
	_3,
	_4,
	_5,
	_6,
	_7,
	_8,
	_9,
	//Letters

	_A = 'A',
	_B,
	_C,
	_D,
	_E,
	_F,
	_G,
	_H,
	_I,
	_J,
	_K,
	_L,
	_M,
	_N,
	_O,
	_P,
	_Q,
	_R,
	_S,
	_T,
	_U,
	_V,
	_W,
	_X,
	_Y,
	_Z,

#if _WIN32
	//ESCAPE KEY
	_ESC = 0x1B,
	//RIGHT SHFT
	_RS = 0xA1,
	//LEFT SHIFT
	_LS = 0xA0,
#endif
	};

//states that keys on a keyboard can have 
enum KeyState : char
{
	//key state is set to the when the key been up for two frame or more or when the key is first added to the list of keys to check for
	Null,
	//key state is set to this when the key is pressed
	Down,
	//key state is set when the key was unpressed 
	Up
};

//An input System
class Input
{
	public:
	bool isKey(enum KeyCode key, enum KeyState state);
	//keeps track of all the keys that you want to check for using the isKey function
	class std::map<enum KeyCode, enum KeyState> mkeys;
};