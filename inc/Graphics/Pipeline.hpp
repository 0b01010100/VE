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
    void ClearRenderTargetColor(float red, float green, float blue, float alpha);
    void SetViewportSize(int width, int height);
    void DrawTrianlgeList(int vertex_count, int start_vertex_index);
    void DrawIndexedList(int index_count, int start_vertex_index, int start_index_location);
    void DrawTrianlgeStrip(int vertex_count, int start_vertex_index);
    // might add more drawing types soon

private:
    struct{
        unsigned int vs, ps, spo;
    }m_ShaderProgram = {0,0,0};
private:
    friend class RenderSystem;
};