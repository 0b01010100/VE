#pragma once
#include <Graphics/Defines.h>

class RenderSystem
{
public: 
    
    VertexShader* createVertexShader(std::string_view shader_code);
    PixelShader* createPixelShader(std::string_view shader_code);
    VertexBuffer* createVertexBuffer
    (
        void * vertices, 
        size_t vertex_size, 
        size_t vertex_count, 
        Attributes vertex_attribs
    );
    UniformBuffer* createUniformBuffer
    (
        void* buffer, 
        unsigned int buffer_size
    );

    Pipeline* getPipline() const;
private:
    Pipeline* m_pipeline = nullptr;
    RenderSystem();
    ~RenderSystem();
    friend class Graphics;
};