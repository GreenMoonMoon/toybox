#version 460
layout (location = 0) in vec3 aPosition;

// TODO: Some mesh have a absolute world position and don't need the model matrix to be passed.
uniform mat4 mvp; //view-projection matrix

out vec3 color;

void main() {
    color = vec3(aPosition.y / 5.0f);
    gl_Position = mvp * vec4(aPosition, 1.0);
}
