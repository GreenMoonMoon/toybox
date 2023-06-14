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


Node node_create();
void node_delete(Node *node);
void node_draw(Node *node);

#endif //TOYBOX_SRC_SCENE_NODE_H_
