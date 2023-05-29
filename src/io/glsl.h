//
// Created by josue on 2023-01-23.
//

#ifndef SUPERMARIO_GLSL_H
#define SUPERMARIO_GLSL_H

#include "types/shader.h"
#include "io/file.h"

/// Load and compile a programe from a single vertex and fragment sources
/// \param vertex_source_file
/// \param fragment_source_file
/// \return Initialized Shader object
Shader load_glsl_from_files(const char *vertex_source_file, const char *fragment_source_file);

#endif //SUPERMARIO_GLSL_H
