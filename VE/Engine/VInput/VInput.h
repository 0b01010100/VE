#if _WIN32 
#include <Windows.h>
#include<map>
#endif
namespace VE 
{
	namespace Input
	{
		//The numeric code of keyboards keys
		enum VKeyCode : short
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
			_ESC = VK_ESCAPE,
			//RIGHT SHFT
			_RS = VK_RSHIFT,
			//LEFT SHIFT
			_LS = VK_LSHIFT,
#endif
		};
		//states that keys on a keyboard can have 
		enum VKeyState : char
		{
		   //key state is set to the when the key been up for two frame or more or when the key is first added to the list of keys to check for
			Null,
			//key state is set to this when the key is pressed
			Down,
			//key state is set when the key was unpressed 
			Up
		};
		//An input System
		class VInput
		{
		public:
			bool isKey(VKeyCode key, VKeyState state);
			//keeps track of all the keys that you want to check for using the isKey function
			std::map<VKeyCode, VKeyState> mkeys;
		};
	};
};