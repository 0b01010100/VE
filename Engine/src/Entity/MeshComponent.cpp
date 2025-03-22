#include <Entity/MeshComponent.hpp>
#include <Entity/Entity.hpp>
#include <Game/World.hpp>
#include <Game/Game.hpp>
#include <Graphics/GraphicsEngine.hpp>

MeshComponent::MeshComponent ( )
{
}

MeshComponent::~MeshComponent ( )
{
	m_entity->getWorld ( )->getGame ( )->getGraphicsEngine ( )->removeComponent ( this );
}

void MeshComponent::setMesh ( const MeshPtr& mesh )
{
	m_mesh = mesh;
}

const MeshPtr& MeshComponent::getMesh ( )
{
	return m_mesh;
}

void MeshComponent::addMaterial ( const MaterialPtr& material )
{
	this->m_materials.push_back ( material );
}

void MeshComponent::removeMaterial ( ui32 index )
{	
	if (index >= m_materials.size ( )) return;
	this->m_materials.erase ( m_materials.begin ( ) + index );
}
const std::vector<MaterialPtr>& MeshComponent::getMaterials ( )
{
	return m_materials;
}

void MeshComponent::onCreateInternal ( )
{
	m_entity->getWorld ( )->getGame ( )->getGraphicsEngine ( )->addComponent ( this );
}