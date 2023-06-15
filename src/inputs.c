//
// Created by josue on 2023-01-27.
//

#include "inputs.h"
#include "SDL.h"

float get_horizontal_input_axis() {
    const uint8_t *state = SDL_GetKeyboardState(NULL);
    return (float)state[SDL_SCANCODE_A] - (float)state[SDL_SCANCODE_D];
}

float get_vertical_input_axis() {
    const uint8_t *state = SDL_GetKeyboardState(NULL);
    return (float)state[SDL_SCANCODE_W] - (float)state[SDL_SCANCODE_S];
}