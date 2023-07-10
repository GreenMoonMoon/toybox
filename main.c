#include <stdlib.h>

#include "viewport.h"
#include "inputs.h"
#include "mesh.h"
#include "material.h"
#include "camera.h"

int main(int argc, char *argv[]) {
    // Init viewport
    Viewport *viewport = new_viewport(800, 600, "Main");
//    viewport_capture_mouse(viewport);

    set_clear_color(0.1f, 0.1f, 0.1f, 1.0f);
    init_keyboard_inputs();

    // Load resources
    Mesh tri = new_mesh_triangle();
    mesh_load(&tri);

    Material basic = new_material_from_files("assets/shaders/basic.vert",
                                             "assets/shaders/basic.frag");

    // Set camera
    Camera camera = new_orthographic_camera(4.0f/3.0f,
                                            (vec3){0.0f, 0.0f, -8.0f},
                                            2.0f,
                                            0.1f,
                                            100.0f);

    while (!viewport_is_closing(viewport)) {
        // INPUTS
        viewport_process_events(viewport);

        viewport_start_frame(viewport);

        material_enable(&basic);
        material_set_mvp(basic, GLM_MAT4_IDENTITY, camera.transform, camera.projection);
        mesh_draw(&tri);

        viewport_end_frame(viewport);
    }

    material_delete(&basic);
    mesh_delete(&tri);
    viewport_delete(viewport);

    return EXIT_SUCCESS;
}
