//
// Created by josue on 2023-01-29.
//

#ifndef SUPERMARIO_CAMERA_H
#define SUPERMARIO_CAMERA_H

#include "cglm/cglm.h"

typedef struct Camera {
    mat4 transform;
    mat4 projection;
} Camera;

Camera create_perspective_camera(float aspect_ratio);

#endif //SUPERMARIO_CAMERA_H
