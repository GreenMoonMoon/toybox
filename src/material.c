//
// Created by josue on 2023-01-27.
//
#include "material.h"
#include <stdarg.h>
#include "texture.h"
#include "io/file.h"

/// Load shader source, create and return a Material
/// \param vertex_source_file Vertex shader source file
/// \param fragment_source_file Fragment shader source file
/// \return struct Material
Material load_material_from_files(const char *vertex_source_file, const char *fragment_source_file) {
    Material result = {
        .shader = load_shader_from_file(vertex_source_file, fragment_source_file),
    };

    return result;
}

void material_enable(Material material) {
    glUseProgram(material.shader.handle);
}

void material_set_mvp(Material material, mat4 model, mat4 view, mat4 projection) {
    mat4 model_view;
    glm_mat4_mul(view, model, model_view);
    glUniformMatrix4fv(material.shader.model_view_loc, 1, GL_FALSE, (float *) model_view);

    mat4 mvp;
    glm_mat4_mul(projection, model_view, mvp);
    glUniformMatrix4fv(material.shader.mvp_loc, 1, GL_FALSE, (float *) mvp);
}

void material_set_albedo(Material material, struct Texture *texture) {
    texture_enable(*texture, 0);
    glUniform1i(material.shader.albedo_loc, 0);
}

void material_set_heightmap(Material material, struct Texture *texture) {
    texture_enable(*texture, 1);
    glUniform1i(material.shader.heightmap_loc, 1);
}

void material_set_scale(Material material, float scale){
    glUniform1f(material.shader.scale_loc, scale);
}

void material_set_offset(Material material, float offset){
    glUniform1f(material.shader.offset_loc, offset);
}

void material_set_eye_position(Material material, mat4 transform){
    glUniform3f(material.shader.eye_position_loc, transform[3][0], transform[3][1], transform[3][2]);
}

void material_unload(Material material) {
    glDeleteProgram(material.shader.handle);
}
