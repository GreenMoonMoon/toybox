#include <stdlib.h>

#include "viewport.h"
#include "node.h"
#include "draw.h"
#include "terrain.h"
#include "inputs.h"
#include "behavior/debug_camera.h"

Viewport *viewport;

int main() {
    viewport_init(800, 600, "Main", &viewport);

    viewport_set_clear_color(0.1f, 0.1f, 0.1f, 1.0f);

    debug_camera_init();


//    Node quad = node_create_quad();
//    Node grid = node_create_grid(5.0f, 5.0f, 4, 4);

    Terrain terrain = terrain_load_from_png("assets/textures/simple_test.png", 8.0f);
    Material material = material_load_from_files("assets/shaders/grid_test.vert", "assets/shaders/grid_test.frag");

    while (!viewport_is_closing(viewport)) {
        viewport_start_frame(viewport);
        double delta_time = viewport_get_delta_time(viewport);

        debug_camera_update(delta_time);

        draw_mesh(terrain.mesh, GLM_MAT4_IDENTITY, debug_camera.transform, debug_camera.projection, material);
//        draw_mesh_wireframe(terrain.mesh, GLM_MAT4_IDENTITY, debug_camera.transform, debug_camera.projection, material);

        viewport_end_frame(viewport);
    }

//    node_delete(&quad);
//    node_delete(&grid);
    terrain_delete(terrain);

    viewport_delete(viewport);

    return EXIT_SUCCESS;
}
