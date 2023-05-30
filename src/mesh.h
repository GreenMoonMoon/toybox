//
// Created by josue on 2023-02-16.
//

#ifndef SUPERMARIO_GPU_H
#define SUPERMARIO_GPU_H

#include <stdint.h>
#include <stdbool.h>

typedef struct Mesh {
  uint32_t vao;
  uint32_t vbo;
  uint32_t ebo;
  uint32_t mode;
  int32_t index_count;

  float *vertex_buffer;
  int64_t vertex_buffer_length;
  uint32_t *index_buffer;
  int64_t index_buffer_length;
} Mesh;

void mesh_load(Mesh *mesh);
void mesh_unload(Mesh *mesh);

void gpu_load_static_vertex_buffer(struct Mesh *mesh, uint8_t *buffer, int64_t length);
void gpu_load_static_element_buffer(struct Mesh *mesh, uint8_t *buffer, int64_t length);

uint32_t load_static_array_buffer(size_t size, const void *data);

uint32_t load_static_element_array_buffer(size_t size, const void *data);

void init_primitive(DrawMode mode, Primitive *primitive);

void set_primitive_indices(int32_t index_count, uint32_t buffer_handle, Primitive *primitive);

void set_primitive_attribute_1i(bool normalized, uint32_t index, uint32_t binding_index, GpuBufferView buffer, Primitive *primitive);
void set_primitive_attribute_2i(bool normalized, uint32_t index, uint32_t binding_index, GpuBufferView buffer, Primitive *primitive);
void set_primitive_attribute_3i(bool normalized, uint32_t index, uint32_t binding_index, GpuBufferView buffer, Primitive *primitive);
void set_primitive_attribute_4i(bool normalized, uint32_t index, uint32_t binding_index, GpuBufferView buffer, Primitive *primitive);
void set_primitive_attribute_1f(bool normalized, uint32_t index, uint32_t binding_index, GpuBufferView buffer, Primitive *primitive);
void set_primitive_attribute_2f(bool normalized, uint32_t index, uint32_t binding_index, GpuBufferView buffer, Primitive *primitive);
void set_primitive_attribute_3f(bool normalized, uint32_t index, uint32_t binding_index, GpuBufferView buffer, Primitive *primitive);
void set_primitive_attribute_4f(bool normalized, uint32_t index, uint32_t binding_index, GpuBufferView buffer, Primitive *primitive);

void gpu_load_static_model(struct Model *model);

#endif //SUPERMARIO_GPU_H
