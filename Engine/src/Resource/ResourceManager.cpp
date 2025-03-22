#include <Resource/ResourceManager.hpp>
#include <Resource/Material.hpp>
#include <Resource/Texture.hpp>
#include <Resource/Mesh.hpp>
#include <filesystem>

ResourceManager::ResourceManager(Game* game) : m_game(game)
{
}
Game *ResourceManager::getGame()
{
    return this->m_game;
}

ResourcePtr ResourceManager::createResourceFromFileConcrete(std::string_view file_path)
{
    std::filesystem::path resourePath = file_path;//Assign the wchar_t path to a file system variable to make handling the path easier 
	auto ext = resourePath.extension();//Get the extension of the file
    
	auto it = m_map_resources.find(file_path.data());//Check if the Resource exsitst 
	//Since the find function dosn't throught errors when something is not found checking to see if it != m_map_resources.end() will check if the data we are looking for is past the end of the list meaning it not there.
	if (it != m_map_resources.end()) 
	{
        auto mat = std::dynamic_pointer_cast<Material>(it->second);
		if (mat) return std::make_shared<Material>(mat, this);
		return it->second;//Return second if it was already created. 
	}
	if (!std::filesystem::exists(resourePath)) return ResourcePtr();//Checks if the file Path is real
    
	ResourcePtr resPtr;
    
	if (!ext.compare (L".obj"))
	{ //Checks to see if the extension is a object file extension
    	resPtr = std::make_shared<Mesh> ( resourePath.string().c_str(), this);
	}
	else if (
			!ext.compare(L".jpg") || 
			!ext.compare(L".png") || 
			!ext.compare (L".bmp")
			)
	{ //Checks to see if the extension is a image file extension
    	resPtr = std::make_shared<Texture> ( resourePath.string().c_str(), this);
	}
	else if (
			!ext.compare(L".glsl") || 
			!ext.compare(L".fx" )  ||
			!ext.compare(L".frag") || 
			!ext.compare(L".vert") || 
			!ext.compare(L".shader")
			)
	{ //Checks to see if the extension is a shader file extension
    	resPtr = std::make_shared<Material>( resourePath.string().c_str(), this);
	}
	if (resPtr) //Checks to see if the extension is .obj
	{
        m_map_resources.emplace (file_path, resPtr);
		return resPtr;
	}	
	return resPtr;
}

ResourceManager::~ResourceManager()
{
}