#pragma once
#include <req.h>
namespace VE 
{
	namespace Graphics 
	{

		class VGraphicsResourceChief
		{
		public:
			VGraphicsResourceChief();
			VE::Graphics::Resources::VMesh* createMesh
			(
				void* points, unsigned int vertexSize, unsigned int pointCount, void* indices, unsigned int indiceCount, void* cb, unsigned int cbSize
			);
		};
	};
};