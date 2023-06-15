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

/// Create a perspective camera
/// \param aspect_ratio Viewport aspect ratio
/// \param position Camera position
/// \param fov Field of view
/// \param near Near clip plane
/// \param far Far clip plane
/// \return struct Camera
Camera create_perspective_camera(float aspect_ratio, vec3 position, float fov, float near, float far);

#endif //SUPERMARIO_CAMERA_H
