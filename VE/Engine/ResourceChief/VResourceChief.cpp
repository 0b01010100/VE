#include <ResourceChief/VResourceChief.hpp>
#include <preprocessing.h>

VE::Resources::VResourceChief::VResourceChief()
{
}

void VE::Resources::VResourceChief::LoadResourceFromFileAuto(const wchar_t* file, const char* entry_point = 0)
{
	namespace fs = std::filesystem;
	//fs::path r1 = fs::absolute("..\\..\\..\\Games\\Game0\\Resources\\VertexShader.hlsl");
	fs::path rp = fs::absolute(file);
	if (!fs::exists(rp)) 
	{
		RC_ERROR("FAILED TO PROPERLY HANDLE RESORUSE code in file: ", file);
		return;
	}

	std::wstring extension = rp.extension();
	void* shaderCode = nullptr;
	if(extension == L".hlsl")
	{
		shaderCode = MS_Compile_HSLS_Shader(file, entry_point);
	}


}
