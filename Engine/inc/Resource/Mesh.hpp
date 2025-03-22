#pragma once
#include <Resource/Resource.hpp>
#include <Graphics/VertexBuffer.hpp>
#include <Graphics/IndexBuffer.hpp>
#include <Math/Vector3D.hpp>
#include <Math/Vector2D.hpp>

#include <vector>
#include <Math/VertexMesh.hpp>

struct MaterialSlot 
{
	size_t start_index = 0;
	size_t num_indices = 0;
	size_t material_id = 0;
};

class Mesh : public Resource
{
public:
	Mesh(std::string_view full_path, ResourceManager* manager);
	Mesh
	( 
		VertexMesh* vertex_list_data, unsigned int vertex_list_size,
		unsigned int* index_list_data, unsigned int index_list_size,
		MaterialSlot* material_slot_list, unsigned int material_slot_list_size,
		ResourceManager* manager
	);
	~Mesh();

	MaterialSlot getMaterialSlot(unsigned int slot);
	size_t getNumMaterialSlots();
private:
	void computeTangents(
		const Vector3D& v0, const Vector3D& v1, const Vector3D& v2,
		const Vector2D& t0, const Vector2D& t1, const Vector2D& t2,
		Vector3D& tangent, Vector3D& binormal
	);
private:
	VertexBufferPtr m_vertex_buffer;
	IndexBufferPtr m_index_buffer;
	Attributes m_attributes;
	std::vector<struct MaterialSlot> m_mat_slots;
private:
	friend class GraphicsEngine; 
};
