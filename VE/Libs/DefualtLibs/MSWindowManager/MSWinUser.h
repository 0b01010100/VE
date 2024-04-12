#pragma once
//#define UNICODE
#include <Windows.h>
#include <sstream>

//creates a Microsift specefic window
void* MS_CreateWindow(const wchar_t* name, long SizeX, long SizeY);
//update window
__declspec(noinline) void MS_UpdateWindow(void * hwnd);
//Debugging only for MS window creation tool
#define MS_ERROR(error_type, ...) \
{ \
	std::wstringstream stream = {}; \
	stream << error_type << L"\n" <<__VA_ARGS__ << __FILEW__ << L"\n"; \
	printf("%ls", stream.str().c_str()); \
	OutputDebugStringW(stream.str().c_str()); \
	MessageBoxW(0, stream.str().c_str(), error_type, MB_ICONERROR | MB_OK); \
}
