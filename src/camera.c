//
// Created by josue on 2023-01-30.
//
#include "camera.h"

Camera create_perspective_camera(float aspect_ratio) {
    Camera camera;

    glm_mat4_identity(camera.transform);
    vec3 position = {0.0f, 0.0f, -8.0f};
    glm_translate(camera.transform, position);
    glm_perspective(75.0f, aspect_ratio, 0.1f, 100.0f, camera.projection);

    return camera;
}