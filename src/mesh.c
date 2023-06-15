//
// Created by josue on 2023-02-16.
//

#include "mesh.h"
#include "memory.h"
#include "glad/gl.h"

Mesh mesh_load(Vertex *vertices, int32_t vertex_count, uint32_t *indices, int32_t index_count) {
    GLuint buffers[2];
    glCreateBuffers(2, buffers);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, (int64_t)(vertex_count * sizeof(Vertex)), vertices, GL_STATIC_DRAW);
    GLintptr base_offset = 0;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (int64_t)(index_count * sizeof(float)), indices, GL_STATIC_DRAW);

    GLuint vao;
    glCreateVertexArrays(1, &vao);
    glVertexArrayVertexBuffer(vao, 0, buffers[0], base_offset, sizeof(Vertex)); // Bind a buffer to binding point 0
    glVertexArrayElementBuffer(vao, buffers[1]);

    Mesh mesh = {0};
    mesh.vao = vao;
    mesh.buffers[0] = buffers[0];
    mesh.buffers[1] = buffers[1];
    mesh.index_count = index_count;

    return mesh;
}

void mesh_set_vertex_attribute(Mesh mesh, uint32_t attribute_index, int32_t offset) {
    glEnableVertexArrayAttrib(mesh.vao, attribute_index);
    glVertexArrayAttribFormat(mesh.vao, attribute_index, 3, GL_FLOAT, GL_FALSE, offset);
    glVertexArrayAttribBinding(mesh.vao, attribute_index, 0); // Bind attribute location to binding point
}

void mesh_unload(Mesh mesh) {
    // Check and unbind vertex array before deleting it
    int32_t bound_vao;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &bound_vao);
    if (bound_vao == mesh.vao) glBindVertexArray(0);

    glDeleteBuffers(2, mesh.buffers);
    glDeleteVertexArrays(1, &mesh.vao);
}

void mesh_delete(Mesh mesh) {
    mesh_unload(mesh);
    if (mesh.vertices) FREE(mesh.vertices);
    if (mesh.indices) FREE(mesh.indices);
}

Mesh create_grid_mesh(float width, float height, int32_t subdivision_x, int32_t subdivision_y){
    // Generate vertices
    float quad_width = width / (float)(subdivision_x + 1);
    float quad_height = height / (float)(subdivision_y + 1);

    int32_t vertex_count = (subdivision_x + 2) * (subdivision_y + 2);
    Vertex *vertices = MALLOC(vertex_count * sizeof(Vertex));
    for (int i = 0; i < subdivision_y + 2; ++i) {
        for (int j = 0; j < subdivision_x + 2; ++j) {
            int32_t vi = i * (subdivision_x + 2) + j;
            vertices[vi] = (Vertex){
                .position = {(float)j * quad_width, 0.0f, (float)i * quad_height},
                .normal = {0.0f, 1.0f, 0.0f},
                .uv = {(float)j * quad_width / width, (float)i * quad_height / height},
            };
        }
    }

    // Generate indices
    int32_t index_count = 0;
//    uint32_t *indices = MALLOC(index_count * sizeof(float));
    uint32_t  *indices = NULL;

    // Load mesh
    Mesh grid = mesh_load(vertices, vertex_count, indices, index_count);
    mesh_set_vertex_attribute(grid, 0, 0);
    mesh_set_vertex_attribute(grid, 2, 3 * sizeof(float));

    // Explicitly passing buffer ownership to the mesh struct
    grid.vertices = vertices;
    grid.vertex_count = vertex_count;
    grid.indices = indices;
    grid.index_count = index_count;

    return grid;
}