#pragma once

namespace VE 
{
	//used for speciying the Api to use
	enum class VAPI : unsigned char
	{
#ifdef _WIN32
		//Window Api by Microsoft
		WINDOWS,
#endif
		//Window Api by Silicon Graphics, Inc.
		OGL,
		//Other Window Api by Khronos Group
		VULKAN
	};
}
