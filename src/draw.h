//
// Created by josue on 2023-05-29.
//

#ifndef TOYBOX_SRC_DRAW_H_
#define TOYBOX_SRC_DRAW_H_

#include "material.h"
#include "mesh.h"

void draw_mesh(Mesh mesh, mat4 model, mat4 view, mat4 projection, Material material);

#endif //TOYBOX_SRC_DRAW_H_
