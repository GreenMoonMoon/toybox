//
// Created by josue on 2023-01-31.
//

#ifndef SUPERMARIO_SCENE_H
#define SUPERMARIO_SCENE_H

#include <stdbool.h>
#include <stdint.h>
#include "cglm/cglm.h"

typedef struct Node {
  size_t *children;
  size_t child_count;

  uint32_t id;
  mat4 transform;
  mat4 normal_matrix;
  uint32_t mesh_index;
  uint32_t shader_index;
} Node;

typedef struct Scene {
    uint32_t *root_node_indices;
    size_t root_node_count;
} Scene;

void scene_delete(Scene *scene);

#endif //SUPERMARIO_SCENE_H
