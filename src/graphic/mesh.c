//
// Created by josue on 2023-02-16.
//

#include "mesh.h"

#include "glad/gl.h"

Mesh mesh_load(float *vertices, int64_t vertices_size, uint32_t *indices, int64_t indices_size) {
    GLuint buffers[2];
    glCreateBuffers(2, buffers);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);
    GLintptr base_offset = 0;
    GLsizei vertex_size = sizeof(float) * 3;
    GLsizei relative_offset = 0;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);

    GLuint vao;
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexArrayAttrib(vao, 0);

    glVertexArrayVertexBuffer(vao, 0, buffers[0], base_offset, vertex_size); // Bind a buffer to binding point 0
    glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, relative_offset);
    glVertexArrayAttribBinding(vao, 0, 0); // Bind attribute location to binding point

    glVertexArrayElementBuffer(vao, buffers[1]);

    Mesh mesh = {
        .vao = vao,
        .buffers = {buffers[0], buffers[1]},
        .index_count = 0,
    };
    return mesh;
}

void mesh_unload(Mesh mesh) {
    glBindVertexArray(0);
    glDeleteBuffers(2, mesh.buffers);
    glDeleteVertexArrays(1, &mesh.vao);
}

//void init_primitive(DrawMode mode, Primitive *primitive) {
//    glGenVertexArrays(1, &primitive->vao);
//    GLenum gl_mode;
//    switch (mode) {
//        case POINTS_DRAW_MODE:
//            gl_mode = POINTS_DRAW_MODE;
//            break;
//        case LINE_STRIPS_DRAW_MODE:
//            gl_mode = LINE_STRIPS_DRAW_MODE;
//            break;
//        case LINE_LOOPS_DRAW_MODE:
//            gl_mode = LINE_LOOPS_DRAW_MODE;
//            break;
//        case LINES_DRAW_MODE:
//            gl_mode = LINES_DRAW_MODE;
//            break;
//        case TRIANGLE_STRIPS_DRAW_MODE:
//            gl_mode = TRIANGLE_STRIPS_DRAW_MODE;
//            break;
//        case TRIANGLE_FANS_DRAW_MODE:
//            gl_mode = TRIANGLE_FANS_DRAW_MODE;
//            break;
//        default:
//            gl_mode = GL_TRIANGLES;
//    }
//    primitive->mode = gl_mode;
//}

//// TODO: split into various attribute type loading functions
//void load_primitive_attributes(Primitive *primitive, AttributeDescription *attribute_description, uint32_t attribute_count) {
//    for (int i = 0; i < attribute_count; ++i) {
//        glEnableVertexArrayAttrib(primitive->vao, attribute_description->index);
//        glVertexArrayVertexBuffer(primitive->vao, attribute_description->binding_index, attribute_description->buffer_handle, attribute_description->buffer_offset, (int32_t)attribute_description->buffer_stride);
//        glVertexArrayAttribFormat(primitive->vao, attribute_description->index, (int32_t)attribute_description->component_count, attribute_description->component_type, attribute_description->normalized, attribute_description->offset);
//        glVertexArrayAttribBinding(primitive->vao, attribute_description->index, attribute_description->binding_index);
//    }
//}

//void set_primitive_indices(int32_t index_count, uint32_t buffer_handle, Primitive *primitive) {
//    primitive->index_count = index_count;
//    glBindVertexArray(primitive->vao);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_handle);
//
////    glVertexArrayElementBuffer(primitive->vao, buffer_handle);
//}
//
//
//void set_primitive_attribute_2f(bool normalized, uint32_t index, uint32_t binding_index, GpuBufferView buffer, Primitive *primitive) {
//    glEnableVertexArrayAttrib(primitive->vao, index);
//    glVertexArrayVertexBuffer(primitive->vao, binding_index, buffer.handle, buffer.offset, (int32_t)buffer.stride);
//    glVertexArrayAttribFormat(primitive->vao, index, 2, GL_FLOAT, normalized, 0);
//    glVertexArrayAttribBinding(primitive->vao, index, binding_index);
//}
//
//void set_primitive_attribute_3f(bool normalized, uint32_t index, uint32_t binding_index, GpuBufferView buffer, Primitive *primitive) {
//    glEnableVertexArrayAttrib(primitive->vao, index);
//    glVertexArrayVertexBuffer(primitive->vao, binding_index, buffer.handle, buffer.offset, (int32_t)buffer.stride);
//    glVertexArrayAttribFormat(primitive->vao, index, 3, GL_FLOAT, normalized, 0);
//    glVertexArrayAttribBinding(primitive->vao, index, binding_index);
//}
//
//void gpu_load_static_model(Model *model) {
//    return 0;
//}
