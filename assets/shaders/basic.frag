#version 460
out vec4 FragColor;

in vec3 light;
in vec3 color;

void main() {
    FragColor = vec4(color, 1.0f);
}