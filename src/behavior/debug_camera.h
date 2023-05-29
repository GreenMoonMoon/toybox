//
// Created by josue on 2023-01-30.
//

#ifndef SUPERMARIO_DEBUG_CAMERA_H
#define SUPERMARIO_DEBUG_CAMERA_H

#include "camera.h"
#include "scene/inputs.h"

#include "cglm/cglm.h"

extern const float ASPECT;
Camera debug_camera;
const float camera_speed = 10.0f;

void debug_camera_init(void){
    debug_camera = create_perspective_camera(ASPECT);
}

void debug_camera_update(double delta_time){
//    vec3 move_input = {INPUT.RIGHT - INPUT.LEFT, 0.0f, INPUT.UP - INPUT.DOWN};
    vec3 move_input = {0};
    glm_vec3_scale(move_input, camera_speed * (float)delta_time, move_input);
    glm_translate(debug_camera.transform, move_input);
}

//debug_camera_draw();

//debug_camera_delete();

#endif //SUPERMARIO_DEBUG_CAMERA_H
