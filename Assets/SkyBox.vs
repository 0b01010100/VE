#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texcoord;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 binormal;

out vec2 TexCoord;

uniform mat4 transform;
// uniform mat4 world;
// uniform mat4 view;
// uniform mat4 proj;

void main() {
    // vec4 worldPos = world * position;
    // vec4 viewPos = view * worldPos;
    gl_Position = transform * position;

    TexCoord = texcoord;
}
