//
// Created by josue on 2023-01-30.
//
#include "camera.h"

Camera camera_create_perspective(float aspect_ratio, vec3 position, float fov, float near, float far) {
    Camera camera;

    glm_mat4_identity(camera.transform);
    glm_translate(camera.transform, position);
    glm_perspective(fov, aspect_ratio, near, far, camera.projection);

    return camera;
}