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

void terrain_create(Terrain *terrain, int32_t resolution, float width, float height);

void terrain_load_mesh(Terrain *terrain);

void load_heightmap(Terrain *terrain, const char *filename);

// TODO: load heightmap from png, then initialize terrain with heightmap
Terrain load_terrain_from_png(const char *filename, float world_scale);

void terrain_delete(Terrain terrain);

#endif //TOYBOX_SRC_GEOMETRY_TERRAIN_H_
