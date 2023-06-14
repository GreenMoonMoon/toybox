#version 460
layout (location = 0) in vec3 aPosition;

// TODO: Some mesh have a absolute world position and don't need the model matrix to be passed.
uniform mat4 mvp; //view-projection matrix

void main() {
    gl_Position = mvp * vec4(aPosition, 1.0);
}
