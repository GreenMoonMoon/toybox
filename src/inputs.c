//
// Created by josue on 2023-01-27.
//

#include "inputs.h"
#include "SDL.h"

float input_get_horizontal_axis() {
    const uint8_t *state = SDL_GetKeyboardState(NULL);
    return (float)state[SDL_SCANCODE_D] - (float)state[SDL_SCANCODE_A];
}

float input_get_vertical_axis() {
    const uint8_t *state = SDL_GetKeyboardState(NULL);
    return (float)state[SDL_SCANCODE_W] - (float)state[SDL_SCANCODE_S];
}