//
// Created by josue on 2023-01-27.
//

#include "mesh.h"
#include <stdlib.h>
#include "glad/gl.h"

void free_meshes(Mesh *meshes, size_t count){
    for (int i = 0; i < count; ++i) {
        free(meshes[i].primitives);
    }

    GLenum mode = GL_TRIANGLES;
}
