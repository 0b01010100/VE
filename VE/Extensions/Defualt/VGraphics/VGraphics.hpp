#pragma once
#include <VWindow/VWindow.hpp>
#include <VGraphics/VGraphicsResourceChief.hpp>

namespace VE
{
	namespace Graphics
	{
		/*extends IGraphicsEngine_Base*/
		#include <VGraphics/req.h>
		//A GRAPHICS ENGINE 
		class VGraphics
		{
		public:
			//initialize the Graphics Engine
			VGraphics(class VE::Window::VWindow* wnd);
			~VGraphics();
			//will a set a Pixel/Fragment shader for the render system to use 
			void SetFragmentShader(void* fs);
			//will a set a Vertex shader for the render system to use 
			void SetVertexShader(void* vs);
			//will a set a Mesh the render system to use 
			void SetMesh(VE::Graphics::Resources::VMesh mesh);
			//will clear the color of the texture to a given color
			void ClearScreenColor(float r, float g, float b, float a);
			//will present what was draw on the render texture so we can see it 
			void Present();
		private:
			//WARNING ANY MODIFICATION TO THE INTERFACE CAN LEAD TO MEMORY LEAKS
			//________________________________________________________________
			//will a set a Pixel/Fragment shader for the render system to use 
			void(*setFragmentShader)(void* rs, void* fs) = nullptr;
			//will a set a Vertex shader for the render system to use 
			void(*setVertexShader)(void* rs, void* vs) = nullptr;
			//will clear the color of the texture to a given color
			void(*clearScreenColor)(void* rs, float r, float g, float b, float a) = nullptr;
			//will present what was draw on the render texture so we can see it 
			void(*present)(void* rs) = nullptr;
			//will a set a Mesh the render system to use 
			void(*setMesh)(void* rs, VE::Graphics::Resources::VMesh mesh) = nullptr;
			//________________________________________________________________
			
			//window to render to
			class VE::Window::VWindow* wnds = nullptr;
			//pointer the the render system
			void* renderSystem = nullptr;
			//these pointer functions will help us interract with rendering APIs 
		public:
			VGraphicsResourceChief* resourceManager = nullptr;
		};

	};
};