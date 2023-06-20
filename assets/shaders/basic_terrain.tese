#version 460 core

layout (quads, fractional_odd_spacing, ccw) in;

uniform sampler2D heightmap;
uniform mat4 mvp;

uniform float scale;
uniform float offset;

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
    vec2 t0 = (t01 - t00) * uv.y + t00;
    vec2 t1 = (t11 - t10) * uv.y + t10;
    vec2 g_uv = (t1 - t0) * uv.x + t0;
    tuv = g_uv;

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
    vec4 p0 = (p01 - p00) * uv.y + p00;
    vec4 p1 = (p11 - p10) * uv.y + p10;
    vec4 p = (p1 - p0) * uv.x + p0;

    // Retreive the height from the heightmap
    height = texture(heightmap, g_uv).r;

    // Displace point along normal
    p += normal * height * scale;
    p.y += offset;

    // OUTPUT
    // Output patch point position in clip space;
    gl_Position = mvp * p;
}