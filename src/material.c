//
// Created by josue on 2023-01-27.
//
#include "material.h"
#include <stdarg.h>

void validate_shader(GLuint handle) {
    GLint success = 0;
    char info_log[512];
    glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(handle, 512, NULL, info_log);
        fprintf(stderr, "%s", info_log);
    }
}

void validate_program(GLuint handle) {
    GLint success = 0;
    char info_log[512];
    glGetProgramiv(handle, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(handle, 512, NULL, info_log);
        fprintf(stderr, "%s", info_log);
    }
}

GLuint compile_vertex_shader(const char *source) {
    GLuint shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

#ifdef DEBUG_BUILD
    validate_shader(shader);
#endif

    return shader;
}

GLuint compile_fragment_shader(const char *source) {
    GLuint shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

#ifdef DEBUG_BUILD
    validate_shader(shader);
#endif

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

#ifdef DEBUG_BUILD
    validate_program(program);
#endif

    return program;
}

Shader setup_shader(GLuint program_handle) {
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
    };
}

Shader load_shader_from_files(const char *vertex_source, const char *fragment_source) {
    GLuint vertex_handle = compile_vertex_shader(vertex_source);
    GLuint fragment_handle = compile_fragment_shader(fragment_source);
    GLuint program_handle = build_program(2, vertex_handle, fragment_handle);

    return setup_shader(program_handle);
}

void use_shader(Shader shader) {
    glUseProgram(shader.handle);
}

void set_shader_mvp(Shader shader, mat4 model, mat4 view, mat4 projection) {
    glUniformMatrix4fv(shader.view_loc, 1, GL_FALSE, (float *) view);
    glUniformMatrix4fv(shader.projection_loc, 1, GL_FALSE, (float *) projection);

    mat4 mvp;
    glm_mat4_mul(view, model, mvp);
    glUniformMatrix4fv(shader.model_view_loc, 1, GL_FALSE, (float *) mvp);

    glm_mat4_mul(projection, mvp, mvp);
    glUniformMatrix4fv(shader.mvp_loc, 1, GL_FALSE, (float *) mvp);
}

void set_shader_light(Shader shader, vec3 position, vec3 intensity, vec3 reflectivity) {
    glUniform3fv(shader.light_source_loc, 1, position);
    glUniform3fv(shader.light_intensity_loc, 1, intensity);
    glUniform3fv(shader.diffuse_reflectivity_loc, 1, reflectivity);
}

void set_shader_normal_matrix(Shader shader, mat4 normal_matrix){
    glUniformMatrix4fv(shader.normal_loc, 1, GL_FALSE, (float *) normal_matrix);
}
