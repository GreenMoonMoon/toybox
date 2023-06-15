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

typedef struct Material {
    Shader shader;
} Material;

Shader setup_shader(uint32_t program_handle);

Shader load_shader_from_file(const char* vertex_source_file, const char* fragment_source_file);

Material load_material_from_files(const char *vertex_source_file, const char *fragment_source_file);

void material_enable(Material material);

void material_set_mvp(Material material, mat4 model, mat4 view, mat4 projection);

void material_unload(Material material);

#endif //SUPERMARIO_SHADER_H
