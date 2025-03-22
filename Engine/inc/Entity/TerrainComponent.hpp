#pragma once
#include <Prerequisites.hpp>
#include <Entity/Component.hpp>
#include <Math/Vector3D.hpp>


class TerrainComponent : public Component
{
public:
	TerrainComponent ( );
	virtual ~TerrainComponent ( );

	void setHeightMap ( const TexturePtr& heightMap );
	const TexturePtr& getHeightMap ( );

	void setGroundMap ( const TexturePtr& groundMap );
	const TexturePtr& getGroundMap ( );

	void setCliffMap ( const TexturePtr& cliffMap );
	const TexturePtr& getCliffMap ( );

	void setSize ( const Vector3D& size );
	Vector3D getSize ( );
private:
	void generateTerrainMesh ( );
	void updateData ( void* data, ui32 size);
protected:
	virtual void onCreateInternal ( );
private:
	TexturePtr m_heightMap;
	TexturePtr m_groundMap;
	TexturePtr m_cliffMap;

	Vector3D m_size = Vector3D ( 512, 100, 510 );//Size of the Terrain

	VertexBufferPtr m_meshVb;
	IndexBufferPtr m_meshIb;
	UniformBufferPtr m_cb;

	VertexShaderPtr m_vertexShader;
	PixelShaderPtr m_pixelShader;


	friend class GraphicsEngine;
};
