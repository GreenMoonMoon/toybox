//
// Created by josue on 2023-01-27.
//
#include "material.h"
#include <stdarg.h>
#include "texture.h"
#include "memory.h"
#include "io/file.h"

void validate_shader(GLuint handle) {
    GLint success = 0;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint log_length = 0;
        glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &log_length);

        char *log = MALLOC(sizeof(char) * log_length);
        glGetShaderInfoLog(handle, log_length, NULL, log);
        fprintf(stderr, "ERROR GLSL Shader: %s", log);
        free(log);
    }
}

void validate_program(GLuint handle) {
    GLint success = 0;
    glGetProgramiv(handle, GL_LINK_STATUS, &success);
    if (!success) {
        GLint log_length = 0;
        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &log_length);

        char *log = MALLOC(sizeof(char) * log_length);
        glGetProgramInfoLog(handle, log_length, NULL, log);
        fprintf(stderr, "ERROR GLSL Program: %s", log);
        free(log);
    }
}

GLuint compile_shader(const char *source, GLenum shader_type) {
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    validate_shader(shader);

    return shader;
}

/// Attach and link shaders to a Shader Program
/// \param count number of shader passed to the function
/// \param ... compiled shaders to attach to the program
/// \return handle to the Shader Program
GLuint build_program(int count, ...) {
    GLuint program = glCreateProgram();

    // Attach all shaders
    va_list arg_list;
            va_start(arg_list, count);
    for (int i = 0; i < count; i++) {
        glAttachShader(program, va_arg(arg_list, GLuint));
    }
            va_end(arg_list);

    glLinkProgram(program);

    // Delete all shaders (shader remains in memory until either detached or the program is deleted)
            va_start(arg_list, count);
    for (int i = 0; i < count; i++) {
        glDeleteShader(va_arg(arg_list, GLuint));
    }
            va_end(arg_list);

    validate_program(program);

    return program;
}

Shader setup_shader(uint32_t program_handle) {
    return (Shader) {
            .handle = program_handle,
            .view_loc = glGetUniformLocation(program_handle, "view"),
            .model_view_loc = glGetUniformLocation(program_handle, "modelView"),
            .normal_loc = glGetUniformLocation(program_handle, "normalMatrix"),
            .projection_loc = glGetUniformLocation(program_handle, "Projection"),
            .mvp_loc = glGetUniformLocation(program_handle, "mvp"),
            .light_source_loc = glGetUniformLocation(program_handle, "lightSource"),
            .light_intensity_loc = glGetUniformLocation(program_handle, "lightIntensity"),
            .diffuse_reflectivity_loc = glGetUniformLocation(program_handle, "diffuseReflectivity"),
            .albedo_loc = glGetUniformLocation(program_handle, "tAlbedo"),
    };
}

Shader setup_tesselation_shader(uint32_t program_handle) {
    return (Shader) {
        .handle = program_handle,
        .mvp_loc = glGetUniformLocation(program_handle, "mvp"),
        .heightmap = glGetUniformLocation(program_handle, "heightmap"),
    };
}

Shader load_shader_from_file(const char *vertex_source_file, const char *fragment_source_file) {
    char *vertex_source;
    read_file(vertex_source_file, &vertex_source);
    GLuint vertex_handle = compile_shader(vertex_source, GL_VERTEX_SHADER);
    FREE(vertex_source);

    char *fragment_source;
    read_file(fragment_source_file, &fragment_source);
    GLuint fragment_handle = compile_shader(fragment_source, GL_FRAGMENT_SHADER);
    FREE(fragment_source);

    GLuint program_handle = build_program(2, vertex_handle, fragment_handle);

    return setup_shader(program_handle);
}

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
    FREE(vertex_source);

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
    glUniformMatrix4fv(material.shader.view_loc, 1, GL_FALSE, (float *) model_view);
    glUniformMatrix4fv(material.shader.projection_loc, 1, GL_FALSE, (float *) projection);

    mat4 mvp;
    glm_mat4_mul(model_view, view, mvp);
    glUniformMatrix4fv(material.shader.model_view_loc, 1, GL_FALSE, (float *) mvp);

    glm_mat4_mul(projection, mvp, mvp);
    glUniformMatrix4fv(material.shader.mvp_loc, 1, GL_FALSE, (float *) mvp);
}

void material_set_albedo(Material material, struct Texture *texture) {
    texture_enable(*texture, 0);
    glUniform1i(material.shader.albedo_loc, 0);
}

void material_unload(Material material) {
    glDeleteProgram(material.shader.handle);
}
