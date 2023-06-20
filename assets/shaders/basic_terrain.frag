#version 460 core

in vec2 tuv;
in float height;

uniform sampler2D heightmap;

layout(location = 0) out vec4 FragColor;

void main() {
    float h = (height);
    FragColor = vec4(h, h, h, 1.0);
//    FragColor = texture(heightmap, tuv);
}
