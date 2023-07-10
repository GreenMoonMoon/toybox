//
// Created by josue on 2023-07-03.
//

#include "shader.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "io/file.h"
#include "glad/gl.h"

void validate_shader(GLuint handle) {
    GLint success = 0;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint log_length = 0;
        glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &log_length);

        char *log = malloc(sizeof(char) * log_length);
        glGetShaderInfoLog(handle, log_length, NULL, log);
        fprintf(stderr, "ERROR GLSL Shader: %s\n", log);
        free(log);
    }
}

void validate_program(GLuint handle) {
    GLint success = 0;
    glGetProgramiv(handle, GL_LINK_STATUS, &success);
    if (!success) {
        GLint log_length = 0;
        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &log_length);

        char *log = malloc(sizeof(char) * log_length);
        glGetProgramInfoLog(handle, log_length, NULL, log);
        fprintf(stderr, "ERROR GLSL Program: %s\n", log);
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
        .heightmap_loc = glGetUniformLocation(program_handle, "heightmap"),
    };
}

Shader setup_tesselation_shader(uint32_t program_handle) {
    return (Shader) {
        .handle = program_handle,
        .mvp_loc = glGetUniformLocation(program_handle, "mvp"),
        .heightmap_loc = glGetUniformLocation(program_handle, "heightmap"),
        .scale_loc = glGetUniformLocation(program_handle, "scale"),
        .offset_loc = glGetUniformLocation(program_handle, "offset"),
        .eye_position_loc = glGetUniformLocation(program_handle, "eye_position"),
        .model_view_loc = glGetUniformLocation(program_handle, "model_view"),
    };
}

Shader load_shader_from_file(const char *vertex_source_file, const char *fragment_source_file) {
    char *vertex_source;
    read_file(vertex_source_file, &vertex_source);
    GLuint vertex_handle = compile_shader(vertex_source, GL_VERTEX_SHADER);
    free(vertex_source);

    char *fragment_source;
    read_file(fragment_source_file, &fragment_source);
    GLuint fragment_handle = compile_shader(fragment_source, GL_FRAGMENT_SHADER);
    free(fragment_source);

    GLuint program_handle = build_program(2, vertex_handle, fragment_handle);

    return setup_shader(program_handle);
}

Shader load_tesselation_material_from_files(const char *vertex_source_file,
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
    free(tess_control_source);

    char *tess_evaluation_source;
    read_file(tess_evaluation_source_file, &tess_evaluation_source);
    GLuint tess_evaluation_handle = compile_shader(tess_evaluation_source, GL_TESS_EVALUATION_SHADER);
    free(tess_evaluation_source);

    char *fragment_source;
    read_file(fragment_source_file, &fragment_source);
    GLuint fragment_handle = compile_shader(fragment_source, GL_FRAGMENT_SHADER);
    free(fragment_source);

    GLuint
        program_handle = build_program(4, vertex_handle, tess_control_handle, tess_evaluation_handle, fragment_handle);

    Shader shader = setup_tesselation_shader(program_handle);
    return shader;
}

void shader_delete(Shader shader) {
    glDeleteProgram(shader.handle);
}

void init_default_shaders(void) {
    default_generic_shader =
        load_shader_from_file("assets/shaders/default_generic.vert", "assets/shaders/default_generic.frag");
}

void clean_default_shaders(void) {
    shader_delete(default_generic_shader);
}

void shader_enable(Shader shader) {
    glUseProgram(shader.handle);
}

void shader_set_mvp(Shader shader, vec4 *model, vec4 *view, vec4 *projection) {
    mat4 model_view;
    glm_mat4_mul(view, model, model_view);
    glUniformMatrix4fv(shader.model_view_loc, 1, GL_FALSE, (float *) model_view);

    mat4 mvp;
    glm_mat4_mul(projection, model_view, mvp);
    glUniformMatrix4fv(shader.mvp_loc, 1, GL_FALSE, (float *) mvp);
}