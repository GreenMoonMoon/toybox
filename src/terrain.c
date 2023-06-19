//
// Created by josue on 2023-06-13.
//

#include "terrain.h"
#include <assert.h>
#include "io/file.h"
#include "io/image.h"
#include "types/array_2d.h"
#include "cglm/cglm.h"
#include "glad/gl.h"

struct TerrainVertex {
  vec3 position;
  vec2 uv;
};

enum TerrainAttribute {
  TERRAIN_POSITION,
  TERRAIN_UV,
};

void terrain_load_mesh(TerrainMesh *terrain, struct TerrainVertex *vertices, size_t vertices_size) {
#ifndef NDEBUG
    if(terrain->vao > 0){
        fprintf(stderr, "TerrainMesh object is already loaded!");
        return;
    }
#endif

    // Load vertex buffer
    glCreateBuffers(1, &terrain->vertex_buffer);
    glNamedBufferData(terrain->vertex_buffer, (int64_t)vertices_size, vertices, GL_STATIC_DRAW);
//    glBufferStorage(terrain->vertex_buffer, vertices_size, (uint8_t*)vertices, );

    // Bind vertex buffer
    glCreateVertexArrays(1, &terrain->vao);
    glVertexArrayVertexBuffer(terrain->vao, 0, terrain->vertex_buffer, 0, sizeof(struct TerrainVertex));

    // Set vertex attribute (terrain mesh is Position and UV)
    // Position
    glEnableVertexArrayAttrib(terrain->vao, TERRAIN_POSITION);
    glVertexArrayAttribFormat(terrain->vao, TERRAIN_POSITION, 3, GL_FLOAT, GL_FALSE, offsetof(struct TerrainVertex, position));
    glVertexArrayAttribBinding(terrain->vao, TERRAIN_POSITION, 0);
    // UV
    glEnableVertexArrayAttrib(terrain->vao, TERRAIN_UV);
    glVertexArrayAttribFormat(terrain->vao, TERRAIN_UV, 2, GL_FLOAT, GL_FALSE, offsetof(struct TerrainVertex, uv));
    glVertexArrayAttribBinding(terrain->vao, TERRAIN_UV, 0);
}

void terrain_create(TerrainMesh *terrain, int32_t resolution, float width, float height) {
    struct TerrainVertex *vertices;
    terrain->vertex_count = resolution * resolution * 4;
    size_t vertices_size = terrain->vertex_count * sizeof(struct TerrainVertex);
    vertices = MALLOC(vertices_size);
    if (vertices == NULL) return;

    float half_width = width / 2.0f;
    float half_height = height / 2.0f;

    // Generate patch vertices
    size_t index = 0;
    for (int y = 0; y < resolution - 1; ++y) {
        for (int x = 0; x < resolution - 1; x += 4) {
            struct TerrainVertex a = {
                {(width * x)/resolution - half_width, 0.0f, (height * y)/resolution - half_height},
                {x / (float) resolution, y / (float) resolution},
            };
            vertices[index++] = a;

            struct TerrainVertex b = {
                {(width * (x + 1))/resolution - half_width, 0.0f, (height * y)/resolution - half_height},
                {(x + 1) / (float) resolution, y / (float) resolution},
            };
            vertices[index++] = b;

            struct TerrainVertex c = {
                {(width * x)/resolution - half_width, 0.0f, (height * (y + 1))/resolution - half_height},
                {x / (float) resolution, (y + 1) / (float) resolution},
            };
            vertices[index++] = c;

            struct TerrainVertex d = {
                {(width * (x + 1))/resolution - half_width, 0.0f, (height * (y + 1))/resolution - half_height},
                {x / (float) resolution, (y + 1) / (float) resolution},
            };
            vertices[index++] = d;
        }
    }
    terrain_load_mesh(terrain, vertices, vertices_size);
}

//void load_heightmap(TerrainMesh *terrain, const char *filename) {
//    Image image;
//    image_load_png8_file(&image, filename);
//}

//TerrainMesh load_terrain_from_png(const char *filename, float world_scale) {
//    // TODO: there should be a way to avoid create a transient buffer and pass a transform function to manipulate
//    //  the file data directly while copying them in the final buffer.
//    uint8_t *buffer;
//    size_t file_size = read_png_file_r(filename, &buffer);
//
//    assert(file_size != 0);
//    assert(file_size % sizeof(uint8_t) == 0);
//
//    TerrainMesh terrain = {0};
//    terrain.size = (uint32_t) sqrt((double) file_size);
//    terrain.mesh = create_grid_mesh(40.0f, 40.0f, terrain.size - 2, terrain.size - 2);
////    terrain.heightmap = MALLOC(file_size * sizeof(float));
//    for (int i = 0; i < file_size; ++i) {
//        float value = (1.0f / 255.0f) * (float) buffer[i];
////        terrain.heightmap[i] = (1.0f / 255.0f) * (float)buffer[i];
//        terrain.mesh.vertices[i].position[1] = value * world_scale;
//    }
//    FREE(buffer);
//
//    glNamedBufferSubData(terrain.mesh.buffers[0],
//                         0,
//                         terrain.mesh.vertex_count * sizeof(Vertex),
//                         terrain.mesh.vertices);
//
//    return terrain;
//}

void terrain_delete(TerrainMesh terrain) {
    int32_t bound_vao;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &bound_vao);
    if(bound_vao == terrain.vao) glBindVertexArray(0);

    glDeleteVertexArrays(1, &terrain.vao);
    glDeleteBuffers(1, &terrain.vertex_buffer);
}
