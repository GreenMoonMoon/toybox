//
// Created by josue on 2023-05-29.
//

#include "draw.h"
#include "glad/gl.h"
#include "viewport.h"

void draw_frame_start() {
    glClearColor(0.7f, 0.9f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void draw_frame_end(Viewport *viewport) {
    viewport_swap_window(viewport);
}

void draw_node(struct Node *node, struct Camera *camera) {

}

