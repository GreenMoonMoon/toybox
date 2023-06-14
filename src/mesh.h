//
// Created by josue on 2023-02-16.
//

#ifndef SUPERMARIO_GPU_H
#define SUPERMARIO_GPU_H

#include <stdint.h>
#include <stdbool.h>

typedef struct Mesh {
  uint8_t *vertex_data;
  size_t vertex_data_size;
  uint32_t *index_data;
  size_t index_data_size;

  uint32_t vao;
  uint32_t buffers[2];
  int32_t index_count;
} Mesh;

Mesh mesh_load(uint8_t *vertices, int64_t vertices_size, int64_t vertex_size, uint32_t *indices, int64_t indices_size);

void mesh_set_vertex_attribute(Mesh mesh, uint32_t attribute_index, int32_t offset);

void mesh_delete(Mesh mesh);

#endif //SUPERMARIO_GPU_H
