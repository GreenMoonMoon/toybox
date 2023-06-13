//
// Created by josue on 2023-02-16.
//

#include "mesh.h"

#include "glad/gl.h"

void mesh_load(Mesh *mesh) {
    uint32_t buffers[2];
    glGenBuffers(2, buffers);
    glBufferData(GL_VERTEX_ARRAY, mesh->vertex_buffer_length, mesh->vertex_buffer, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->index_buffer_length, mesh->index_buffer, GL_STATIC_DRAW);
    mesh->vbo = buffers[0];
    mesh->ebo = buffers[1];

    glGenVertexArrays(1, &mesh->vao);
    glBindVertexArray(mesh->vao);

    // Position
    glEnableVertexAttribArray(0); // aPosition attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_VERTEX_ARRAY, 0); // Unbind vertex array buffer

    glBindVertexArray(0); // Unbind vertex array object (Bind invalid VAO object at index 0)
}

void mesh_unload(Mesh *mesh) {
    glBindVertexArray(0);
    glDeleteBuffers(1, &mesh->vbo);
    glDeleteBuffers(1, &mesh->ebo);
    glDeleteVertexArrays(1, &mesh->vao);

    mesh->vao = 0;
    mesh->vbo = 0;
    mesh->ebo = 0;
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
