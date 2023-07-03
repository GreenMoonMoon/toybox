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

Material load_tesselation_material_from_files(const char *vertex_source_file,
                                              const char *tess_control_source_file,
                                              const char *tess_evaluation_source_file,
                                              const char *fragment_source_file) {
    char *vertex_source;
    read_file(vertex_source_file, &vertex_source);
    GLuint vertex_handle = compile_shader(vertex_source, GL_VERTEX_SHADER);
    free(vertex_source);

    char *tess_control_source;
    read_file(tess_control_source_file, &tess_control_source);
    GLuint tess_control_handle = compile_shader(tess_control_source, GL_TESS_CONTROL_SHADER);
    FREE(tess_control_source);

    char *tess_evaluation_source;
    read_file(tess_evaluation_source_file, &tess_evaluation_source);
    GLuint tess_evaluation_handle = compile_shader(tess_evaluation_source, GL_TESS_EVALUATION_SHADER);
    FREE(tess_evaluation_source);

    char *fragment_source;
    read_file(fragment_source_file, &fragment_source);
    GLuint fragment_handle = compile_shader(fragment_source, GL_FRAGMENT_SHADER);
    FREE(fragment_source);

    GLuint program_handle = build_program(4, vertex_handle, tess_control_handle, tess_evaluation_handle, fragment_handle);

    Material result = {
        .shader = setup_tesselation_shader(program_handle),
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
