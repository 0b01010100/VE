#include <Window/VWindow.hpp>
namespace VE
{
	namespace Graphics
	{
		//A GRAPHICS ENGINE 
		class VGraphics
		{
		public:
			//initialize the Graphics Engine
			VGraphics(class VE::Window::VWindow* wnd);
			//will a set a Pixel/Fragment shader for the render system to use 
			void SetFragmentShader(void* fs);
			//will a set a Vertex shader for the render system to use 
			void SetVertexShader(void* vs);
			//will clear the color of the texture to a given color
			void ClearScreenColor(float r, float g, float b, float a);
			//will present what was draw on the render texture so we can see it 
			void Present();
		private:
			//window to render to
			class VE::Window::VWindow* wnds;
		
			//pointer the the render system
			void* renderSystem;
			//these pointer functions will help us interract with rendering APIs 

			void(*setFragmentShader)(void* fs) = nullptr;
			void(*setVertexShader)(void* vs) = nullptr;
			void(*clearScreenColor)(void * rs, float r, float g, float b, float a) = nullptr;
			void(*present)(void*) = nullptr;
		};

	};
};