#include <Graphics/Pipeline.hpp>

Pipeline::Pipeline(){
    this->m_ShaderProgram.spo = glCreateProgram();
}

void Pipeline::BindVertexShader(VertexShader* vs)
{
    if (!vs) {
        throw std::invalid_argument("Null vertex shader provided");
    }

    if (m_ShaderProgram.vs) {
        glDetachShader(m_ShaderProgram.spo, m_ShaderProgram.vs);
    }
    
    m_ShaderProgram.vs = vs->m_shader;
    glAttachShader(m_ShaderProgram.spo, vs->m_shader);
    glLinkProgram(m_ShaderProgram.spo);
    
    GLint success;
    glGetProgramiv(m_ShaderProgram.spo, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(m_ShaderProgram.spo, 512, NULL, infoLog);
        throw std::runtime_error("Shader program linking failed: " + std::string(infoLog));
    }
    glUseProgram(m_ShaderProgram.spo);
}

void Pipeline::BindPixelShader(PixelShader* ps)
{
    if (!ps) {
        throw std::invalid_argument("Null pixel shader provided");
    }

    if (m_ShaderProgram.ps) {
        glDetachShader(m_ShaderProgram.spo, m_ShaderProgram.ps);
    }
    
    m_ShaderProgram.ps = ps->m_shader;
    glAttachShader(m_ShaderProgram.spo, ps->m_shader);
    glLinkProgram(m_ShaderProgram.spo);
    
    GLint success;
    glGetProgramiv(m_ShaderProgram.spo, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(m_ShaderProgram.spo, 512, NULL, infoLog);
        throw std::runtime_error("Shader program linking failed: " + std::string(infoLog));
    }
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
