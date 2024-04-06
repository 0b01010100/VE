#pragma once
#include <iostream>
namespace VE
{
	namespace VDebuging
	{
		namespace VConsole
		{
#ifdef _DEBUG
			//Type the string or integral data you want in the parameter and VPRINTf will format it and display it on the console window
			template<typename... Args>
			static void VLOGf(Args&&... args)
			{
				(std::wcout << ... << std::forward<Args>(args));
			}
#else
			// Dummy function for release mode(compiler will delete this, since it is dead code)
			static void VLOGf(...){}
#endif
		};
	};
};