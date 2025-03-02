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
    
    //void BindTexure(Texture * )
    void SetCullMode(CullMode mode);
    
private:
    struct{
        unsigned int vs, ps, spo;
    }m_ShaderProgram = {0,0,0};
private:
    friend class RenderSystem;
};