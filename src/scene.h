//
// Created by josue on 2023-01-31.
//

#ifndef SUPERMARIO_SCENE_H
#define SUPERMARIO_SCENE_H

#include <stdbool.h>
#include <stdint.h>
#include "cglm/cglm.h"

struct Model;
struct Material;

typedef struct Node {
  size_t *children;
  size_t child_count;

  uint32_t id;
  mat4 transform;
  mat4 normal_matrix;

  struct Model *model;
  struct Material *material;
} Node;

typedef struct Scene {
    Node *nodes;
    size_t node_count;
} Scene;

void scene_delete(Scene *scene);

#endif //SUPERMARIO_SCENE_H
