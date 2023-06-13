//
// Created by josue on 2023-02-16.
//

#ifndef SUPERMARIO_GPU_H
#define SUPERMARIO_GPU_H

#include <stdint.h>
#include <stdbool.h>

/// \note Vertex data is separated between static and dynamic buffers. Data is added linearly for now (as opposed to interleaving)
///     The goal is to make it easy to process mesh data before sending it to the GPU; Since we may have different number of attributes
///     per mesh, instead of regenerating a buffer and interleaving all data, we can simply use realloc and append the new attribute
///     buffer at the end. This as also the benefit to be easy to align (for example on 4 bytes)

/// \todo put the element buffer in its own variable.
typedef struct Mesh {
  uint32_t vao;
  uint32_t buffers[2];
  int32_t index_count;
} Mesh;

Mesh mesh_load(float *vertices, int64_t vertices_size, uint32_t *indices, int64_t indices_size);

void mesh_unload(Mesh mesh);

void gpu_load_static_vertex_buffer(struct Mesh *mesh, uint8_t *buffer, int64_t length);
void gpu_load_static_element_buffer(struct Mesh *mesh, uint8_t *buffer, int64_t length);

uint32_t load_static_array_buffer(size_t size, const void *data);

uint32_t load_static_element_array_buffer(size_t size, const void *data);

//void init_primitive(DrawMode mode, Primitive *primitive);

//void set_primitive_indices(int32_t index_count, uint32_t buffer_handle, Primitive *primitive);

//void set_primitive_attribute_1i(bool normalized, uint32_t index, uint32_t binding_index, GpuBufferView buffer, Primitive *primitive);
//void set_primitive_attribute_2i(bool normalized, uint32_t index, uint32_t binding_index, GpuBufferView buffer, Primitive *primitive);
//void set_primitive_attribute_3i(bool normalized, uint32_t index, uint32_t binding_index, GpuBufferView buffer, Primitive *primitive);
//void set_primitive_attribute_4i(bool normalized, uint32_t index, uint32_t binding_index, GpuBufferView buffer, Primitive *primitive);
//void set_primitive_attribute_1f(bool normalized, uint32_t index, uint32_t binding_index, GpuBufferView buffer, Primitive *primitive);
//void set_primitive_attribute_2f(bool normalized, uint32_t index, uint32_t binding_index, GpuBufferView buffer, Primitive *primitive);
//void set_primitive_attribute_3f(bool normalized, uint32_t index, uint32_t binding_index, GpuBufferView buffer, Primitive *primitive);
//void set_primitive_attribute_4f(bool normalized, uint32_t index, uint32_t binding_index, GpuBufferView buffer, Primitive *primitive);

void gpu_load_static_model(struct Model *model);

#endif //SUPERMARIO_GPU_H
