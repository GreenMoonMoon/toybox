//
// Created by josue on 2023-01-27.
//

#include "inputs.h"

void key_callback(GLFWwindow *current_window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(current_window, GL_TRUE);

    float value = action != GLFW_RELEASE ? 1.0f : 0.0f;
    switch (key) {
        case GLFW_KEY_W:
            INPUT.UP = value;
            break;
        case GLFW_KEY_A:
            INPUT.LEFT = value;
            break;
        case GLFW_KEY_S:
            INPUT.DOWN = value;
            break;
        case GLFW_KEY_D:
            INPUT.RIGHT = value;
            break;
        default:
            break;
    }
}

void joystick_callback(int jid, int event) {

}

bool enable_controller() {
    int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
    if (present) {
        printf("%s(%s)\n", glfwGetJoystickName(GLFW_JOYSTICK_1), glfwGetJoystickGUID(GLFW_JOYSTICK_1));

        return true;
    }
    return false;
}