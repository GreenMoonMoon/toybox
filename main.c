#include <stdlib.h>

#include "graphic/viewport.h"
#include "graphic/material.h"
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
    GLuint buffers[2];
    glCreateBuffers(2, buffers);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    GLintptr base_offset = 0;
    GLsizei vertex_size = sizeof(float) * 3;
    GLsizei relative_offset = 0;


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    GLuint vao;
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexArrayAttrib(vao, 0);

    glVertexArrayVertexBuffer(vao, 0, buffers[0], base_offset, vertex_size); // Bind a buffer to binding point 0
    glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, relative_offset);
    glVertexArrayAttribBinding(vao, 0, 0); // Bind attribute location to binding point

    glVertexArrayElementBuffer(vao, buffers[1]);

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

        material_set_in_use(material);
        material_set_mvp(material, model, view, projection);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        viewport_swap_window(viewport);
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(2, buffers);
    material_unload(material);

    viewport_delete(viewport);

    return EXIT_SUCCESS;
}
