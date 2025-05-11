#include <Graphics/RenderSystem.hpp>
//SWAP CHAIN
#include <Graphics/SwapChain.hpp>
#include <Graphics/VertexBuffer.hpp>
#include <Graphics/IndexBuffer.hpp>
#include <Graphics/UniformBuffer.hpp>
#include <Graphics/VertexShader.hpp>
#include <Graphics/PixelShader.hpp>
#include <Graphics/Texture2D.hpp>
#include <Graphics/DeviceContext.hpp>

RenderSystem::RenderSystem()
{
    this->m_imm_device_context = std::make_shared<DeviceContext>( this );
}

SwapChainPtr RenderSystem::createSwapChain(void *hwnd, unsigned int width, unsigned int height)
{
    return std::make_shared<SwapChain>(hwnd, width, height, this);
}

VertexShaderPtr RenderSystem::createVertexShader(std::string_view shader_code)
{
    return std::make_shared<VertexShader>(shader_code, this);
}

PixelShaderPtr RenderSystem::createPixelShader(std::string_view shader_code)
{
    return std::make_shared<PixelShader>(shader_code, this);
}

VertexBufferPtr RenderSystem::createVertexBuffer(void *vertices, size_t vertex_size, size_t vertex_count, Attributes vertex_attribs)
{
    return std::make_shared<VertexBuffer>(vertices, vertex_size, vertex_count, vertex_attribs, this);
}

UniformBufferPtr RenderSystem::createUniformBuffer
(
    void* buffer, 
    unsigned int buffer_size,
    SaveType save_type
)
{
    return std::make_shared<UniformBuffer>(
        buffer, buffer_size, save_type, this
    );
}


UniformBufferPtr RenderSystem::createUniformBuffer
(
    SaveType save_type
)
{
    return std::make_shared<UniformBuffer>(
        save_type, this
    );
}

IndexBufferPtr RenderSystem::createIndexBuffer
(
    void* indies, 
    unsigned int index_size, 
    unsigned int index_count
)
{
    return std::make_shared<IndexBuffer>(indies, index_size, index_count, this);
}

Texture2DPtr RenderSystem::createTexture(const std::string_view full_path)
{
    return std::make_shared<Texture2D>(full_path);
}

Texture2DPtr RenderSystem::createTexture(const Rect<>& size, Type type)
{
    return std::make_shared<Texture2D>(size, type);
}

DeviceContextPtr RenderSystem::getImmediateDeviceContext()
{
    return this->m_imm_device_context;
}