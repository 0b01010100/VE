#include "MSResUser.h"




void* MS_Compile_HSLS_Shader(const wchar_t* file_path, const char* entry_point)
{
	ID3DBlob* shaderCode = nullptr;
	ID3DBlob* errCode = nullptr;
	
	//Open file for reading
	std::ifstream file(file_path); 
	if (!file.is_open()) {
		D3D_ERROR("HLSL SHADEER CAN'T BE OPENED. File is: ", file_path);
	}
	//get first line of the txt file. The first line will help specfy the shader type and version 
	std::string firstLine;
	if (!std::getline(file, firstLine)) { // Read the first line
		D3D_ERROR("HLSL SHADEER version not specifyed on the first line of the shader code of: ", file_path);
	}
	//Close the file
	file.close(); 
	//remove the frist and second slash(/) 
	firstLine.erase(0, 2);
	//compiler Shader

	HRESULT hr = D3DCompileFromFile(file_path, 0, 0, entry_point, firstLine.c_str(), 0, 0, &shaderCode, &errCode);
	//check if shader compiled with errors
	if(errCode)
	{
		std::wostringstream warr;
		warr << (char*)errCode->GetBufferPointer() << L"in file:"<< file_path;
		D3D_ERROR(L"HLSL SHADEER COMPILED WITH ERRORS\n\n" , warr.str().c_str());
	}
	//check of there are more warnings
	if (FAILED(hr))
	{
		D3D_ERROR(L"FAILED TO HANDLE HLSL Code in file:\n", file_path);
	}
	return shaderCode;
}
