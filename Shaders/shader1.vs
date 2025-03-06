#version 330 core

layout(std140) uniform UniformData {
vec2 x;
};

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main() {
    gl_Position = vec4(aPos.xy + x, aPos.z, 1.0);
    TexCoord = aTexCoord;
}
