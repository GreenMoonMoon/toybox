//
// Created by josue on 2023-02-03.
//

#ifndef SUPERMARIO_GLTF_H
#define SUPERMARIO_GLTF_H

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

#endif //SUPERMARIO_GLTF_H
