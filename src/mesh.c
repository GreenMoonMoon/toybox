//
// Created by josue on 2023-02-16.
//

#include "mesh.h"
#include <string.h>
#include <stdint.h>
#include "memory.h"
#include "glad/gl.h"

uint32_t mesh_load_vertex_buffer(Mesh *mesh, const uint8_t *vertices, int32_t vertex_size, size_t vertex_count) {
    GLuint buffer;
    glCreateBuffers(1, &buffer);

    glNamedBufferData(buffer, (int64_t)(vertex_size * vertex_count), vertices, GL_STATIC_DRAW);

    glCreateVertexArrays(1, &mesh->vao);
    glVertexArrayVertexBuffer(mesh->vao, 0, buffer, 0, vertex_size);

}

void mesh_load(Mesh *mesh) {
    GLuint buffers[2];
    glCreateBuffers(2, buffers);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, (int64_t)(mesh->vertices_count * sizeof(Vertex)), mesh->vertices, GL_STATIC_DRAW);
    GLintptr base_offset = 0;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (int64_t)(mesh->indices_count * sizeof(float)), mesh->indices, GL_STATIC_DRAW);

    GLuint vao;
    glCreateVertexArrays(1, &vao);
    glVertexArrayVertexBuffer(vao, 0, buffers[0], base_offset, sizeof(Vertex)); // Bind a buffer to binding point 0
    glVertexArrayElementBuffer(vao, buffers[1]);

    mesh->vao = vao;
    mesh->buffers[0] = buffers[0];
    mesh->buffers[1] = buffers[1];

    mesh_set_vertex_attribute(mesh, 0, 3, offsetof(Vertex, position));
    mesh_set_vertex_attribute(mesh, 2, 2, offsetof(Vertex, uv));
}

void mesh_set_vertex_attribute(Mesh *mesh, uint32_t attribute_index, int32_t attribute_dimension, int32_t offset) {
    glEnableVertexArrayAttrib(mesh->vao, attribute_index);
    glVertexArrayAttribFormat(mesh->vao, attribute_index, attribute_dimension, GL_FLOAT, GL_FALSE, offset);
    glVertexArrayAttribBinding(mesh->vao, attribute_index, 0); // Bind attribute location to binding point
}

void mesh_unload(Mesh *mesh) {
    int32_t bound_vao;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &bound_vao);
    if (bound_vao == mesh->vao) glBindVertexArray(0);

    glDeleteBuffers(2, mesh->buffers);
    mesh->buffers[0] = 0;
    mesh->buffers[1] = 0;
    glDeleteVertexArrays(1, &mesh->vao);
    mesh->vao = 0;
}

void mesh_delete(Mesh *mesh) {
    if (mesh->vao) {
        mesh_unload(mesh);
    }
    if (mesh->vertices) {
        free(mesh->vertices);
        mesh->vertices = NULL;
        mesh->vertices_count = 0;
    }
    if (mesh->indices) {
        free(mesh->indices);
        mesh->indices = NULL;
        mesh->indices_count = 0;
    }
}

