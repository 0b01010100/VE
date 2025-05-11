#pragma once
#include <Prerequisites.hpp>
#include <optional>
class DeviceContext
{
public:
    DeviceContext(RenderSystem * system);
    ~DeviceContext();
public: 
    void setVertexShader(VertexShaderPtr vs);
    void setPixelShader(PixelShaderPtr ps);
    void setUniformBuffer(UniformBufferPtr ub, unsigned int bindingPoint);
    void setVertexBuffer(VertexBufferPtr vb);
    void setIndexBuffer(IndexBufferPtr ib);
    void setTexture(Texture2DPtr* tex, unsigned int num_textures);
    
    void setAttributes(Attributes attribs);

    void setRenderMode(RenderMode mode);
    void setCullMode(CullMode mode);
    
    void drawTrianlgeList(int vertex_count, int start_vertex_index);
    void drawIndexedTriangleList(int index_count, int start_vertex_index, int start_index_location);
    void drawTrianlgeStrip(int vertex_count, int start_vertex_index);

    void clearRenderTargetColor(const SwapChainPtr& swap_chain, float red, float green, float blue, float alpha);
    void clearDepthStencil(const SwapChainPtr& swap_chain);

    void setViewportSize(int width, int height);

private:
    struct{
        unsigned int vs, ps, spo, ubo;
    }m_ShaderProgram = {0,0,0,0};
    RenderSystem * m_system;
private:
    friend class RenderSystem;
};