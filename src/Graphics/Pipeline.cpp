#include <Graphics/Pipeline.hpp>

Pipeline::Pipeline(){
    this->m_ShaderProgram.spo = glCreateProgram();
}

void Pipeline::BindVertexShader(VertexShader* vs)
{
    if (m_ShaderProgram.vs) {
        glDetachShader(m_ShaderProgram.spo, m_ShaderProgram.vs);
    }
    
    m_ShaderProgram.vs = vs->m_shader;
    glAttachShader(m_ShaderProgram.spo, vs->m_shader);
    glLinkProgram(m_ShaderProgram.spo);
    
    glUseProgram(m_ShaderProgram.spo);
}

void Pipeline::BindPixelShader(PixelShader* ps)
{
    if (m_ShaderProgram.ps) {
        glDetachShader(m_ShaderProgram.spo, m_ShaderProgram.ps);
    }
    
    m_ShaderProgram.ps = ps->m_shader;
    glAttachShader(m_ShaderProgram.spo, ps->m_shader);
    glLinkProgram(m_ShaderProgram.spo);
    

    glUseProgram(m_ShaderProgram.spo);
}

void Pipeline::BindVUniform(UniformBuffer *ub, unsigned int bindingPoint)
{
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, ub->m_buffer_id);
}

void Pipeline::BindVertexBuffer(VertexBuffer* vb)
{
    glBindVertexArray(vb->m_vba);
    glBindBuffer(GL_ARRAY_BUFFER, vb->m_vbo);
}

void Pipeline::BindIndexBuffer(IndexBuffer* ib)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->m_ebo);
}

void Pipeline::BindTexture2D(Texture2D* tex, unsigned int unit)
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, tex->m_texture);
}

Pipeline::~Pipeline()
{
    glDeleteProgram(this->m_ShaderProgram.spo);
}

void Pipeline::SetRenderMode(RenderMode mode)
{
    if (mode == 0) // Solid mode
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else if (mode == 1) // Wireframe mode
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else if (mode == 2) // Point mode
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
}


void Pipeline::SetCullMode(CullMode mode)
{
    if (mode == CullMode::None) {
        glDisable(GL_CULL_FACE);
        return;
    }

    glEnable(GL_CULL_FACE);

    switch (mode) {
        case CullMode::Front:
            glCullFace(GL_FRONT);
            break;
        case CullMode::Back:
            glCullFace(GL_BACK);
            break;
        case CullMode::FrontAndBack:
            glCullFace(GL_FRONT_AND_BACK);
            break;
        default:
            break;
    }
}

void Pipeline::ClearRenderTargetColor(float red, float green, float blue, float alpha){
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Pipeline::SetViewportSize(int width, int height){
    glViewport(0, 0, width, height);
}

void Pipeline::DrawTrianlgeList(int vertex_count, int start_vertex_index){
    glDrawArrays(GL_TRIANGLES, start_vertex_index, vertex_count);
}

void Pipeline::DrawIndexedList(int index_count, int start_vertex_index, int start_index_location){
    glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, (void*)(start_index_location * sizeof(GLuint)));
}

void Pipeline::DrawTrianlgeStrip(int vertex_count, int start_vertex_index){
    glDrawArrays(GL_TRIANGLE_STRIP, start_vertex_index, vertex_count);
}