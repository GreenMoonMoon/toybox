#version 460
layout (location = 0) in vec3 aPosition;
layout (location = 2) in vec2 aTexcoord;
layout (location = 1) in vec3 aNormal;

// TODO: Some mesh have a absolute world position and don't need the model matrix to be passed.
uniform mat4 mvp; //view-projection matrix

out vec3 color;
out vec2 uv;

void main() {
    color = vec3(aPosition.y / 8.0f);
    uv = aTexcoord;
    gl_Position = mvp * vec4(aPosition, 1.0);
}
