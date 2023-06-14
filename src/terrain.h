//
// Created by josue on 2023-06-13.
//

#ifndef TOYBOX_SRC_GEOMETRY_TERRAIN_H_
#define TOYBOX_SRC_GEOMETRY_TERRAIN_H_

#include "cglm/cglm.h"

struct Mesh;

typedef struct Terrain {
  struct Mesh *mesh;
  float *heightmap;
  size_t size;
} Terrain;

// TODO: load heightmap from png, then initialize terrain with heightmap
Terrain terrain_load_from_png(const char *filename);

void terrain_delete(Terrain terrain);

#endif //TOYBOX_SRC_GEOMETRY_TERRAIN_H_
