#pragma once
#include <sstream>

namespace VE
{
	namespace Resources
	{
		class VResourceChief
		{
		public:
			VResourceChief();
			//loads a resource from a file and manages it based of of the extenstion of the file. 
			//So in this case to extion of the file will help the resource manager know what to do with the file.
			void LoadResourceFromFileAuto(const wchar_t* file_path, const char* entry_point);
		};
	};
};
#define RC_ERROR(error_type, ...) \
{ \
	std::wstringstream stream = {}; \
	stream << error_type << L" " <<__VA_ARGS__<< "\nin " << __FILEW__ << L"\n"; \
	printf("%ls", stream.str().c_str()); \
}
