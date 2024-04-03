#include <ResourceChief/VResourceChief.hpp>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>

#if WIN32
#include <d3dcompiler.h>
#endif // WIN32

VE::Resources::VResourceChief::VResourceChief()
{
}

void VE::Resources::VResourceChief::LoadResourceFromFileAuto(const wchar_t* file, const char* entry_point)
{
	namespace fs = std::experimental::filesystem;
	fs::path relativePath = file;
	fs::path absolutePath = fs::absolute(relativePath);

	int hr = 0xf;
	if (fs::exists(absolutePath))
	{
		//get file extension
		std::wstring extension = absolutePath.extension();

		if (extension == L".hlsl") 
		{
			//D3DCompileFromFile(relativePath.c_str(), 0, 0, entry_point, "vs_5_0", 0, 0);
			hr = 0xf;
		}
	}
	if (hr == 0xf)
	{
		RC_ERROR(L"Failed to compile file: ", relativePath.c_str());
		
	}

}
