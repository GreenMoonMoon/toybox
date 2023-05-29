//
// Created by josue on 2023-01-30.
//
#include "render.h"
#include "inputs.h"

#include "types/mesh.h"
#include "material.h"

bool init_render(int width, int height) {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "SuperMario", NULL, NULL);
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);
    glfwSetJoystickCallback(joystick_callback);

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        fprintf(stderr, "Failed to initialize OpenGL context");
        return false;
    }

    glEnable(GL_DEPTH_TEST);

    return true;
}

void terminate_render(void) {
    glfwTerminate();
}

void draw_primitive(Primitive primitive) {
    glBindVertexArray(primitive.vao);
    glDrawElements(primitive.mode, primitive.index_count, GL_UNSIGNED_INT, 0);
}

void draw_mesh(Mesh mesh) {
    for (size_t i = 0; i < mesh.primitive_count; i++) {
        draw_primitive(mesh.primitives[i]);
    }
}

void draw_node(Node node, Camera camera, Mesh *meshes, Shader *shaders){
    shader_use(shaders[node.shader_index]);

    material_set_mvp(shaders[node.shader_index], node.transform, camera.transform, camera.projection);
    material_set_light(shaders[node.shader_index], (vec3) {0.0f, 0.0f, -5.0f}, (vec3) {2.0f}, (vec3) {0.8f});
    material_set_normal_matrix(shaders[node.shader_index], node.normal_matrix);

    draw_mesh(meshes[node.mesh_index]);
}

double get_delta_time() {
    double current_time = glfwGetTime();
    double delta_time = current_time - last_frame_time;

    last_frame_time = current_time;
    return delta_time;
}
