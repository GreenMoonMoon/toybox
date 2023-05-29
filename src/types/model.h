//
// Created by josue on 2023-01-29.
//

#ifndef SUPERMARIO_MODEL_H
#define SUPERMARIO_MODEL_H

#include <stdbool.h>

#include "mesh.h"
#include "shader.h"
#include "cglm/cglm.h"

struct ListNode;

typedef struct Model {
    struct ListNode *node;
    struct Mesh mesh;
    mat4 transform;
    mat4 model_view_matrix;
    mat4 normal_matrix;
    bool scaled;

    Shader shader;
} Model;

Model *models;
struct ListNode *model_node_pool;

void allocate_model_node_pool(size_t model_count);


void calculate_normal_matrix(Model *model, mat4 view_matrix);

void translate_model(Model *model, vec3 translation);

void scale_model(Model *model, vec3 scale);

void rotate_model(Model *model, float angle, vec3 axis);

void free_models(Model *models, int count);

#endif //SUPERMARIO_MODEL_H
