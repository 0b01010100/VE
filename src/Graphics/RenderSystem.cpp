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
    unsigned int buffer_size,
    SaveType save_type
)
{
    return new UniformBuffer(buffer, buffer_size, save_type, this);
}

IndexBuffer* RenderSystem::createIndexBuffer
(
    void* indies, 
    unsigned int index_size, 
    unsigned int index_count
)
{
    return new IndexBuffer(indies, index_size, index_count, this);
}

Texture2D *RenderSystem::createTexture(const std::string_view full_path)
{
    return new Texture2D(full_path);
}

Texture2D *RenderSystem::createTexture(int width, int height, VType type)
{
    return new Texture2D(width, height, type);
}

Pipeline *RenderSystem::getPipline() const
{
    return this->m_pipeline;
}

RenderSystem::~RenderSystem()
{
    delete this->m_pipeline;
}
