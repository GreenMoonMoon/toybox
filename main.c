#include <stdlib.h>
#include "viewport.h"
#include "camera.h"
#include "cglm/cglm.h"

Camera *main_camera;

int main() {
    Viewport *viewport;
    viewport_init(800, 600, "Main", &viewport);

    //load resources
    Model *models;
    int model_count = load_model("C:\\Users\\josue\\Projects\\supermario64\\assets\\scenes\\physics_tests.m3d", models);
    for(int i = 0; i < model_count; i++) {

    }

    Shader shaders[1];
    shaders[0] = load_glsl_from_files("C:/Users/josue/Projects/supermario64/assets/shaders/basic.vert",
                                      "C:/Users/josue/Projects/supermario64/assets/shaders/basic.frag");

    uint32_t id = 0;
    Node *nodes = malloc(mesh_count * sizeof(Mesh));
    for (int i = 0; i < mesh_count; ++i) {
        nodes[i].child_count = 0;
        nodes[i].children = NULL;
        nodes[i].id = id++;
        nodes[i].mesh_index = i;
        nodes[i].shader_index = 0;

        glm_mat4_identity(nodes[i].transform);
        glm_mat4_identity(nodes[i].normal_matrix);
    }

    Scene scene = {
        .root_node_indices = malloc(mesh_count * sizeof(size_t)),
        .root_node_count = mesh_count,
    };
    scene.root_node_indices[0] = 0;
    scene.root_node_indices[1] = 1;
    scene.root_node_indices[2] = 2;

    free_gltf(gltf);

    // Setup camera;
    debug_camera_init();
    main_camera = &debug_camera;

    while (!viewport_is_closing(viewport)) {
        glfwPollEvents();
        double delta_time = get_delta_time();

        // UPDATE
        debug_camera_update(delta_time);

        // RENDER
        render_begin();

        draw_node(nodes[0], *main_camera, meshes, shaders);

        render_end();
    }

    free_meshes(meshes, mesh_count);
    free_scene(scene);
    viewport_delete(viewport);

    return EXIT_SUCCESS;
}
