#pragma once

// STL
#include <string_view>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <iostream>
#include <stdexcept>
#include <filesystem>
#include <fstream>

// Enums/structs

enum class Type : int
{
    Normal,
    RenderTarget,
    DepthStencil
};

enum Venum : int {
    VUNSIGNED_BYTE  = 0x1401,
    VSHORT          = 0x1402,
    VUNSIGNED_SHORT = 0x1403,
    VINT            = 0x1404,
    VUNSIGNED_INT   = 0x1405,
    VFLOAT          = 0x1406
};

enum RenderMode : int
{
    SOLID,
    WIRE,
    POINT
};

enum SaveType : int {
    STATIC,
    DYNAMIC
};

// struct for input layout
struct Attribute {
    uint32_t index;      // Shader attribute location
    int32_t size;        // Number of components (e.g., 3 for vec3)
    Venum type;         // Data type (e.g., float)
    bool normalized;     // Normalize fixed-point data
    uint32_t stride;     // Distance between consecutive attributes
    const void* offset;  // Offset within the buffer
};

// Vertex attributes dynamic array
using Attributes = std::vector<Attribute>;

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

class SwapChain;
class DeviceContext;
class VertexBuffer;
class IndexBuffer;
class UniformBuffer;
class VertexShader;
class PixelShader;
class Texture2D;
class RenderSystem;
class GraphicsEngine;
class Resource;
class ResourceManager;
class Texture;
class TextureManager;
class MeshManager;
class Mesh;
class Material;
//class FrameBuffer;
class Window;
class Game;
class Display;
class InputSystem;

class Component;
class TransformComponent;
class MeshComponent;
class CameraComponent;
class LightComponent;
class TerrainComponent;


class Entity;
class World;

typedef std::shared_ptr<SwapChain> SwapChainPtr;
typedef std::shared_ptr<DeviceContext> DeviceContextPtr;
typedef std::shared_ptr<VertexBuffer> VertexBufferPtr;
typedef std::shared_ptr<IndexBuffer> IndexBufferPtr;
typedef std::shared_ptr<UniformBuffer> UniformBufferPtr;
typedef std::shared_ptr<VertexShader> VertexShaderPtr;
typedef std::shared_ptr<PixelShader> PixelShaderPtr;
typedef std::shared_ptr<Texture2D> Texture2DPtr;
typedef std::shared_ptr<Resource> ResourcePtr;
typedef std::shared_ptr<Texture> TexturePtr;

typedef std::shared_ptr<Mesh> MeshPtr;
typedef std::shared_ptr<Material> MaterialPtr;

typedef unsigned int ui32;
typedef int          i32;
typedef float		 f32;
typedef double       f64;

enum class Key
{
	A = 0,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	_0,
	_1,
	_2,
	_3,
	_4,
	_5,
	_6,
	_7,
	_8,
	_9,
	Escape,
	Shift,
	Space,
	Enter,
	LeftMouseButton,
	MiddleMouseButton,
	RightMouseButton
};

enum class CameraType
{
	Orthogonal = 0,
	Perspective
};
enum class CullMode
{
	None = 0,
	Front,
	Back
};