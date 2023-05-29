//
// Created by josue on 2023-01-30.
//

#include "types/model.h"
#include "camera.h"

#include "cglm/cglm.h"

#ifndef SUPERMARIO_SPINNING_MONKEY_H
#define SUPERMARIO_SPINNING_MONKEY_H

extern Camera *main_camera;

Model monkey_model;
vec3 rotation_axis = {0.707f, 0.707f, 0.0f};

void spinning_monkey_init(void){}

void spinning_monkey_update(double delta_time){
    rotate_model(&monkey_model, 2.5f * (float)delta_time, rotation_axis);
    calculate_normal_matrix(&monkey_model, (*main_camera).transform);
}

void spinning_monkey_draw(){
    draw_model(&monkey_model, *main_camera);
}

//void spining_monkey_delete(void){}

#endif //SUPERMARIO_SPINNING_MONKEY_H
