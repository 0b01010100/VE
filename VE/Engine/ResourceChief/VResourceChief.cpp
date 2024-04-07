#include <ResourceChief/VResourceChief.hpp>
#include <preprocessing.h>

VE::Resources::VResourceChief::VResourceChief()
{
}

void* VE::Resources::VResourceChief::LoadResourceFromFileAuto(const wchar_t* file, const char* entry_point = 0)
{
	namespace fs = std::filesystem;

	//get the the full file path. Like where the file is in the enteirs strorage drive
	fs::path rp = fs::absolute(file);
	//check if the file really exist
	if (!fs::exists(rp)) 
	{
		RC_ERROR("FAILED TO PROPERLY HANDLE RESORUSE code in file: ", file);
		return 0;
	}

	void* resource = nullptr;

	std::wstring extension = rp.extension();
	//check if the file extension in .hlsl
	if(extension == L".hlsl")
	{//if som compile .hlsl resource
		resource = MS_Compile_HSLS_Shader(file, entry_point);
	}

	return resource;

}
