//
// Created by josue on 2023-02-16.
//

#ifndef SUPERMARIO_GPU_H
#define SUPERMARIO_GPU_H

#include <stdint.h>
#include <stdbool.h>
#include "cglm/cglm.h"

typedef struct Vertex {
    vec3 position;
    vec3 normal;
    vec2 uv;
} Vertex;

typedef struct Mesh {
  Vertex *vertices;
  size_t vertex_count;
  uint32_t *indices;
  int32_t index_count;

  uint32_t vao;
  uint32_t buffers[2];
} Mesh;

/// Load a mesh on the GPU
Mesh mesh_load(Vertex *vertices, int32_t vertex_count, uint32_t *indices, int32_t index_count);

/// Set a vertex attribute by specifying at which layout location it is going to be accessed and the data offset from
///  the start of each vertex.
/// \param mesh Input mesh
/// \param attribute_index Index corresponding to the shader layout attribute
/// \param offset Relative offset from the start of a vertex data structure
void mesh_set_vertex_attribute(Mesh mesh, uint32_t attribute_index, int32_t offset);

/// Unload a mesh from the gpu but doesn't delete the local data.
void mesh_unload(Mesh mesh);

/// Unload a mesh from the GPU and delete local data
void mesh_delete(Mesh mesh);

#endif //SUPERMARIO_GPU_H
