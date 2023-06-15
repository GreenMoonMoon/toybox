//
// Created by josue on 2023-06-13.
//

#include "node.h"
#include "draw.h"
#include "mesh.h"
#include "camera.h"
#include "memory.h"


Node node_create_quad() {
    Vertex vertices[4] = {
        {{-1.0f, 1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},
        {{-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
        {{1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
        {{1.0f, 1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
    };

    uint32_t indices[6] = {
        0, 1, 2, 2, 3, 0,
    };

    Mesh quad = mesh_load(vertices, 4, indices, 6);
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

Node node_create_grid(float width, float height, int32_t subdivision_x, int32_t subdivision_y) {
    Mesh grid = create_grid_mesh(width, height, subdivision_x, subdivision_y);

    Material material = material_load_from_files("assets/shaders/grid_test.vert", "assets/shaders/grid_test.frag");

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
