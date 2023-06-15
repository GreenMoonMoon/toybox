//
// Created by josue on 2023-01-30.
//

#ifndef SUPERMARIO_DEBUG_CAMERA_H
#define SUPERMARIO_DEBUG_CAMERA_H

#include "camera.h"
#include "inputs.h"

#include "cglm/cglm.h"

Camera debug_camera;
const float camera_speed = 7.5f;

void debug_camera_init(void){
    debug_camera = camera_create_perspective(4.0f/3.0f, (vec3){-5.0f, 1.0f, -8.0f}, 75.0f, 0.1f, 100.0f);
    glm_rotate_x(debug_camera.transform, -0.25f, debug_camera.transform);
}

void debug_camera_update(double delta_time){
    vec3 move_input = {
        input_get_horizontal_axis(),
        0.0f,
        input_get_vertical_axis()
    };
    glm_vec3_normalize(move_input);
    glm_vec3_scale(move_input, delta_time * camera_speed, move_input);

    glm_translate(debug_camera.transform, move_input);
}

//debug_camera_draw();

//debug_camera_delete();

#endif //SUPERMARIO_DEBUG_CAMERA_H
