#pragma once
namespace VE 
{
	namespace Window
	{
		struct VWRect
		{
			long    left;
			long    top;
			long    right;
			long    bottom;
		};
		//used for speciying the Api to use
		enum class VAPI : unsigned int
		{
#ifdef _WIN32
			//Window Api by Microsoft
			WINDOWS,
#endif
			//Window Api by Silicon Graphics, Inc.
			OGL,
			//Other Window Api by Khronos Group
			VULKAN
		};
		//A WINDOW
		class VWindow
		{
		public:
			//initialize the window
			//@param Name -> Name of the window 
			//@param SizeX -> Width of the window
			//@param SizeY -> Height of the window
			//@param Api -> the api that should be used for creating the window. For example OGL or MSW(Windoing api by Microsoft)
			VWindow(const wchar_t* Name, long SizeX, long SizeY, VAPI Api);
			//for updateting the window 
			void Update();
			VWRect GetClientWindowRect();
			unsigned int GetRenderingApi() const noexcept;
			void* GetWindowHandle() const noexcept;
		private:
			//used to point to an Api specfic function that will update the window
			void(*update)(void* phwnd) = nullptr;
			void(*getClientWindowRect)(void* phwnd, long rect[4]) = nullptr;
	
			//used to pointer to an Api specfic id for a window
			void* phwnd = nullptr;
			
		public:
			VAPI RenderingApi;
		};
	}

}


