#include <Resource/Material.hpp>
#include <Graphics/VertexShader.hpp>
#include <Graphics/PixelShader.hpp>
#include <Graphics/UniformBuffer.hpp>
#include <Resource/ResourceManager.hpp>
#include <Game/Game.hpp>
#include <Graphics/GraphicsEngine.hpp>
#include <Graphics/RenderSystem.hpp>
#include <Resource/Texture.hpp>
#include <Graphics/Texture2D.hpp>

Material::Material(std::string_view path, ResourceManager* manager) : Resource(path, manager)
{
	auto rsys = m_manager->getGame()->getGraphicsEngine()->getRenderSystem();

	m_vertex_shader = rsys->createVertexShader(path);
	if (!m_vertex_shader) std::runtime_error("Material not created successfully");

	m_pixel_shader = rsys->createPixelShader(path);
	if (!m_pixel_shader) std::runtime_error( "Material not created successfully");
}

Material::Material(std::string_view path_vs, std::string_view path_ps, ResourceManager* manager) 
: Resource({path_vs, path_vs}, manager)
{
	auto rsys = m_manager->getGame()->getGraphicsEngine()->getRenderSystem();

	m_vertex_shader = rsys->createVertexShader(path_vs);
	if (!m_vertex_shader) std::runtime_error("Material not created successfully");

	m_pixel_shader = rsys->createPixelShader(path_ps);
	if (!m_pixel_shader) std::runtime_error( "Material not created successfully");

}

Material::Material (const MaterialPtr& material, ResourceManager* manager) : Resource ("", manager)
{
	m_vertex_shader = material->m_vertex_shader;
	m_pixel_shader = material->m_pixel_shader;
}

void Material::addTexture(const TexturePtr& texture)
{
	m_vec_textures.push_back(texture->m_texture);
}

void Material::removeTexture(unsigned int index)
{
	if (index >= this->m_vec_textures.size()) return;
	m_vec_textures.erase(m_vec_textures.begin() + index);
}

void Material::setData(void* data, unsigned int size)
{
	auto rsys = m_manager->getGame()->getGraphicsEngine()->getRenderSystem();
	if (!m_constant_buffer)
		m_constant_buffer = rsys->createUniformBuffer(data, size, SaveType::STATIC);
	else
		m_constant_buffer->Update(data);
}

void Material::setCullMode(const CullMode& mode)
{
	m_cull_mode = mode;
}

const CullMode Material::getCullMode()
{
	return m_cull_mode;
}