#pragma once

//init the Microsift specefic window system
void* MSW_init(void* window, const wchar_t* name, long SizeX, long SizeY);

//THESE FUNCTIONS ARE PRIVATE AND IN MSWinUser.cpp
//creates a Microsift specefic window
//static void* MSW_CreateWindow(const wchar_t* name, long SizeX, long SizeY);

//update window
//static __declspec(noinline) void MSW_UpdateWindow(void * hwnd);

//Gets the client Size of the window
//__declspec(noinline) static void MSW_GetClientWindowRect(void* hwnd, long rect[4]);