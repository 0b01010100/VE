#include <string>
#include <sstream>
namespace VE
{
	namespace VMath
	{
		//want to use a Vector 3 then do #define Vec3
		#if defined(Vec3)
		#include "Vvec3"
		#endif // defined(Vec3)

		//want to use a 4 by 4 matrix then do #define Mat4x4
		#if defined(Mat4x4)
		#include "Vmat4x4" 
		#endif // defined(Mat4x4)
	};
};