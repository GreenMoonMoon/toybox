//
// Created by josue on 2023-05-29.
//

#ifndef TOYBOX_SRC_DRAW_H_
#define TOYBOX_SRC_DRAW_H_

struct Viewport;
struct Node;
struct Camera;
struct Model;

void draw_frame_start();
void draw_frame_end(struct Viewport *viewport);

void draw_node(struct Node *node, struct Camera *camera);
void draw_model(struct Model *model);

#endif //TOYBOX_SRC_DRAW_H_
