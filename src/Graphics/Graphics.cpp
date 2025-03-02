#include <Graphics/Graphics.hpp>

Graphics::Graphics()
{
    this->m_system = new RenderSystem();
}

RenderSystem *Graphics::getRenderSystem() const
{
    return this->m_system;
}

Graphics::~Graphics()
{
    delete m_system;
}