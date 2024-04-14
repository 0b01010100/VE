#include <VGraphics/VGraphicsResourceChief.hpp>

VE::Graphics::VGraphicsResourceChief::VGraphicsResourceChief()
{
}

VE::Graphics::Resources::VMesh* VE::Graphics::VGraphicsResourceChief::createMesh(void* points, unsigned int vertexSize, unsigned int pointCount, void* indices, unsigned int indiceCount, void* cb, unsigned int cbSize)
{
	
	return new VE::Graphics::Resources::VMesh(points, vertexSize, pointCount, indices, indiceCount, cb, cbSize);
}
