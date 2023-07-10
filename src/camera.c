//
// Created by josue on 2023-01-30.
//
#include "camera.h"

Camera new_camera_perspective(float aspect_ratio, vec3 position, float fov, float near, float far) {
    Camera camera;

    glm_mat4_identity(camera.transform);
    glm_translate(camera.transform, position);
    glm_perspective(fov, aspect_ratio, near, far, camera.projection);

    return camera;
}

Camera new_orthographic_camera(float aspect_ratio, vec3 position, float width, float near, float far) {
    Camera camera;

    glm_mat4_identity(camera.transform);
    glm_translate(camera.transform, position);
    glm_ortho(-(width * 0.5f),
              width * 0.5f,
              -width * 0.5f * aspect_ratio,
              width * 0.5f * aspect_ratio,
              near,
              far,
              camera.projection);

    return camera;
}