#version 460 core

layout (location = 0) in vec3 aPosition;
layout (location = 2) in vec2 aTexcoord;

out vec2 uv;

void main() {
    uv = aTexcoord;
    gl_Position = vec4(aPosition, 1.0);
}
