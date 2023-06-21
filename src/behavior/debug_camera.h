//
// Created by josue on 2023-01-30.
//

#ifndef SUPERMARIO_DEBUG_CAMERA_H
#define SUPERMARIO_DEBUG_CAMERA_H

#include "camera.h"
#include "inputs.h"

#include "cglm/cglm.h"

Camera debug_camera;
//mat3 local_transform;
//mat3 rig_transform;
mat4 local;
mat4 rig;

const float camera_speed = 7.5f;
const float look_speed = 25.0f;

// Inputs
KeyBinding input_left = {PHYSICAL_KEY_A, 0};
KeyBinding input_right = {PHYSICAL_KEY_D, 0};
KeyBinding input_backward = {PHYSICAL_KEY_S, 0};
KeyBinding input_forward = {PHYSICAL_KEY_W, 0};
KeyBinding input_up = {PHYSICAL_KEY_SPACE, 0};
KeyBinding input_down = {PHYSICAL_KEY_LCTRL, 0};

void debug_camera_init(void) {
    debug_camera = create_perspective_camera(4.0f / 3.0f, (vec3) {0}, 1.5f, 0.1f, 100.0f);

    glm_mat4_identity(local);
    glm_translate_make(rig, (vec3){0.0f, -2.0f, -8.0f});
}

void debug_camera_update(double delta_time) {
    vec2 look_input;
    mouse_get_relative_motion(look_input);

//    glm_rotated_y(rig, look_input[0] * (float) delta_time * look_speed, rig);
    glm_rotate_y(rig, look_input[0] * (float) delta_time * look_speed, rig);
    glm_rotate_x(local, look_input[1] * (float) delta_time * look_speed, local);

    vec3 move_input = {
        key_binding_get_axis(&input_right, &input_left),
        key_binding_get_axis(&input_up, &input_down),
        key_binding_get_axis(&input_backward, &input_forward),
    };
    glm_vec3_normalize(move_input);
    glm_vec3_scale(move_input, (float) delta_time * camera_speed, move_input);
//    glm_mat4_mulv3(rig, move_input, 0.0f, move_input);
    glm_translate(rig, move_input);

    glm_mul(local, rig, debug_camera.transform);
}

//debug_camera_draw();

//debug_camera_delete();

#endif //SUPERMARIO_DEBUG_CAMERA_H
