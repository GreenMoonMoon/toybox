#include <stdlib.h>

#include "viewport.h"
#include "inputs.h"
#include "mesh.h"

int main(int argc, char *argv[]) {
    // Init viewport
    Viewport *viewport = new_viewport(800, 600, "Main");
//    viewport_capture_mouse(viewport);

    set_clear_color(0.1f, 0.1f, 0.1f, 1.0f);
    init_keyboard_inputs();

    // Load resources
    Mesh tri = new_mesh_triangle();
    mesh_load(&tri);

    while (!viewport_is_closing(viewport)) {
        // INPUTS
        viewport_process_events(viewport);

        viewport_start_frame(viewport);

        mesh_draw();

        viewport_end_frame(viewport);
    }

    mesh_delete(tri);
    viewport_delete(viewport);

    return EXIT_SUCCESS;
}
