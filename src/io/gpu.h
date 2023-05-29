//
// Created by josue on 2023-02-16.
//

#ifndef SUPERMARIO_GPU_H
#define SUPERMARIO_GPU_H

#include <stdint.h>
#include <stdbool.h>
#include "types/mesh.h"

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

#endif //SUPERMARIO_GPU_H
