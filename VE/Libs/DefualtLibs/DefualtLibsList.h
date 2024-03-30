#pragma once
//------------------------------------------
//FOR MICROSOFTS window creation tool
#include "MSWindowManager/WinUser.h"
#ifdef USING_MSWINDOWMANAGER
#else//if function does not exist
#define MS_CreateWindow(N, N1, N2) 0
#define MS_UpdateWindow(N) 0
#endif
//------------------------------------------