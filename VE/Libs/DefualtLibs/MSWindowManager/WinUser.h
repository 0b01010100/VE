#pragma once
#include <Windows.h>
#include <sstream>
#define USING_MSWINDOW_MANAGER

//creates a Microsift specefic window
void* MS_CreateWindow(const wchar_t* name, unsigned int SizeX, unsigned int SizeY);
//update window
void MS_UpdateWindow(void* hwnd);
//Debugging only for MS window creation tool
#define MS_ERROR(error_type, ...) \
{ \
	std::wstringstream stream = {}; \
	stream << error_type << L"\n" <<__VA_ARGS__ << __FILEW__ << "\n"; \
	printf("%ls", stream.str().c_str()); \
	OutputDebugString(stream.str().c_str()); \
	MessageBox(0, stream.str().c_str(), error_type, MB_ICONERROR | MB_OK); \
}
