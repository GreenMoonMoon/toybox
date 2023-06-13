#include <stdlib.h>

#include "graphic/viewport.h"
#include "graphic/material.h"
#include "graphic/mesh.h"
#include "graphic/draw.h"
#include "cglm/cglm.h"
#include "glad/gl.h"

Viewport *viewport;

int main() {
    viewport_init(800, 600, "Main", &viewport);

    glClearColor(0.1f, 1.0f, 0.1f, 1.0f);

    float vertices[12] = {
        -1.0f, 1.0f, 0.0f, -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    };

    uint32_t indices[6] = {
        0, 1, 2, 2, 3, 0,
    };

    //Load mesh
    Mesh quad = mesh_load(vertices, sizeof(vertices), indices, sizeof(indices));

    // Load Material
    Material material = material_load_from_files(
        "assets/shaders/basic.vert", "assets/shaders/basic.frag"
        );

    mat4 model;
    glm_mat4_identity(model);
    mat4 view;
    glm_mat4_identity(view);
    glm_translate(view, (vec3){0.0f, 0.0f, -4.0f});
    mat4 projection;
    glm_perspective(75.0f, 4.0f/3.0f, 0.1f, 100.0f, projection);

    while (!viewport_is_closing(viewport)) {
        viewport_process_events(viewport);
        double delta_time = viewport_get_delta_time(viewport);

        glClear(GL_COLOR_BUFFER_BIT);

        draw_mesh(quad, model, view, projection, material);

        viewport_swap_window(viewport);
    }

    mesh_unload(quad);
    material_unload(material);

    viewport_delete(viewport);

    return EXIT_SUCCESS;
}
