#pragma once
#include <Windows.h>
#define USING_MSWINDOWMANAGER

void* MS_CreateWindow(const wchar_t* name, unsigned int SizeX, unsigned int SizeY);

void MS_UpdateWindow(void * hwnd);