#version 460
out vec4 FragColor;

uniform sampler2D tAlbedo;

in vec2 uv;
in vec3 light;
in vec3 color;

void main() {
    FragColor = texture(tAlbedo, uv);
}