//
// Created by josue on 2023-01-23.
//

#ifndef SUPERMARIO_MESH_H
#define SUPERMARIO_MESH_H

#include <stdbool.h>
#include <stdint.h>

typedef enum DrawMode {
    POINTS_DRAW_MODE,
    LINE_STRIPS_DRAW_MODE,
    LINE_LOOPS_DRAW_MODE,
    LINES_DRAW_MODE,
    TRIANGLES_DRAW_MODE,
    TRIANGLE_STRIPS_DRAW_MODE,
    TRIANGLE_FANS_DRAW_MODE,
} DrawMode;

typedef enum AttributeIndex {
    POSITION_INDEX,
    NORMAL_INDEX,
    TANGENT_INDEX,
    TEXCOORD_INDEX,
    COLOR_INDEX,
} AttributeIndex;

typedef struct GpuBufferView {
    uint32_t handle;
    uint32_t offset;
    uint32_t stride;
} GpuBufferView;

typedef struct Primitive {
    uint32_t vao;
    uint32_t mode;
    int32_t index_count;
} Primitive;

typedef struct Mesh {
    size_t primitive_count;
    struct Primitive *primitives;
} Mesh;

void free_meshes(Mesh *meshes, size_t count);

#endif //SUPERMARIO_MESH_H
