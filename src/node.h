//
// Created by josue on 2023-06-13.
//

#ifndef TOYBOX_SRC_SCENE_NODE_H_
#define TOYBOX_SRC_SCENE_NODE_H_

#include "mesh.h"
#include "material.h"
#include "cglm/cglm.h"

typedef struct Node {
  Mesh mesh;
  Material material;
  mat4 model;
  mat4 view;
  mat4 projection;
} Node;


Node node_create_quad();
Node node_create_grid(float width, float depth, uint32_t subdivision_x, uint32_t subdivision_y);

void node_delete(Node *node);
void node_draw(Node *node);
void node_draw_wireframe(Node *node);

#endif //TOYBOX_SRC_SCENE_NODE_H_
