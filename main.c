#include <stdlib.h>
#include "viewport.h"
//#include "behavior/debug_camera.h"
#include "draw.h"
//#include "model.h"
//#include "material.h"
//#include "scene.h"
//#include "gpu.h"
//#include "cglm/cglm.h"
//#include "io/gltf.h"
//#include "memory.h"

Viewport *viewport;

//Scene scene;
//Camera *main_camera;
//Model *models;

int main() {
    viewport_init(800, 600, "Main", &viewport);

//    //load resources
//    size_t model_count = gltf_load_models("assets/models/generics.glb", &models);
//    for(size_t i = 0; i < model_count; i++) {
//        gpu_load_static_model(&models[i]);
//    }

//    Shader basic_shader = shader_load_from_files("assets/shaders/basic.vert",
//                                                 "assets/shaders/basic.frag");
//    Material basic_material = {
//        .shader = basic_shader,
//    };
//
//    // Setup scene
//    scene.node_count = model_count;
//    scene.nodes = MALLOC(sizeof(Node) * scene.node_count);
//
//    uint32_t id = 0;
//    for (int i = 0; i < scene.node_count; ++i) {
//        scene.nodes[i].child_count = 0;
//        scene.nodes[i].children = NULL;
//        scene.nodes[i].id = id++;
//        scene.nodes[i].model = &models[i];
//        scene.nodes[i].material = &basic_material;
//
//        glm_mat4_identity(scene.nodes[i].transform);
//        glm_translate(scene.nodes[i].transform, (vec3){});
//        glm_mat4_identity(scene.nodes[i].normal_matrix);
//    }
//
//    // Setup camera;
//    debug_camera_init();
//    main_camera = &debug_camera;

    while (!viewport_is_closing(viewport)) {
        viewport_process_events(viewport);
        double delta_time = viewport_get_delta_time(viewport);

        // UPDATE
//        debug_camera_update(delta_time);

        // RENDER
        draw_frame_start();

//        draw_node(&scene.nodes[0], main_camera);

        draw_frame_end(viewport);
    }

//    models_delete(models, model_count);
    viewport_delete(viewport);

    return EXIT_SUCCESS;
}
