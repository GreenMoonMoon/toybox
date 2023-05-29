//
// Created by josue on 2023-01-31.
//

#include "scene.h"
#include <stdlib.h>

void free_scene(Scene scene){
    free(scene.root_node_indices);
}