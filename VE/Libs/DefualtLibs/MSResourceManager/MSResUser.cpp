#include "MSResUser.h"


void* MS_Compile_HSLS_Shader(const wchar_t* file_path, const char* entry_point)
{
	ID3DBlob* shaderCode = nullptr;
	ID3DBlob* errCode = nullptr;
	long hr = D3DCompileFromFile(file_path, 0, 0, "vsmain", "vs_5_0", 0, 0, &shaderCode, &errCode);
	if (FAILED(hr))
	{
		D3D_ERROR("FAILED TO PROPERLY HANDLE HLSL Code in file: ", file_path);
	}
	return shaderCode;
}
