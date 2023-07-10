#version 460 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexcoord;

uniform mat4 modelView;
uniform mat4 mvp;

out vec3 color;

void main() {
    color = vec3(aTexcoord, 0.0);
    gl_Position = mvp * vec4(aPosition, 1.0);
}