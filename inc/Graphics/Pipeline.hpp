#pragma once
#include <Graphics/Defines.h>

class Pipeline
{
private:
    Pipeline();
    ~Pipeline();
public: 
    void BindVertexShader(VertexShader* vs);
    void BindPixelShader(PixelShader* ps);
    void BindVUniform(UniformBuffer* ub, unsigned int bindingPoint);
    void BindVertexBuffer(VertexBuffer* vb);
    void BindIndexBuffer(IndexBuffer* ib);
    void BindTexture2D(Texture2D* tex, unsigned int unit);
    void SetRenderMode(RenderMode mode);
    void SetCullMode(CullMode mode);
    
private:
    struct{
        unsigned int vs, ps, spo;
    }m_ShaderProgram = {0,0,0};
private:
    friend class RenderSystem;
};