Mesh new_mesh_quad(float width, float height) {
    const Vertex vertices[] = {
        {{0.0f,  height, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},
        {{0.0f,  0.0f,   0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
        {{width, 0.0f,   0.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
        {{width, height, 0.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
    };

    const uint32_t indices[] = {
        0, 1, 2, 2, 3, 0,
    };

    Mesh quad = {
        .vertices = malloc(sizeof(vertices)),
        .vertices_count = sizeof(vertices) / sizeof(Vertex),
        .indices = malloc(sizeof(indices)),
        .indices_count = 3
    };

    memcpy(quad.vertices, vertices, sizeof(vertices));
    memcpy(quad.indices, indices, 3);

    return quad;
}

Mesh new_mesh_cube(float width, float height, float depth) {
    const Vertex vertices[] = {
        {{ 0.0f, height,  0.0f}, { 0.57535f, -0.57535f,  0.57535f}, {0.0f, 1.0f}},
        {{ 0.0f,   0.0f,  0.0f}, { 0.57535f,  0.57535f,  0.57535f}, {0.0f, 0.0f}},
        {{width,   0.0f,  0.0f}, {-0.57535f,  0.57535f,  0.57535f}, {1.0f, 0.0f}},
        {{width, height,  0.0f}, {-0.57535f, -0.57535f,  0.57535f}, {1.0f, 1.0f}},
        {{ 0.0f, height, depth}, { 0.57535f, -0.57535f, -0.57535f}, {0.0f, 1.0f}},
        {{ 0.0f,   0.0f, depth}, { 0.57535f,  0.57535f, -0.57535f}, {0.0f, 0.0f}},
        {{width,   0.0f, depth}, {-0.57535f,  0.57535f, -0.57535f}, {1.0f, 0.0f}},
        {{width, height, depth}, {-0.57535f, -0.57535f, -0.57535f}, {1.0f, 1.0f}},
    };

    const uint32_t indices[] = {
        1, 0, 2, 3, 2, 0,
        2, 3, 6, 7, 6, 3,
        6, 7, 5, 4, 5, 7,
        5, 4, 1, 0, 1, 4,
        0, 4, 3, 7, 3, 4,
        5, 1, 6, 2, 6, 1,
    };

    Mesh cube = {
        .vertices = malloc(sizeof(vertices)),
        .vertices_count = sizeof(vertices) / sizeof(Vertex),
        .indices = malloc(sizeof(indices)),
        .indices_count = 3
    };

    memcpy(cube.vertices, vertices, sizeof(vertices));
    memcpy(cube.indices, indices, 3);

    return cube;
}

Mesh new_mesh_grid(float width, float depth, int32_t subdivision_x, int32_t subdivision_y){
    Mesh grid;

    // Generate vertices
    float quad_width = width / (float)(subdivision_x + 1);
    float quad_height = depth / (float)(subdivision_y + 1);
    float uv_factor_x = 1.0f / (float)(subdivision_x + 2);
    float uv_factor_y = 1.0f / (float)(subdivision_y + 2);

    grid.vertices_count = (subdivision_x + 2) * (subdivision_y + 2);
    grid.vertices = malloc(grid.vertices_count * sizeof(Vertex));
    for (int y = 0; y < subdivision_y + 2; ++y) {
        for (int x = 0; x < subdivision_x + 2; ++x) {
            int32_t vi = y * (subdivision_x + 2) + x;
            grid.vertices[vi] = (Vertex){
                .position = {(float)x * quad_width, 0.0f, (float)y * quad_height},
                .normal = {0.0f, 1.0f, 0.0f},
                .uv = {(float)x * uv_factor_x, (float)y * uv_factor_y},
            };
        }
    }

    // Generate indices
    grid.indices_count = ((subdivision_x + 1 ) * (subdivision_y + 1)) * 6;
    grid.indices = malloc(grid.indices_count * sizeof(uint32_t));
    uint32_t index = 0;
    for (int y = 0; y < subdivision_y + 1; ++y) {
        for (int x = 0; x < subdivision_x + 1; ++x) {
            uint32_t bl = y * (subdivision_x + 2 ) + x;          // bottom left
            uint32_t tl = (y + 1) * (subdivision_x + 2) + x;     // top left
            uint32_t br = y * (subdivision_x + 2 ) + x + 1;      // bottom right
            uint32_t tr = (y + 1) * (subdivision_x + 2) + x + 1; // top right

            // first quad triangle
            grid.indices[index++] = br;
            grid.indices[index++] = bl;
            grid.indices[index++] = tl;

            // second quad triangle
            grid.indices[index++] = tl;
            grid.indices[index++] = tr;
            grid.indices[index++] = br;
        }
    }

    return grid;
}

Mesh new_mesh_triangle() {
    const Vertex vertices[] = {
        {{0.0f,  0.5f,   0.0f}, { 0.57535f, -0.57535f,  0.57535f}, {0.0f, 1.0f}},
        {{-0.5f, -0.5f,  0.0f}, { 0.57535f,  0.57535f,  0.57535f}, {0.0f, 0.0f}},
        {{0.5f,  -0.5f,  0.0f}, {-0.57535f,  0.57535f,  0.57535f}, {1.0f, 0.0f}},
    };

    const uint32_t indices[] = {0, 1, 2};

    Mesh triangle = {
        .vertices = malloc(sizeof(vertices)),
        .vertices_count = sizeof(vertices) / sizeof(Vertex),
        .indices = malloc(sizeof(indices)),
        .indices_count = 3
    };

    memcpy(triangle.vertices, vertices, sizeof(vertices));
    memcpy(triangle.indices, indices, 3);

    return triangle;
}

void mesh_draw(Mesh *mesh) {
    glBindVertexArray(mesh->vao);
    glDrawArrays(GL_TRIANGLES, 0, mesh->indices_count);
}
