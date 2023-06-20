//
// Created by josue on 2023-06-13.
//

#ifndef TOYBOX_SRC_GEOMETRY_TERRAIN_H_
#define TOYBOX_SRC_GEOMETRY_TERRAIN_H_

#include "mesh.h"
#include "cglm/cglm.h"

typedef struct TerrainMesh {
  float *heightmap;
  size_t size;
  uint32_t vao;
  uint32_t vertex_buffer;
  int32_t index_count;
  int32_t vertex_count;
} TerrainMesh;

void terrain_create(TerrainMesh *terrain, float width, float height, int32_t resolution);

void load_heightmap(TerrainMesh *terrain, const char *filename);

// TODO: load heightmap from png, then initialize terrain with heightmap
TerrainMesh load_terrain_from_png(const char *filename, float world_scale);

void terrain_delete(TerrainMesh terrain);

#endif //TOYBOX_SRC_GEOMETRY_TERRAIN_H_
