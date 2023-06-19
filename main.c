#include <stdlib.h>

#include "viewport.h"
#include "node.h"
#include "draw.h"
#include "terrain.h"
#include "texture.h"
#include "behavior/debug_camera.h"

Viewport *viewport;

int main() {
    viewport_init(&viewport, 800, 600, "Main");
    set_clear_color(0.1f, 0.1f, 0.1f, 1.0f);

    // Load scene
    debug_camera_init();

    TerrainMesh terrain_mesh = {0};
    terrain_create(&terrain_mesh, 20, 512, 512);

    Material terrain_material = load_tesselation_material_from_files("assets/shaders/basic_terrain.vert",
                                                                     "assets/shaders/basic_terrain.tesc",
                                                                     "assets/shaders/basic_terrain.tese",
                                                                     "assets/shaders/basic_terrain.frag");

    Texture texture = load_texture_from_png("assets/textures/grid.png");

    while (!viewport_is_closing(viewport)) {
        viewport_process_events(viewport);
        viewport_start_frame(viewport);
        double delta_time = viewport_get_delta_time(viewport);

        debug_camera_update(delta_time);

        material_set_albedo(terrain_material, &texture);
//        draw_mesh(terrain.mesh, GLM_MAT4_IDENTITY, debug_camera.transform, debug_camera.projection, terrain_material);
        draw_terrain_wireframe(&terrain_mesh, GLM_MAT4_IDENTITY, debug_camera.transform, debug_camera.projection, terrain_material);

        viewport_end_frame(viewport);
    }

    terrain_delete(terrain_mesh);
    viewport_delete(viewport);

    return EXIT_SUCCESS;
}
