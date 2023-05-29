//
// Created by josue on 2023-01-30.
//
#include "glsl.h"

Shader load_glsl_from_files(const char *vertex_source_file, const char *fragment_source_file) {
    char *buffer;
    read_file(vertex_source_file, &buffer);
    uint32_t vs = compile_vertex_shader(buffer);
    free(buffer);

    read_file(fragment_source_file, &buffer);
    uint32_t fs = compile_fragment_shader(buffer);
    free(buffer);

    uint32_t program = build_program(2, vs, fs);

    return setup_shader(program);
}
