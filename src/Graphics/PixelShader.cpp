#include <Graphics/PixelShader.hpp>

PixelShader::PixelShader(std::string_view shader_code, RenderSystem * system)
:m_system(system)
{
    std::string code = loadShaderFile(shader_code);

    // Create the vertex shader
    this->m_shader = glCreateShader(GL_FRAGMENT_SHADER);
    if (this->m_shader == 0) {
        throw std::runtime_error("Failed to create vertex shader");
    }

    // OpenGL makes an internal copy of the source code
    const char* glcode = code.c_str();
    GLint length = static_cast<GLint>(code.size());
    glShaderSource(this->m_shader, 1, &glcode, &length);

    // Compile the shader
    glCompileShader(this->m_shader);

    // Check for compilation errors
    GLint success;
    glGetShaderiv(this->m_shader, GL_COMPILE_STATUS, &success);
    
    if (!success) {
        GLint maxLength = 0;
        glGetShaderiv(this->m_shader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(this->m_shader, maxLength, &maxLength, errorLog.data());

        // Clean up shader
        glDeleteShader(this->m_shader);

        throw std::runtime_error("Pixel shader compilation failed: " + std::string(errorLog.data()));
    }
}

bool PixelShader::looksLikeFile(std::string_view str) {
    size_t dotPos = str.rfind('.');
    if (dotPos == std::string_view::npos) {
        return false;
    }

    std::string_view ext = str.substr(dotPos);
    static constexpr std::array<std::string_view, 4> shaderExts = {
        ".frag", ".glsl", ".fs", ".shader"
    };
    
    for (std::string_view validExt : shaderExts) {
        if (ext == validExt) {
            return true;
        }
    }

    return false;
}

// Load shader file (optimized, minimal allocations)
std::string PixelShader::loadShaderFile(std::string_view shader_code) {
    if (!looksLikeFile(shader_code)) {
        return std::string(shader_code); // If it's not a file, return the input string
    }

    std::ifstream file(shader_code.data(), std::ios::ate | std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open shader file: " + std::string(shader_code));
    }

    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::string final_code(fileSize, '\0');
    file.read(final_code.data(), fileSize);

    return final_code;
}

PixelShader::~PixelShader(){
    glDeleteShader(this->m_shader);
}