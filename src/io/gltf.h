//
// Created by josue on 2023-02-03.
//

#ifndef SUPERMARIO_GLTF_H
#define SUPERMARIO_GLTF_H

#include <stdbool.h>

struct Model;
struct Mesh;
struct cgltf_data;

typedef struct gltfResource {
    struct cgltf_data *data;
    char *file_path;

    //map
} gltfResource;

bool load_gltf_file(const char* filename, gltfResource *gltf_resource);

void free_gltf(gltfResource gltf_resource);

size_t gltf_load_meshes_from_file(const char *filename, struct Mesh **meshes);

size_t gltf_load_models(const char *filename, struct Model **models);

#endif //SUPERMARIO_GLTF_H
