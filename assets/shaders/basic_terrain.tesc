#version 460 core

layout (vertices=4) out;

in vec2 uv[];
out vec2 textureCoord[];

void main(){
    // Passing attributes through
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    textureCoord[gl_InvocationID] = uv[gl_InvocationID];

    // invocation zero controls tessellation levels for the entire patch
    gl_TessLevelOuter[0] = 16;
    gl_TessLevelOuter[1] = 16;
    gl_TessLevelOuter[2] = 16;
    gl_TessLevelOuter[3] = 16;

    gl_TessLevelInner[0] = 16;
    gl_TessLevelInner[1] = 16;
}