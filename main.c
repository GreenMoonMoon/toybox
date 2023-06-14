#include <stdlib.h>

#include "viewport.h"
#include "node.h"
#include "terrain.h"

Viewport *viewport;

int main() {
    viewport_init(800, 600, "Main", &viewport);

    viewport_set_clear_color(0.1f, 1.0f, 0.1f, 1.0f);

    Node quad = node_create_quad();
    Node grid = node_create_grid(5.0f, 5.0f, 4, 4);

    Terrain terrain = terrain_load_from_png("assets/textures/heightmap.png");

    while (!viewport_is_closing(viewport)) {
        viewport_process_events(viewport);
        double delta_time = viewport_get_delta_time(viewport);

        viewport_clear();

//        node_draw(&quad);
        node_draw_wireframe(&quad);
//        node_draw_wireframe(&grid);

        viewport_swap_window(viewport);
    }

    node_delete(&quad);
    terrain_delete(terrain);

    viewport_delete(viewport);

    return EXIT_SUCCESS;
}
