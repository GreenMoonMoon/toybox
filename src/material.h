//
// Created by josue on 2023-01-23.
//

#ifndef SUPERMARIO_SHADER_H
#define SUPERMARIO_SHADER_H

#include "shader.h"
#include "glad/gl.h"
#include "cglm/cglm.h"

struct Texture;

typedef struct Material {
    Shader shader;
} Material;

Material load_material_from_files(const char *vertex_source_file, const char *fragment_source_file);

Material load_tesselation_material_from_files(const char *vertex_source_file, const char *tess_control_source_file, const char *tess_evaluation_source_file, const char* fragment_source_file);

void material_enable(Material material);

void material_set_mvp(Material material, mat4 model, mat4 view, mat4 projection);

void material_set_albedo(Material material, struct Texture *texture);

void material_set_heightmap(Material material, struct Texture *texture);

void material_set_scale(Material material, float scale);

void material_set_offset(Material material, float offset);

void material_set_eye_position(Material material, mat4 transform);

void material_unload(Material material);

#endif //SUPERMARIO_SHADER_H
