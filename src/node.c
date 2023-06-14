//
// Created by josue on 2023-06-13.
//

#include "node.h"
#include "draw.h"
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
    // Generate vertices
    float quad_width = width / (float)(subdivision_x + 1);
    float quad_height = height / (float)(subdivision_y + 1);

    int32_t vertex_count = (subdivision_x + 2) * (subdivision_y + 2);
    Vertex *vertices = MALLOC(vertex_count * sizeof(Vertex));
    for (int i = 0; i < subdivision_y + 2; ++i) {
        for (int j = 0; j < subdivision_x + 2; ++j) {
            int32_t vi = i * (subdivision_x + 2) + j;
            vertices[vi] = (Vertex){
                .position = {(float)j * quad_width, (float)i * quad_height, 0.0f},
                .normal = {0.0f, 0.0f, 1.0f},
                .uv = {(float)j * quad_width / width, (float)i * quad_height / height},
            };
        }
    }

    // Generate indices
    int32_t index_count = 0;
    uint32_t *indices = MALLOC(index_count * sizeof(float));

    // Load mesh
    Mesh grid = mesh_load(vertices, vertex_count, indices, index_count);
    mesh_set_vertex_attribute(grid, 0, 0);
    mesh_set_vertex_attribute(grid, 2, 3 * sizeof(float));

    // Explicitly passing buffer ownership to the mesh struct
    grid.vertices = vertices;
    grid.vertex_count = vertex_count;
    grid.indices = indices;
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
