#include <stdlib.h>

#include "graphic/viewport.h"
#include "graphic/material.h"
#include "graphic/mesh.h"
#include "graphic/draw.h"

#include "scene/node.h"
#include "cglm/cglm.h"

Viewport *viewport;

int main() {
    viewport_init(800, 600, "Main", &viewport);

    viewport_set_clear_color(0.1f, 1.0f, 0.1f, 1.0f);

    Node node = node_create();

    while (!viewport_is_closing(viewport)) {
        viewport_process_events(viewport);
        double delta_time = viewport_get_delta_time(viewport);

        viewport_clear();

        node_draw(&node);

        viewport_swap_window(viewport);
    }

    node_delete(&node);

    viewport_delete(viewport);

    return EXIT_SUCCESS;
}
