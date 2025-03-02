#include <Graphics/RenderSystem.hpp>

RenderSystem::RenderSystem()
{
    this->m_pipeline = new Pipeline();
}

VertexShader *RenderSystem::createVertexShader(std::string_view shader_code)
{
    return new VertexShader(shader_code, this);
}

PixelShader *RenderSystem::createPixelShader(std::string_view shader_code)
{
    return new PixelShader(shader_code, this);
}

VertexBuffer *RenderSystem::createVertexBuffer(void *vertices, size_t vertex_size, size_t vertex_count, Attributes vertex_attribs)
{
    return new VertexBuffer(vertices, vertex_size, vertex_count, vertex_attribs, this);
}

UniformBuffer* RenderSystem::createUniformBuffer
(
    void* buffer, 
    unsigned int buffer_size
)
{
    return new UniformBuffer(buffer, buffer_size, this);
}

Pipeline *RenderSystem::getPipline() const
{
    return this->m_pipeline;
}

RenderSystem::~RenderSystem()
{
    delete this->m_pipeline;
}
