#include <VGraphics/VGraphicsResourceChief.hpp>

VE::Graphics::VGraphicsResourceChief::VGraphicsResourceChief()
{
}

VE::Graphics::Resources::VMesh* VE::Graphics::VGraphicsResourceChief::createMesh(void* verties, unsigned int vertexSize, unsigned int vertexCount, void* indices, unsigned int indiceCount, void* cb, unsigned int cbSize)
{
	
	return new VE::Graphics::Resources::VMesh(verties, vertexSize, vertexCount, indices, indiceCount, cb, cbSize);
}
