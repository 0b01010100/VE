#include <string>
#include <sstream>
#include <math.h>
#define V_pi 3.14159265358979323846F
#define V_e 2.71828182845904523536F
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