#include <Entity/Component.hpp>
#include <Entity/Entity.hpp>

Component::Component ( )
{
}

Component::~Component ( )
{
}

void Component::release ( )
{
	m_entity->removeComponent ( m_typeId );
}

Entity* Component::getEntity ( )
{
	return m_entity;
}

void Component::onCreateInternal ( )
{

}