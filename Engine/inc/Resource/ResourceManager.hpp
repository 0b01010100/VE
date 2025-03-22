#pragma once
#include <unordered_map>
#include <string>
#include <Prerequisites.hpp>
#include <Resource/Resource.hpp>

class ResourceManager
{
public:
	ResourceManager(Game * game);
	~ResourceManager();
	template < typename T >
	std::shared_ptr< T > createResourceFromFile ( std::string_view file_path ) 
	{
		return std::dynamic_pointer_cast<T>(createResourceFromFileConcrete ( file_path));
	}

	Game* getGame ( );
private:
	ResourcePtr createResourceFromFileConcrete( std::string_view file_path);
private:
	std::unordered_map<std::string, ResourcePtr> m_map_resources;
	Game* m_game = nullptr;
};