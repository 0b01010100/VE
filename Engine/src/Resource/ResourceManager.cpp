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

ResourceManager::~ResourceManager()
{
}