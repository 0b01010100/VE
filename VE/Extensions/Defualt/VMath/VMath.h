#include <string>
#include <sstream>
#include <math.h>
//want to use a Vector 3 then do #define Vec3
#if defined(_Vec3)
#include "Vvec3"
#endif // defined(Vec3)

//want to use a 4 by 4 matrix then do #define Mat4x4
#if defined(_Mat4x4)
#include "Vmat4x4" 
#endif // defined(Mat4x4)

//want to use a Vertex library then do #define Vertex
#if defined(_Vertex)
#include "Vvertex" 
#endif // defined(Vertex)