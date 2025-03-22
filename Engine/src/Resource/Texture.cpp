#include <Resource/Texture.hpp>
#include <Resource/ResourceManager.hpp>
#include <Game/Game.hpp>
#include <Graphics/GraphicsEngine.hpp>
#include <Graphics/RenderSystem.hpp>
#include <Graphics/Texture2D.hpp>

Texture::Texture(std::string_view full_path, ResourceManager* manager) : Resource(full_path, manager)
{
	m_texture = manager->getGame()->getGraphicsEngine()->getRenderSystem()->createTexture(full_path);
}

const Texture2DPtr& Texture::getTexture()
{
	return this->m_texture;
}