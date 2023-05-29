//
// Created by josue on 2023-01-23.
//

#ifndef SUPERMARIO_SHADER_H
#define SUPERMARIO_SHADER_H

#include "glad/gl.h"
#include "cglm/cglm.h"

typedef struct Shader {
    uint32_t handle;
    // Uniform locations
    int32_t view_loc;
    int32_t model_view_loc;
    int32_t normal_loc;
    int32_t projection_loc;
    int32_t mvp_loc;
    int32_t light_source_loc;
    int32_t light_intensity_loc;
    int32_t diffuse_reflectivity_loc;
} Shader;

uint32_t compile_vertex_shader(const char *source);

uint32_t compile_fragment_shader(const char *source);

uint32_t build_program(int count, ...);

Shader setup_shader(uint32_t program_handle);

Shader load_shader_from_files(const char* vertex_source, const char* fragment_source);

void use_shader(Shader shader);

void set_shader_mvp(Shader shader, mat4 view, mat4 model_view, mat4 projection);

void set_shader_light(Shader shader, vec3 position, vec3 intensity, vec3 reflectivity);

void set_shader_normal_matrix(Shader shader, mat4 normal_matrix);

#endif //SUPERMARIO_SHADER_H
