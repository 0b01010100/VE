#pragma once
#pragma comment(lib,"d3dcompiler.lib")
#include <d3dcompiler.h>

//Compiles an HLSL shader 
//file_path -> the relative file path of the Shader file
//entry_point ->name of entry point function in the shader
void* MS_Compile_HSLS_Shader(const wchar_t* file_path, const char* entry_point);

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define D3D_ERROR(error_type, ...) \
{ \
	std::wstringstream stream = {}; \
	stream << error_type <<__VA_ARGS__<< L"\ncompiler located in file in " << __FILEW__ << L"\n\n"; \
	printf("%ls", stream.str().c_str()); \
}