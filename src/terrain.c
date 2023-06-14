//
// Created by josue on 2023-06-13.
//

#include "terrain.h"
#include <assert.h>
#include <stdio.h>
#include "io/file.h"
#include "types/array_2d.h"
#include "mesh.h"
#include "cglm/cglm.h"

Terrain terrain_load_from_png(const char *filename) {
    uint8_t *buffer;
    size_t file_size = read_png_file(filename, &buffer);

    assert(file_size != 0);
    assert(file_size % sizeof(uint8_t) == 0);

    Terrain terrain = {0};
    terrain.heightmap = MALLOC(file_size * sizeof(float));
    for (int i = 0; i < file_size; ++i) {
        terrain.heightmap[i] = (1.0f / 255.0f) * (float)buffer[i];
    }
    terrain.size = (uint32_t)sqrt((double)file_size);
    FREE(buffer);

    return terrain;
}

void terrain_delete(Terrain terrain){
    if (terrain.mesh) mesh_delete(*terrain.mesh);
    FREE_ARRAY_2D(terrain.heightmap);
}