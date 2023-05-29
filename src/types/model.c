//
// Created by josue on 2023-01-30.
//
#include "model.h"

void calculate_normal_matrix(Model *model, mat4 view_matrix){
    glm_mat4_mul(view_matrix, model->transform, model->model_view_matrix);

    if(model->scaled) {
        glm_mat4_inv(model->model_view_matrix, model->normal_matrix);
        glm_mat4_transpose(model->normal_matrix);
    } else {
        glm_mat4_copy(model->model_view_matrix, model->normal_matrix);
    }


}

void translate_model(Model *model, vec3 translation){
    glm_translate(model->transform, translation);
}

void scale_model(Model *model, vec3 scale){
    glm_scale(model->transform, scale);
    model->scaled = true;
}

void rotate_model(Model *model, float angle, vec3 axis){
    glm_rotate(model->transform, angle, axis);
}

void free_models(Model *models, int count) {
    for(int i = 0; i < count; i++){
        //TODO: free models
    }
    free(models);
}
