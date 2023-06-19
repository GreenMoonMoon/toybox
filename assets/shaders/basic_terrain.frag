#version 460

in vec2 tuv;
in float height;

layout(location = 0) out vec4 FragColor;

void main() {
    float h = (height/255.0);
//    FragColor = vec4(h, h, h, 1.0);
    FragColor = vec4(1.0);
}
