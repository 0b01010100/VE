
//This file will keep track of all of the libs being used. If you don't want to use certian libs, difine Macros here

//FROM DEFUALT LIBS
#ifdef _WIN32
#include <DefualtLibs/MSWindowManager/MSWinUser.h>
#else
#define MS_CreateWindow(name, SizeX, SizeY) 0
#define MS_UpdateWindow() 0
#endif // _WIN32 



