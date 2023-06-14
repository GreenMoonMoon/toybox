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
        .index_count = (int32_t)(indices_size / sizeof(uint32_t)),
    };
    return mesh;
}

void mesh_unload(Mesh mesh) {
    glBindVertexArray(0);
    glDeleteBuffers(2, mesh.buffers);
    glDeleteVertexArrays(1, &mesh.vao);
}