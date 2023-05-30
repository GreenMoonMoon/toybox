//
// Created by josue on 2023-01-29.
//

#ifndef SUPERMARIO_MODEL_H
#define SUPERMARIO_MODEL_H

#include <stdbool.h>
#include "cglm/cglm.h"
#include "mesh.h"
#include "gpu_generics.h"

struct ListNode;
struct Material;

typedef struct Model {
    mat4 transform;
    mat4 model_view_matrix;
    mat4 normal_matrix;
    bool scaled;

    Mesh *meshes;
    int32_t mesh_count;
    struct Material *material;
} Model;

struct ListNode *model_node_pool;

void allocate_model_node_pool(size_t model_count);

void calculate_normal_matrix(Model *model, mat4 view_matrix);

void translate_model(Model *model, vec3 translation);

void scale_model(Model *model, vec3 scale);

void rotate_model(Model *model, float angle, vec3 axis);

void free_models(Model *models, int count);

void model_delete(Model *model);

void models_delete(Model *models, size_t model_count);

#endif //SUPERMARIO_MODEL_H
