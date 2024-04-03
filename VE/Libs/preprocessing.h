
//This file will keep track of all of the libs being used. If you don't want to use certian libs, difine Macros here

//FROM DEFUALT LIBS
#ifdef _WIN32
#include <DefualtLibs/MSWindowManager/MSWinUser.h>
#include <DefualtLibs/MSGraphicsManager/MSDX11User.h>
#pragma comment(lib,"d3dcompiler.lib")
#else
//For the Window
#define MS_CreateWindow(name, SizeX, SizeY) 0
#define MS_UpdateWindow 0
//For the Graphics Engine
#define initDX11() 0
#define DX11_clearScreenColor 0 
#define DX11_present 0 
#endif // _WIN32 



