#pragma once
#include <Prerequisites.hpp>
#include <Entity/Component.hpp>
#include <vector>

class MeshComponent : public Component
{
public:
	MeshComponent ( );
	virtual ~MeshComponent ( ); 

	void setMesh ( const MeshPtr& mesh );
	const MeshPtr& getMesh ( );

	void addMaterial ( const MaterialPtr& material );
	void removeMaterial ( ui32 index );
	const std::vector<MaterialPtr>& getMaterials ( );
protected:
	void onCreateInternal ( ) override;
private:
	MeshPtr m_mesh; 
	std::vector<MaterialPtr> m_materials;
};
