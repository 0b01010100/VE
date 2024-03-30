#pragma once
#include <req.h>
namespace VE 
{
	namespace Window
	{
		//A window
		class VWindow
		{
		public:
			//initialize the window
			//@param Name -> Name of the window 
			//@param SizeX -> Width of the window
			//@param SizeY -> Height of the window
			//@param Api -> the api that should be used for creating the window. For example OGL or MSW(Windoing api by Microsoft)
			VWindow(const wchar_t* Name, unsigned int SizeX, unsigned int SizeY, VAPI Api);
			//for updateting the window 
			void Update();
		private:
			//used to point to an Api specfic function that will update the window
			void(*update)(void* phwnd);
			//used to point to an Api specfic id for a window
			void* phwnd;
		};
	}

}


