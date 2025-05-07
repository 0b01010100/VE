#pragma once
#include <unordered_map>
#include <string>
#include <Prerequisites.hpp>
#include <Resource/Resource.hpp>
#include <memory>
#include <type_traits>
#include <utility>

class ResourceManager
{
public:
	ResourceManager(Game * game);
	~ResourceManager();

	
	template <typename T, typename... Args, typename = std::enable_if_t<std::is_constructible_v<T, Args..., std::nullptr_t>>>
	std::shared_ptr<T> createResource(Args&&... args) {
    	return std::make_shared<T>(std::forward<Args>(args)..., this);
	}

	Game* getGame ( );
private:
	//ResourcePtr createResourceFromFileConcrete( std::string_view file_path);
private:
	std::unordered_map<std::string, ResourcePtr> m_map_resources;
	Game* m_game = nullptr;
};