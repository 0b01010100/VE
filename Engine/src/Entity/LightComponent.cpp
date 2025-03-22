#include <Entity/LightComponent.hpp>
#include <Entity/Entity.hpp>
#include <Game/World.hpp>
#include <Game/Game.hpp>
#include <Graphics/GraphicsEngine.hpp>

LightComponent::LightComponent ( )
{
}

LightComponent::~LightComponent ( )
{
	m_entity->getWorld ( )->getGame ( )->getGraphicsEngine ( )->removeComponent ( this );
}

void LightComponent::setColor ( const Vector4D& color )
{
	this->m_color = color;
}

Vector4D LightComponent::getColor ( )
{
	return m_color;
}

void LightComponent::onCreateInternal ( )
{
	m_entity->getWorld ( )->getGame ( )->getGraphicsEngine ( )->addComponent ( this );
}