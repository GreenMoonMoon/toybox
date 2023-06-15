#include <stdlib.h>

#include "viewport.h"
#include "node.h"
#include "camera.h"
#include "draw.h"
#include "terrain.h"
#include "inputs.h"

Viewport *viewport;

int main() {
    viewport_init(800, 600, "Main", &viewport);

    viewport_set_clear_color(0.1f, 0.1f, 0.1f, 1.0f);

    Camera camera = camera_create_perspective(4.0f/3.0f, (vec3){-6.2f, 0.75f, -35.0f}, 75.0f, 0.1f, 100.0f);
    glm_rotate_x(camera.transform, -0.25f, camera.transform);

//    Node quad = node_create_quad();
//    Node grid = node_create_grid(5.0f, 5.0f, 4, 4);

    Terrain terrain = terrain_load_from_png("assets/textures/simple_test.png");
    Material material = material_load_from_files("assets/shaders/grid_test.vert", "assets/shaders/grid_test.frag");

    while (!viewport_is_closing(viewport)) {
        viewport_start_frame(viewport);
        double delta_time = viewport_get_delta_time(viewport);

        vec3 move_input = {
            input_get_horizontal_axis(),
            0.0f,
            input_get_vertical_axis()
        };
        glm_vec3_normalize(move_input);
        glm_vec3_scale(move_input, delta_time * 5.0f, move_input);

        glm_translate(camera.transform, move_input);

//        node_draw(&quad, &camera);
//        node_draw_wireframe(&quad, &camera);
//        node_draw_wireframe(&grid, &camera);
        draw_mesh_wireframe(terrain.mesh, GLM_MAT4_IDENTITY, camera.transform, camera.projection, material);

        viewport_end_frame(viewport);
    }

//    node_delete(&quad);
//    node_delete(&grid);
    terrain_delete(terrain);

    viewport_delete(viewport);

    return EXIT_SUCCESS;
}
