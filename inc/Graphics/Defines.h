#pragma once

// STL
#include <array>
#include <string_view>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <memory>

// OpenGL
#include <glad/glad.h>

// Enums/structs

enum VGenum {
    VG_UNSIGNED_BYTE  = 0x1401,
    VG_SHORT          = 0x1402,
    VG_UNSIGNED_SHORT = 0x1403,
    VG_INT            = 0x1404,
    VG_UNSIGNED_INT   = 0x1405,
    VG_FLOAT          = 0x1406
};

enum CullMode {
    None,         // Disable face culling
    Front,        // Cull front faces
    Back,         // Cull back faces (default)
    FrontAndBack  // Cull both front and back faces
};

enum SaveType {
    STATIC,
    DYNAMIC
};

// struct for input layout
struct Attribute {
    uint32_t index;      // Shader attribute location
    int32_t size;        // Number of components (e.g., 3 for vec3)
    VGenum type;         // Data type (e.g., float)
    bool normalized;     // Normalize fixed-point data
    uint32_t stride;     // Distance between consecutive attributes
    const void* offset;  // Offset within the buffer
};

static const char* default_vs =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main() {\n"
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n";

static const char* default_ps =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";

// Vertex attributes dynamic array
using Attributes = std::vector<Attribute>;

// Forward declarations

class VertexShader;
class IndexBuffer;
class PixelShader;
class VertexBuffer;
class UniformBuffer;
class RenderSystem;
class Pipeline;

// Our includes
#include <Graphics/VertexShader.hpp>
#include <Graphics/IndexBuffer.hpp>
#include <Graphics/PixelShader.hpp>
#include <Graphics/VertexBuffer.hpp>
#include <Graphics/UniformBuffer.hpp>
#include <Graphics/RenderSystem.hpp>
#include <Graphics/Pipeline.hpp>

// Smart Pointers
