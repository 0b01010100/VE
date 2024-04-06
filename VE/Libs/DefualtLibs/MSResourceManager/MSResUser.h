#pragma once
#pragma comment(lib,"d3dcompiler.lib")
#include <d3dcompiler.h>

//Compiles an HLSL shader 
//file_path -> the relative file path of the Shader file
//entry_point ->name of entry point function in the shader
void* MS_Compile_HSLS_Shader(const wchar_t* file_path, const char* entry_point);

#include <filesystem>
#include <sstream>
#include <string>
#define D3D_ERROR(error_type, ...) \
{ \
	std::wstringstream stream = {}; \
	stream << L"HSLS compiler error" << L" " <<__VA_ARGS__<< L"\nin " << __FILEW__ << L"\n"; \
	printf("%ls", stream.str().c_str()); \
}