//
// Created by josue on 2023-06-13.
//

#include "node.h"
#include <stdint.h>
#include "draw.h"


Node node_create() {
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
    mat4 view;
    glm_mat4_identity(view);
    glm_translate(view, (vec3){0.0f, 0.0f, -4.0f});
    mat4 projection;
    glm_perspective(75.0f, 4.0f/3.0f, 0.1f, 100.0f, projection);


    Node node = {
        .mesh = quad,
        .material = material,
        .model = {0},
        .view = {0},
        .projection = {0},
    };
    glm_mat4_copy(model, node.model);
    glm_mat4_copy(view, node.view);
    glm_mat4_copy(projection, node.projection);
    return node;
}

void node_delete(Node *node) {
    mesh_delete(node->mesh);
    material_unload(node->material);
}

void node_draw(Node *node) {
    draw_mesh(node->mesh, node->model, node->view, node->projection, node->material);
}
