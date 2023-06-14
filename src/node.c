//
// Created by josue on 2023-06-13.
//

#include "node.h"
#include "draw.h"
#include "camera.h"
#include "memory.h"


Node node_create_quad() {
    float vertices[20] = {
        -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
        -1.0f, -1.0f,  0.0f,  0.0f,  0.0f,
         1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         1.0f,  1.0f,  0.0f,  1.0f,  1.0f,
    };

    uint32_t indices[6] = {
        0, 1, 2, 2, 3, 0,
    };

    Mesh quad = mesh_load((uint8_t *)vertices, sizeof(vertices), 5 * sizeof(float), indices, sizeof(indices));
    mesh_set_vertex_attribute(quad, 0, 0);
    mesh_set_vertex_attribute(quad, 2, 3 * sizeof(float));

    Material material = material_load_from_files("assets/shaders/basic.vert", "assets/shaders/basic.frag");

    mat4 model;
    glm_mat4_identity(model);

    Node node = {
        .mesh = quad,
        .material = material,
        .transform = {0},
    };
    glm_mat4_copy(model, node.transform);
    return node;
}

Node node_create_grid(float width, float depth, uint32_t subdivision_x, uint32_t subdivision_y) {
    // Generate vertices
    int32_t vertex_size = 3 * sizeof(float);
    int64_t vertex_data_size = (subdivision_x + 1) * (subdivision_y + 1) * (int64_t)sizeof(float) * 3;
    float *vertex_data = MALLOC(vertex_data_size);

    // Generate indices
    int32_t index_count = 0;
    int64_t index_data_size = 0;
    uint32_t *index_data = MALLOC(index_data_size);

    // Load mesh
    Mesh grid = mesh_load((uint8_t *)vertex_data, vertex_data_size, vertex_size, index_data, index_data_size);
    mesh_set_vertex_attribute(grid, 0, 0);
    mesh_set_vertex_attribute(grid, 2, 3 * sizeof(float));

    // Explicitly passing buffer ownership to the mesh struct
    grid.vertex_data = (uint8_t*)vertex_data;
    grid.vertex_data_size = vertex_size;
    grid.index_data = index_data;
    grid.index_data_size = index_data_size;
    grid.index_count = index_count;

    Material material = material_load_from_files("assets/shaders/basic.vert", "assets/shaders/basic.frag");

    mat4 model;
    glm_mat4_identity(model);

    Node node = {
        .mesh = grid,
        .material = material,
        .transform = {0},
    };
    glm_mat4_copy(model, node.transform);

    return node;
}

void node_delete(Node *node) {
    mesh_delete(node->mesh);
    material_unload(node->material);
}

void node_draw(Node *node, Camera *camera) {
    draw_mesh(node->mesh, node->transform, camera->transform, camera->projection, node->material);
}

void node_draw_wireframe(Node *node, Camera *camera) {
    draw_mesh_wireframe(node->mesh, node->transform, camera->transform, camera->projection, node->material);
}
