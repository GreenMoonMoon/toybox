#include <stdlib.h>

#include "viewport.h"
#include "node.h"
#include "terrain.h"

Viewport *viewport;

int main() {
    viewport_init(800, 600, "Main", &viewport);

    viewport_set_clear_color(0.1f, 1.0f, 0.1f, 1.0f);

    Node node = node_create();

    Terrain terrain = terrain_load_from_png("assets/textures/heightmap.png");

    while (!viewport_is_closing(viewport)) {
        viewport_process_events(viewport);
        double delta_time = viewport_get_delta_time(viewport);

        viewport_clear();

        node_draw(&node);

        viewport_swap_window(viewport);
    }

    node_delete(&node);
    terrain_delete(terrain);

    viewport_delete(viewport);

    return EXIT_SUCCESS;
}
