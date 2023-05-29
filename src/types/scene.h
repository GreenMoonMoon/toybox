//
// Created by josue on 2023-01-31.
//

#ifndef SUPERMARIO_SCENE_H
#define SUPERMARIO_SCENE_H

#include <stdbool.h>
#include <stdint.h>

struct Node;
struct Mesh;

typedef struct Scene {
    uint32_t *root_node_indices;
    size_t root_node_count;
} Scene;

void free_scene(Scene scene);

#endif //SUPERMARIO_SCENE_H
