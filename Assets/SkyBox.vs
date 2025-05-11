#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 binormal;

out vec2 TexCoord;

struct LightData
{
	vec4 color;
	vec4 direction;
};

struct TerrainData
{
	vec4 size;
	float heightMapSize;
};

layout(std140) uniform GlobalUbo {
    mat4 world;
    mat4 view;
    mat4 proj;
    vec4 cameraPosition;
    LightData light;
};

void main() {
    gl_Position = proj * view * world * vec4(position, 1.0f);
    TexCoord = texcoord;
}