//
// Created by josue on 2023-02-16.
//

#ifndef TOYBOX_SRC_MESH_H_
#define TOYBOX_SRC_MESH_H_

#include <stdint.h>
#include <stdbool.h>
#include "types.h"
#include "cglm/cglm.h"

struct Camera;

struct MeshData {
  u8 *vertices_data;
  isize vertices_data_size;
  isize vertex_size;
  i32 *indices_data;
  isize indices_data_size;
};

typedef struct Mesh {
  struct MeshData data;
  i32 index_count;
  u32 vao;
  u32 buffers[];
} Mesh;

uint32_t mesh_load_vertex_buffer(Mesh *mesh, const uint8_t *vertices, int32_t vertex_size, size_t vertex_count);

void mesh_load(Mesh mesh);

/// Set a vertex attribute by specifying at which layout location it is going to be accessed and the data offset from
///  the start of each vertex.
/// \param mesh Input mesh
/// \param attribute_index Index corresponding to the shader layout attribute
/// \param attribute_dimension Attribute dimension. Between 1 and 4 (ex: vec3 is 3)
/// \param offset Relative offset from the start of a vertex data structure
void mesh_set_vertex_attribute(Mesh mesh, uint32_t attribute_index, int32_t attribute_dimension, int32_t offset);

/// Unload a mesh from the gpu but doesn't delete the local data.
void mesh_unload(Mesh mesh);

/// Unload a mesh from the GPU and delete local data
void mesh_delete(Mesh mesh);

Mesh new_quad_mesh(float width, float height);
Mesh new_cube_mesh(float width, float height, float depth);
Mesh new_grid_mesh(float width, float depth, int32_t subdivision_x, int32_t subdivision_y);

void mesh_draw_generic(Mesh mesh, mat4 transform, struct Camera *camera);

#endif //TOYBOX_SRC_MESH_H_
