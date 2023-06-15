#version 460

in vec3 color;
in vec2 uv;

uniform sampler2D tAlbedo;

layout(location = 0) out vec4 FragColor;

void main() {
    FragColor = texture(tAlbedo, uv);
}
