#pragma once

namespace VE 
{
	//used for speciying the Api to use
	enum class VAPI : unsigned char
	{
		//Window Api by Microsoft
		WINDOWS,
		//Window Api by Silicon Graphics, Inc.
		OGL,
		//Other Window Api by Khronos Group
		VULKAN
	};
}
