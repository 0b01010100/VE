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
        unsigned int buffer_size,
        SaveType save_type
    );

    IndexBuffer* createIndexBuffer
    (
        void* indies, 
        unsigned int index_size, 
        unsigned int index_count
    );
    Texture2D* createTexture(const std::string_view full_path);
    Texture2D* createTexture(int width, int height, VType type);

    Pipeline* getPipline() const;
private:
    Pipeline* m_pipeline = nullptr;
    RenderSystem();
    ~RenderSystem();
    friend class Graphics;
};