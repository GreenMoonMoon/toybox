//
// Created by josue on 2023-02-16.
//

#ifndef SUPERMARIO_GPU_H
#define SUPERMARIO_GPU_H

#include <stdint.h>
#include <stdbool.h>

/// \todo put the element buffer in its own variable.
typedef struct Mesh {
  uint32_t vao;
  uint32_t buffers[2];
  int32_t index_count;
} Mesh;

Mesh mesh_load(float *vertices, int64_t vertices_size, uint32_t *indices, int64_t indices_size);

void mesh_unload(Mesh mesh);

#endif //SUPERMARIO_GPU_H
