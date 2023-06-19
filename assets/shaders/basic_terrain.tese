#version 460 core

layout (quads, fractional_odd_spacing, ccw) in;

uniform sampler2D heightmap;
uniform mat4 mvp;

in vec2 textureCoord[];
out vec2 tuv;
out float height;

void main(){
    // TEXTURE COORDINATES
    vec2 uv = gl_TessCoord.xy;

    vec2 t00 = textureCoord[0];
    vec2 t01 = textureCoord[1];
    vec2 t10 = textureCoord[2];
    vec2 t11 = textureCoord[3];

    // Interpolate UV for the generated point
    vec2 t0 = (t01 - t00) * uv.x + t00;
    vec2 t1 = (t11 - t10) * uv.x + t10;
    vec2 g_uv = (t1 - t0) * uv.y + t0;
    tuv = g_uv;

    // Retreive the height from the heightmap
    height = texture(heightmap, g_uv).r;

    // POSITION
    vec4 p00 = gl_in[0].gl_Position;
    vec4 p01 = gl_in[1].gl_Position;
    vec4 p10 = gl_in[2].gl_Position;
    vec4 p11 = gl_in[3].gl_Position;

    // Compute vertices normals
    vec4 uVec = p01 - p00;
    vec4 vVec = p10 - p00;
    vec4 normal = normalize(vec4(cross(vVec.xyz, uVec.xyz), 0.0));

    // Bilinearly interpolate vertices positions
    vec4 p0 = (p01 - p00) * uv.x + p00;
    vec4 p1 = (p11 - p10) * uv.x + p10;
    vec4 p = (p1 - p0) * uv.y + p0;

    // Displace point along normal
    p += normal * height;

    // OUTPUT
    // Output patch point position in clip space;
    gl_Position = mvp * p;
}