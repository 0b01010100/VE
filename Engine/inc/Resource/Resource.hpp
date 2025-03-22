#pragma once
#include <Prerequisites.hpp>
#include <string>

class Resource
{
public:
	Resource(std::vector<std::string_view> full_paths, ResourceManager* manager);
	Resource(std::string_view full_path, ResourceManager* manager);

	virtual ~Resource();
protected:
	std::vector<std::string> m_full_paths;
	ResourceManager* m_manager = nullptr;
};
