#include <Resource/Resource.hpp>

// turn std::vector to std::span+
Resource::Resource(std::vector<std::string_view> full_paths, ResourceManager* manager ) 
: m_manager(manager)
{
    m_full_paths.reserve(full_paths.size());
    for (const auto& path : full_paths) {
        m_full_paths.emplace_back(path);
    }
}

Resource::Resource(std::string_view full_path, ResourceManager* manager) 
: m_manager(manager)
{
    m_full_paths.reserve(1);
    m_full_paths.emplace_back(full_path);
}

Resource::~Resource()
{
}