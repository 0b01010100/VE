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
    void BindVUniform(UniformBuffer* ub);

    void BindVertexBuffer(VertexBuffer* vb);
    //void BindTexure(Texture * )
    void SetCullMode(CullMode mode);
    
private:
    struct{
        unsigned int vs, ps, spo;
    }m_ShaderProgram = {0,0,0};
private:
    friend class RenderSystem;
};