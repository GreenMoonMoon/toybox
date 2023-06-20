#version 460 core

layout (vertices=4) out;

in vec2 uv[];
out vec2 textureCoord[];

uniform mat4 model_view;

void main(){
    // Passing attributes through
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    textureCoord[gl_InvocationID] = uv[gl_InvocationID];

    // invocation zero controls tessellation levels for the entire patch
    if (gl_InvocationID == 0) {
        // Define tesselation control parameters
        const int MIN_TESS_LEVEL = 4;
        const int MAX_TESS_LEVEL = 64;
        const float MIN_DISTANCE = 1.0;
        const float MAX_DISTANCE = 2.0;

        // Tranform vertices to get the distance to the eye center
        vec4 eye_space_pos00 = model_view * gl_in[0].gl_Position;
        vec4 eye_space_pos01 = model_view * gl_in[1].gl_Position;
        vec4 eye_space_pos10 = model_view * gl_in[2].gl_Position;
        vec4 eye_space_pos11 = model_view * gl_in[3].gl_Position;

        // Get distance form the eye
        float distance00 = clamp((abs(eye_space_pos00.z) - MIN_DISTANCE) / (MAX_DISTANCE - MIN_DISTANCE), 0.0, 1.0);
        float distance01 = clamp((abs(eye_space_pos01.z) - MIN_DISTANCE) / (MAX_DISTANCE - MIN_DISTANCE), 0.0, 1.0);
        float distance10 = clamp((abs(eye_space_pos10.z) - MIN_DISTANCE) / (MAX_DISTANCE - MIN_DISTANCE), 0.0, 1.0);
        float distance11 = clamp((abs(eye_space_pos11.z) - MIN_DISTANCE) / (MAX_DISTANCE - MIN_DISTANCE), 0.0, 1.0);

        // Interpolate tesselation level based on distance
        float tess_level_0 = mix(MAX_TESS_LEVEL, MIN_TESS_LEVEL, min(distance10, distance00));
        float tess_level_1 = mix(MAX_TESS_LEVEL, MIN_TESS_LEVEL, min(distance00, distance01));
        float tess_level_2 = mix(MAX_TESS_LEVEL, MIN_TESS_LEVEL, min(distance01, distance11));
        float tess_level_3 = mix(MAX_TESS_LEVEL, MIN_TESS_LEVEL, min(distance11, distance10));

        // Set outer edge tesselation
        gl_TessLevelOuter[0] = tess_level_0;
        gl_TessLevelOuter[1] = tess_level_1;
        gl_TessLevelOuter[2] = tess_level_2;
        gl_TessLevelOuter[3] = tess_level_3;

        // Set inner edge tesselation to the max fo the two parallel edges
        gl_TessLevelInner[0] = max(tess_level_1, tess_level_3);
        gl_TessLevelInner[1] = max(tess_level_0, tess_level_2);
    }
}