#include <Graphics/GraphicsEngine.hpp>
#include <Graphics/RenderSystem.hpp>
#include <Graphics/DeviceContext.hpp>
#include <Graphics/SwapChain.hpp>

#include <Resource/ResourceManager.hpp>
#include <Resource/Mesh.hpp>
#include <Resource/Texture.hpp>
#include <Graphics/Texture2D.hpp>
#include <Resource/Material.hpp>

#include <Game/Game.hpp>
#include <Game/Display.hpp>

#include <Math/Matrix4x4.hpp>
#include <Math/Vector4D.hpp>

#include <Entity/TransformComponent.hpp>
#include <Entity/MeshComponent.hpp>
#include <Entity/CameraComponent.hpp>
#include <Entity/LightComponent.hpp>
#include <Entity/TerrainComponent.hpp>

#include <Entity/Entity.hpp>
#include <Math/Rect.hpp>

struct alignas(16) LightData
{
	Vector4D color;
	Vector4D direction;
};
struct alignas(16) TerrainData
{
	Vector4D size;
	f32 heightMapSize = 0.0f;// the number of texels along one edge of the height map
};

struct alignas(16) ConstantData
{
	Matrix4x4 world;
	Matrix4x4 view;
	Matrix4x4 proj;
	Vector4D cameraPosition;
	LightData light;
	TerrainData terrain;
};


GraphicsEngine::GraphicsEngine ( Game* game ) : m_game ( game )
{
	this->m_render_system = new RenderSystem();
	auto display = game->m_display.get();
	Rect screen_size = display->getScreenSize();
	display->m_swapChain = this->m_render_system->createSwapChain 
	( 
		display->getHandle(), 
		screen_size.width, screen_size.height 
	);
}

void GraphicsEngine::update ( )
{
	auto swapChain = m_game->m_display->m_swapChain;

	auto context = m_render_system->getImmediateDeviceContext ( );

	context->clearRenderTargetColor ( swapChain, 0, 0, 0, 1 );
	auto winSize = m_game->m_display->getClientSize ( );
	context->setViewportSize ( winSize.width, winSize.height );


	ConstantData constData = {};

	for (auto c : m_cameras)
	{
		auto t = c->getEntity ( )->getTransform ( );
		constData.cameraPosition = t->getPosition ( );
		c->setScreenArea ( winSize );
		c->getViewMatrix ( constData.view );
		c->getProjectionMatrix ( constData.proj );
	}


	for (auto l : m_lights)
	{
		auto t = l->getEntity ( )->getTransform ( );
		Matrix4x4 w;
		t->getWorldMatrix ( w );
		constData.light.direction = w.getZDirection ( );
		constData.light.color = l->getColor ( );
	}

	for (auto t : m_terrains) 
	{
		auto transform = t->getEntity ( )->getTransform ( );
		transform->getWorldMatrix ( constData.world );
		constData.terrain.size = t->getSize ( );
		constData.terrain.heightMapSize = t->getHeightMap ( )->getTexture ( )->getSize().width;

		context->setVertexBuffer ( t->m_meshVb );
		context->setIndexBuffer ( t->m_meshIb );

		m_render_system->getImmediateDeviceContext()->setCullMode ( CullMode::Back );
		t->updateData ( &constData, sizeof ( constData ) );
		context->setUniformBuffer( t->m_cb, 0);

		context->setVertexShader ( t->m_vertexShader );
		context->setPixelShader ( t->m_pixelShader );

		Texture2DPtr terrainTexture[3];
		terrainTexture[0] = t->getHeightMap ( )->getTexture ( );
		terrainTexture[1] = t->getGroundMap ( )->getTexture ( );
		terrainTexture[2] = t->getCliffMap ( )->getTexture ( );

		context->setTexture ( terrainTexture, 3 );

		context->drawIndexedTriangleList ( (ui32)t->m_meshIb->getSizeIndexList(), 0, 0);
	}

	for (auto m : m_meshes)
	{
		auto transform = m->getEntity ( )->getTransform ( );
		transform->getWorldMatrix ( constData.world );

		auto mesh = m->getMesh ( ).get ( );
		const auto materials = m->getMaterials ( );


		context->setVertexBuffer ( mesh->m_vertex_buffer );
		context->setIndexBuffer ( mesh->m_index_buffer );


		for (auto i = 0; i < mesh->getNumMaterialSlots ( ); i++)
		{
			if (i >= materials.size ( )) break;
			auto mat = materials[i].get ( );

			m_render_system->getImmediateDeviceContext()->setCullMode ( mat->getCullMode ( ) );

			mat->setData ( &constData, sizeof ( ConstantData ) );
			context->setUniformBuffer ( mat->m_constant_buffer, 0 );

			context->setVertexShader ( mat->m_vertex_shader );
			context->setPixelShader ( mat->m_pixel_shader );

			context->setTexture ( &mat->m_vec_textures[0], (unsigned int)mat->m_vec_textures.size ( ) );

			auto slot = mesh->getMaterialSlot ( i );
			context->drawIndexedTriangleList ( (unsigned int)slot.num_indices, (unsigned int)slot.start_index, 0 );
		}
	}

	swapChain->present ( true );
}

RenderSystem* GraphicsEngine::getRenderSystem ( )
{
	return m_render_system;
}

void GraphicsEngine::addComponent ( Component* component )
{
	if (auto c = dynamic_cast<MeshComponent*>(component))
		m_meshes.emplace ( c );
	else if (auto c = dynamic_cast<CameraComponent*>(component))
	{
		if (!m_cameras.size ( )) m_cameras.emplace ( c );
	}
	else if (auto c = dynamic_cast<LightComponent*>(component))
	{
		if (!m_lights.size ( )) m_lights.emplace ( c );
	}
	else if (auto c = dynamic_cast<TerrainComponent*>(component))
	{
		if (!m_terrains.size ( )) m_terrains.emplace ( c );
	}
}

void GraphicsEngine::removeComponent ( Component* component )
{
	if (auto c = dynamic_cast<MeshComponent*>(component))
		m_meshes.erase ( c );
	else if (auto c = dynamic_cast<CameraComponent*>(component))
		m_cameras.erase ( c );
	else if (auto c = dynamic_cast<LightComponent*>(component))
		m_lights.erase ( c );
	else if (auto c = dynamic_cast<TerrainComponent*>(component))
	{
		m_terrains.erase ( c );
	}
}

GraphicsEngine::~GraphicsEngine ( )
{
	delete this->m_render_system;
}