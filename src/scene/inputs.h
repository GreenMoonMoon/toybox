//
// Created by josue on 2023-01-27.
//

#ifndef SUPERMARIO_INPUTS_H
#define SUPERMARIO_INPUTS_H

#include "GLFW/glfw3.h"

#include <stdio.h>
#include <stdbool.h>

struct Input {
    float UP;
    float DOWN;
    float LEFT;
    float RIGHT;
} INPUT;

struct GLFWwindow;

void key_callback(GLFWwindow *current_window, int key, int scancode, int action, int mode);

void joystick_callback(int jid, int event);

bool enable_controller();

#endif //SUPERMARIO_INPUTS_H
