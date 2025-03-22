#version 330 core
layout(std140) uniform UniformData {
vec2 x;
};
layout (location = 0) in vec3 aPos;
void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
};