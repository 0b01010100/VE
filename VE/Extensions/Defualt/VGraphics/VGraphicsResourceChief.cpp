#include <VGraphics/VGraphicsResourceChief.hpp>

VE::Graphics::VGraphicsResourceChief::VGraphicsResourceChief()
{
}

VE::Graphics::Resources::VMesh VE::Graphics::VGraphicsResourceChief::createMesh
(
	void* verties,//please allocate using the new keyword. memory will be handled for you
	unsigned int vertexSize, 
	unsigned int vertexCount, 
	std::vector<unsigned int> indices, 
	void* cb, 
	unsigned int cbSize
)
{
	return VE::Graphics::Resources::VMesh(verties, vertexSize, vertexCount, indices, cb, cbSize);
}
