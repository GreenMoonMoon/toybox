//
// Created by josue on 2023-02-03.
//

#ifndef SUPERMARIO_NODE_H
#define SUPERMARIO_NODE_H

#include <stdbool.h>
#include "cglm/cglm.h"

typedef struct Node {
    size_t *children;
    size_t child_count;

    uint32_t id;
    mat4 transform;
    mat4 normal_matrix; // TODO: is it neccessary to hold onto the normal matrix?
    uint32_t mesh_index;
    uint32_t shader_index;
} Node;

#endif //SUPERMARIO_NODE_H
