//
// Created by josue on 2023-06-13.
//

#ifndef TOYBOX_SRC_SCENE_NODE_H_
#define TOYBOX_SRC_SCENE_NODE_H_

#include "mesh.h"
#include "material.h"
#include "cglm/cglm.h"

struct Camera;

typedef struct Node {
  Mesh mesh;
  Material material;
  mat4 transform;
} Node;


Node node_create_quad();
Node node_create_grid(float width, float height, int32_t subdivision_x, int32_t subdivision_y);
void node_delete(Node *node);

void node_draw(Node *node, struct Camera *camera);
void node_draw_wireframe(Node *node, struct Camera *camera);

#endif //TOYBOX_SRC_SCENE_NODE_H_
