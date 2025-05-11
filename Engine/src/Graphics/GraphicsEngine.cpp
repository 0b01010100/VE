#include <Graphics/GraphicsEngine.hpp>
#include <Graphics/RenderSystem.hpp>
#include <Graphics/DeviceContext.hpp>
#include <Graphics/SwapChain.hpp>
#include <Graphics/UniformBuffer.hpp>

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

#include <Input/InputSystem.hpp>

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

struct alignas(16) UniformData
{
	Matrix4x4 world;
	Matrix4x4 view;
	Matrix4x4 proj;
	Vector4D cameraPosition;
	LightData light;
	//TerrainData terrain;
};


GraphicsEngine::GraphicsEngine ( Game* game ) : m_game ( game )
{
	this->m_render_system = new RenderSystem();
	auto display = game->m_display.get();
	Rect screen_size = display->getScreenSize();
	display->m_swapChain = this->m_render_system->createSwapChain 
	( 
		display->getHandle(), 
		screen_size.width, 
		screen_size.height 
	);
	this->m_global_ubo_buffer = std::make_shared<UniformBuffer>( SaveType::DYNAMIC, this->getRenderSystem() );
}

void GraphicsEngine::update ( )
{
	auto context = m_render_system->getImmediateDeviceContext ( );

	auto swapChain = m_game->m_display->m_swapChain;

	context->clearRenderTargetColor ( swapChain, 0, 0, 0, 1 );
	auto winSize = m_game->m_display->getClientSize ( );
	context->setViewportSize ( winSize.width, winSize.height );

	UniformData m_global_ubo = {};

	for (auto c : m_cameras)
	{
		auto t = c->getEntity ( )->getTransform ( );
		m_global_ubo.cameraPosition = t->getPosition ( );
		c->setScreenArea ( winSize );
		c->getViewMatrix ( m_global_ubo.view );
		//m_global_ubo.view.setLookAt({0,0,5},{0,0,0},{0,1,0});
		c->getProjectionMatrix ( m_global_ubo.proj );
	}

	for (auto l : m_lights)
	{
		auto t = l->getEntity ( )->getTransform ( );
		Matrix4x4 w;
		t->getWorldMatrix ( w );
		m_global_ubo.light.direction = w.getZDirection ( );
		m_global_ubo.light.color = l->getColor ( );
	}

	for (auto m : m_meshes)
	{
		auto transform = m->getEntity ( )->getTransform ( );
		transform->getWorldMatrix ( m_global_ubo.world );
		
		auto mesh = m->getMesh ();
		
		context->setVertexBuffer ( mesh->m_vertex_buffer );
		context->setIndexBuffer ( mesh->m_index_buffer );
		
		const auto materials = m->getMaterials ( );

		for (auto i = 0; i < mesh->getNumMaterialSlots ( ); i++)
		{
			if (i >= materials.size ( )) break;
			auto mat = materials[i].get ( );

			context->setCullMode ( mat->getCullMode ( ) );
			context->setAttributes( mesh->m_attributes );
			

			context->setVertexShader ( mat->m_vertex_shader );
			context->setPixelShader ( mat->m_pixel_shader );
			
			this->m_global_ubo_buffer->Update(&m_global_ubo, sizeof(m_global_ubo));
			context->setUniformBuffer(m_global_ubo_buffer, 0);

			context->setTexture ( &mat->m_vec_textures[0], (unsigned int)mat->m_vec_textures.size ( ) );

			auto slot = mesh->getMaterialSlot ( i );
			context->drawIndexedTriangleList ( (unsigned int)slot.num_indices, (unsigned int)slot.start_index, 0 );
		}
	}

    swapChain->present(true);
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