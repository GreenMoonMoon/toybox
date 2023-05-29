//
// Created by josue on 2023-02-16.
//

#include "gpu.h"
#include "types/mesh.h"

#include "glad/gl.h"


uint32_t load_static_array_buffer(size_t size, const void *data) {
    uint32_t handle;
    glGenBuffers(1, &handle);
    glNamedBufferData(handle, (int64_t)size, data, GL_STATIC_DRAW);
    return handle;
}

uint32_t load_static_element_array_buffer(size_t size, const void *data) {
    uint32_t handle;
    glGenBuffers(1, &handle);
    glNamedBufferData(handle, (int64_t)size, data, GL_STATIC_DRAW);
    return handle;
}

void init_primitive(DrawMode mode, Primitive *primitive) {
    glGenVertexArrays(1, &primitive->vao);
    GLenum gl_mode;
    switch (mode) {
        case POINTS_DRAW_MODE:
            gl_mode = POINTS_DRAW_MODE;
            break;
        case LINE_STRIPS_DRAW_MODE:
            gl_mode = LINE_STRIPS_DRAW_MODE;
            break;
        case LINE_LOOPS_DRAW_MODE:
            gl_mode = LINE_LOOPS_DRAW_MODE;
            break;
        case LINES_DRAW_MODE:
            gl_mode = LINES_DRAW_MODE;
            break;
        case TRIANGLE_STRIPS_DRAW_MODE:
            gl_mode = TRIANGLE_STRIPS_DRAW_MODE;
            break;
        case TRIANGLE_FANS_DRAW_MODE:
            gl_mode = TRIANGLE_FANS_DRAW_MODE;
            break;
        default:
            gl_mode = GL_TRIANGLES;
    }
    primitive->mode = gl_mode;
}

//// TODO: split into various attribute type loading functions
//void load_primitive_attributes(Primitive *primitive, AttributeDescription *attribute_description, uint32_t attribute_count) {
//    for (int i = 0; i < attribute_count; ++i) {
//        glEnableVertexArrayAttrib(primitive->vao, attribute_description->index);
//        glVertexArrayVertexBuffer(primitive->vao, attribute_description->binding_index, attribute_description->buffer_handle, attribute_description->buffer_offset, (int32_t)attribute_description->buffer_stride);
//        glVertexArrayAttribFormat(primitive->vao, attribute_description->index, (int32_t)attribute_description->component_count, attribute_description->component_type, attribute_description->normalized, attribute_description->offset);
//        glVertexArrayAttribBinding(primitive->vao, attribute_description->index, attribute_description->binding_index);
//    }
//}

void set_primitive_indices(int32_t index_count, uint32_t buffer_handle, Primitive *primitive) {
    primitive->index_count = index_count;
    glBindVertexArray(primitive->vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_handle);

//    glVertexArrayElementBuffer(primitive->vao, buffer_handle);
}


void set_primitive_attribute_2f(bool normalized, uint32_t index, uint32_t binding_index, GpuBufferView buffer, Primitive *primitive) {
    glEnableVertexArrayAttrib(primitive->vao, index);
    glVertexArrayVertexBuffer(primitive->vao, binding_index, buffer.handle, buffer.offset, (int32_t)buffer.stride);
    glVertexArrayAttribFormat(primitive->vao, index, 2, GL_FLOAT, normalized, 0);
    glVertexArrayAttribBinding(primitive->vao, index, binding_index);
}

void set_primitive_attribute_3f(bool normalized, uint32_t index, uint32_t binding_index, GpuBufferView buffer, Primitive *primitive) {
    glEnableVertexArrayAttrib(primitive->vao, index);
    glVertexArrayVertexBuffer(primitive->vao, binding_index, buffer.handle, buffer.offset, (int32_t)buffer.stride);
    glVertexArrayAttribFormat(primitive->vao, index, 3, GL_FLOAT, normalized, 0);
    glVertexArrayAttribBinding(primitive->vao, index, binding_index);
}
