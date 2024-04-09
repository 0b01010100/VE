struct IGraphicsEngine_Base
{
	public:
		//will a set a Pixel/Fragment shader for the render system to use 
		void(*setFragmentShader)(void* rs, void* fs) = nullptr;
		//will a set a Vertex shader for the render system to use 
		void(*setVertexShader)(void* rs, void* vs) = nullptr;
		//will clear the color of the texture to a given color
		void(*clearScreenColor)(void* rs, float r, float g, float b, float a) = nullptr;
		//will present what was draw on the render texture so we can see it 
		void(*present)(void* rs) = nullptr;
};