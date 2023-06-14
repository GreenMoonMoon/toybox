//
// Created by josue on 2023-02-16.
//

#include "mesh.h"
#include "memory.h"
#include "glad/gl.h"

Mesh mesh_load(uint8_t *vertices, int64_t vertices_size, int64_t vertex_size, uint32_t *indices, int64_t indices_size) {
    GLuint buffers[2];
    glCreateBuffers(2, buffers);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);
    GLintptr base_offset = 0;
    GLsizei relative_offset = 0;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);

    GLuint vao;
    glCreateVertexArrays(1, &vao);
    glVertexArrayVertexBuffer(vao, 0, buffers[0], base_offset, vertex_size); // Bind a buffer to binding point 0
    glVertexArrayElementBuffer(vao, buffers[1]);

    Mesh mesh = {
        .vao = vao,
        .buffers = {buffers[0], buffers[1]},
        .index_count = (int32_t)(indices_size / sizeof(uint32_t)),
    };

    return mesh;
}


void mesh_set_vertex_attribute(Mesh mesh, uint32_t attribute_index, int32_t offset) {
    glEnableVertexArrayAttrib(mesh.vao, attribute_index);
    glVertexArrayAttribFormat(mesh.vao, attribute_index, 3, GL_FLOAT, GL_FALSE, offset);
    glVertexArrayAttribBinding(mesh.vao, attribute_index, 0); // Bind attribute location to binding point
}

void mesh_delete(Mesh mesh) {
    if (mesh.vertex_data) FREE(mesh.vertex_data);
    if (mesh.index_data) FREE(mesh.index_data);

    glBindVertexArray(0);
    glDeleteBuffers(2, mesh.buffers);
    glDeleteVertexArrays(1, &mesh.vao);
}
