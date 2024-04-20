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
			//will allow you to create a custom mesh 
			VE::Graphics::Resources::VMesh createMesh
			(
				//this should point to an array of verties 
				void* verties, 
				//size of each vertex
				unsigned int vertexSize,
				//number of verties
				unsigned int vertexCount, 
				//Instead of specifying the vertices directly for each triangle, an index buffer is
				//used to reference vertices from the vertex buffer.
				std::vector<unsigned int> indices, 
				//constant buffer
				void* cb, 
				//size of the const buffer struct or class 
				unsigned int cbSize
			);
		};
	};
};