#pragma once
#include <Resource/Resource.hpp>
#include <vector>


class GraphicsEngine;
class Material : public Resource
{
public:
	Material(std::string_view path_vs_ps, ResourceManager* manager);
	Material(std::string_view path_vs, std::string_view path_ps, ResourceManager* manager);
	Material(const MaterialPtr& material, ResourceManager* manager );

	void addTexture(const TexturePtr& texture);
	void removeTexture(unsigned int index);
	void setData(void* data, unsigned int size);

	void setCullMode( const CullMode& mode) ;
	const CullMode getCullMode() ;
private:
	VertexShaderPtr m_vertex_shader;
	PixelShaderPtr m_pixel_shader;
	UniformBufferPtr m_constant_buffer;
	std::vector<Texture2DPtr> m_vec_textures;
	CullMode m_cull_mode = CullMode::Back;
private:
	friend class GraphicsEngine;
};
