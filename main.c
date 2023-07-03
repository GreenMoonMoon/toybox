#include <stdlib.h>

#include "viewport.h"
#include "inputs.h"
#include "mesh.h"
#include "shader.h"

//#include "ui.h"
//#include "node.h"
//#include "draw.h"
//#include "terrain.h"
//#include "texture.h"

#include "behavior/debug_camera.h"

int main(int argc, char *argv[]) {
    Viewport *viewport = viewport_new(800, 600, "Toybox");
    set_mouse_mode(MOUSE_MODE_CAPTURED);
    set_clear_color(0.1f, 0.1f, 0.1f, 1.0f);

    init_keyboard_inputs();
    init_default_shaders();

    // Load scene
    debug_camera_init();

    Mesh cube = new_cube_mesh(1.0f, 1.0f, 1.0f);
    mesh_load(cube);

//    TerrainMesh terrain_mesh = {0};
//    terrain_create(&terrain_mesh, 128.0f, 128.0f, 32);
//
//    Material terrain_material = load_tesselation_material_from_files("assets/shaders/basic_terrain.vert",
//                                                                     "assets/shaders/basic_terrain.tesc",
//                                                                     "assets/shaders/basic_terrain.tese",
//                                                                     "assets/shaders/basic_terrain.frag");
//
//    Mesh cube_mesh = create_cube_mesh(1.0f, 1.0f, 1.0f);
//    Material cube_material = load_material_from_files("assets/shaders/basic.vert", "assets/shaders/basic.frag");
//
//    Texture texture = load_texture_from_png("assets/textures/grid.png");
//    Texture heightmap = load_texture_from_png("assets/textures/simple_test.png");

    // UI
//    ctx = ui_init(viewport);
//    struct nk_font_atlas *atlas;
//    ui_load_fonts(ctx, atlas);


    while (!viewport_should_close(viewport)) {
        input:
        {
            viewport_process_events(viewport);
    //        SDL_Event event;
    //        ui_event_start(ctx);
    //        while (SDL_PollEvent(&event)) {
    //            if (event.type == SDL_QUIT) viewport_set_is_closing(viewport);
    //            ui_handle_event(&event);
    //        } ui_event_end(ctx);
        }


        render:
        {
            start_frame();
            double delta_time = viewport_get_delta_time(viewport);
            debug_camera_update(delta_time);

//        material_set_albedo(cube_material, &texture);
//        draw_mesh(cube_mesh, GLM_MAT4_IDENTITY, debug_camera.transform, debug_camera.projection, cube_material);

            mesh_draw_generic(cube, GLM_MAT4_IDENTITY, &debug_camera);

//        material_set_heightmap(terrain_material, &heightmap);
//        material_set_scale(terrain_material, 20.0f);
//        material_set_offset(terrain_material, -10.0f);
//        draw_terrain_wireframe(&terrain_mesh, GLM_MAT4_IDENTITY, debug_camera.transform, debug_camera.projection, terrain_material);

            // DRAW UI
//        ui_draw_demo(ctx);

            end_frame();
        }
    }

    quit:
    {
//    ui_delete();
//    texture_unload(texture);
//    texture_unload(heightmap);
//    material_unload(cube_material);
//    material_unload(terrain_material);
//    mesh_delete(cube_mesh);
//    terrain_delete(terrain_mesh);

        mesh_unload(cube);
        mesh_delete(cube);

        viewport_delete(viewport);
    }

    return EXIT_SUCCESS;
}
