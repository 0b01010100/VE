#pragma once
#include <Prerequisites.hpp>
#include <Math/Rect.hpp>

class RenderSystem
{
public: 
    SwapChainPtr createSwapChain(void* hwnd, unsigned int width, unsigned int height);
    VertexShaderPtr createVertexShader(std::string_view shader_code);
    PixelShaderPtr createPixelShader(std::string_view shader_code);
    VertexBufferPtr createVertexBuffer
    (
        void * vertices, 
        size_t vertex_size, 
        size_t vertex_count, 
        Attributes vertex_attribs
    );
    UniformBufferPtr createUniformBuffer
    (
        void* buffer, 
        unsigned int buffer_size,
        SaveType save_type
    );
    UniformBufferPtr createUniformBuffer
    (
        SaveType save_type
    );

    IndexBufferPtr createIndexBuffer
    (
        void* indies, 
        unsigned int index_size, 
        unsigned int index_count
    );
    Texture2DPtr createTexture(std::string_view full_path);
    Texture2DPtr createTexture(const Rect<>& size, Type type);
    DeviceContextPtr getImmediateDeviceContext();
private:
    DeviceContextPtr m_imm_device_context;
    RenderSystem();
    friend class SwapChain;
    friend class VertexBuffer;
    friend class IndexBuffer;
    friend class UniformBuffer;
    friend class VertexShader;
    friend class PixelShader;
    friend class Texture2D;
    friend class GraphicsEngine;
    friend class DeviceContext;
};