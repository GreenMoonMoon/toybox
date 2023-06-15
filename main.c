#include <stdlib.h>

#include "viewport.h"
#include "node.h"
#include "draw.h"
#include "terrain.h"
#include "texture.h"
#include "inputs.h"
#include "behavior/debug_camera.h"

Viewport *viewport;

int main() {
    viewport_init(&viewport, 800, 600, "Main");

    set_clear_color(0.1f, 0.1f, 0.1f, 1.0f);

    debug_camera_init();

    Mesh mesh = create_cube_mesh(5.0f, 6.0f, 7.0f);
//    Terrain terrain = terrain_load_from_png("assets/textures/simple_test.png", 8.0f);

//    Material material = material_load_from_files("assets/shaders/grid_test.vert", "assets/shaders/grid_test.frag");
    Material material = load_material_from_files("assets/shaders/basic_texture.vert", "assets/shaders/basic_texture.frag");

    Texture texture = load_texture_from_png("assets/textures/grid.png");

    while (!viewport_is_closing(viewport)) {
        viewport_process_events(viewport);
        viewport_start_frame(viewport);
        double delta_time = viewport_get_delta_time(viewport);

        debug_camera_update(delta_time);

        material_set_albedo(material, &texture);
//        draw_mesh_wireframe(mesh, GLM_MAT4_IDENTITY, debug_camera.transform, debug_camera.projection, material);
        draw_mesh(mesh, GLM_MAT4_IDENTITY, debug_camera.transform, debug_camera.projection, material);
//        draw_mesh(terrain.mesh, GLM_MAT4_IDENTITY, debug_camera.transform, debug_camera.projection, material);

        viewport_end_frame(viewport);
    }

//    terrain_delete(terrain);
    mesh_delete(mesh);
    viewport_delete(viewport);

    return EXIT_SUCCESS;
}
