//
// Created by josue on 2023-06-13.
//

#ifndef TOYBOX_SRC_GEOMETRY_TERRAIN_H_
#define TOYBOX_SRC_GEOMETRY_TERRAIN_H_

#include "mesh.h"
#include "cglm/cglm.h"

typedef struct Terrain {
  float *heightmap;
  size_t size;
  struct Mesh mesh;
} Terrain;

// TODO: load heightmap from png, then initialize terrain with heightmap
Terrain terrain_load_from_png(const char *filename, float world_scale);

void terrain_delete(Terrain terrain);

#endif //TOYBOX_SRC_GEOMETRY_TERRAIN_H_
