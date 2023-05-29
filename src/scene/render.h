//
// Created by josue on 2023-01-23.
//

#include <stdio.h>
#include <stdbool.h>

#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include "camera.h"

#ifndef SUPERMARIO_RENDER_H
#define SUPERMARIO_RENDER_H

/// Main application window
/// \note there might be no need for a global window variable.
GLFWwindow *window;
double last_frame_time;

struct Shader;
struct Primitive;
struct Mesh;
struct Node;

/// Initialize GLFW and OpenGL
/// \return true if initialization was successful, false otherwise
bool init_render(int width, int height);

/// Terminate GLFW. This function must be called before exiting the application
void terminate_render(void);

void draw_primitive(struct Primitive primitive);

void draw_mesh(struct Mesh mesh);

void draw_node(struct Node node, Camera camera, struct Mesh *meshes, struct Shader *shader);

double get_delta_time();

inline void render_begin(void){
    glClearColor(0.7f, 0.9f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

inline void render_end(void){
    glfwSwapBuffers(window);
}

#endif //SUPERMARIO_RENDER_H
