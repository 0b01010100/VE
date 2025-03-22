#pragma once
#include <Resource/Resource.hpp>

class Texture : public Resource
{
public:
	Texture( std::string_view full_path, ResourceManager* manager );
	const Texture2DPtr& getTexture ( );
private:
	Texture2DPtr m_texture;
	friend class Material;
} ;
