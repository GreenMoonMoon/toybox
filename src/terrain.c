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

void terrain_create(Terrain *terrain, int32_t resolution, float width, float height) {
    struct Vertex {
      vec3 position;
      vec2 uv;
    };

    struct Vertex *vertices;
    vertices = MALLOC(resolution * resolution * sizeof(Vertex));
    if (vertices == NULL) return;

    float half_width = width / 2.0f;
    float half_height = height / 2.0f;

    // Generate patch vertices
    for (int y = 0; y < resolution - 1; ++y) {
        for (int x = 0; x < resolution - 1; ++x) {
            Vertex a = {
                {-half_width + width * x / (float) resolution, 0.0f, -half_height + height * y / (float) resolution,},
                {x / (float) resolution, y / (float) resolution},
            };

            Vertex b = {
                {-half_width + width * (x + 1) / (float) resolution, 0.0f, -half_height + height * y / (float) resolution,},
                {(x + 1) / (float) resolution, y / (float) resolution},
            };

            Vertex c = {
                {-half_width + width * x / (float) resolution, 0.0f, -half_height + height * (y + 1) / (float) resolution,},
                {x / (float) resolution, (y + 1) / (float) resolution},
            };

            Vertex d = {
                {-half_width + width * (x + 1) / (float) resolution, 0.0f, -half_height + height * (y + 1) / (float) resolution,},
                {x / (float) resolution, (y + 1) / (float) resolution},
            };
        }
    }
}

void terrain_load_mesh(Terrain *terrain) {

}

void load_heightmap(Terrain *terrain, const char *filename) {
    Image image;
    image_load_png8_file(&image, filename);
}

Terrain load_terrain_from_png(const char *filename, float world_scale) {
    // TODO: there should be a way to avoid create a transient buffer and pass a transform function to manipulate
    //  the file data directly while copying them in the final buffer.
    uint8_t *buffer;
    size_t file_size = read_png_file_r(filename, &buffer);

    assert(file_size != 0);
    assert(file_size % sizeof(uint8_t) == 0);

    Terrain terrain = {0};
    terrain.size = (uint32_t) sqrt((double) file_size);
    terrain.mesh = create_grid_mesh(40.0f, 40.0f, terrain.size - 2, terrain.size - 2);
//    terrain.heightmap = MALLOC(file_size * sizeof(float));
    for (int i = 0; i < file_size; ++i) {
        float value = (1.0f / 255.0f) * (float) buffer[i];
//        terrain.heightmap[i] = (1.0f / 255.0f) * (float)buffer[i];
        terrain.mesh.vertices[i].position[1] = value * world_scale;
    }
    FREE(buffer);

    glNamedBufferSubData(terrain.mesh.buffers[0],
                         0,
                         terrain.mesh.vertex_count * sizeof(Vertex),
                         terrain.mesh.vertices);

    return terrain;
}

void terrain_delete(Terrain terrain) {
    mesh_delete(terrain.mesh);
    FREE_ARRAY_2D(terrain.heightmap);
}
