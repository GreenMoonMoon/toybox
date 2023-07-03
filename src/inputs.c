//
// Created by josue on 2023-01-27.
//

#include "inputs.h"

// SDL keyboard state. Element are access via key scancode (Based on USB usage page standard)
static const uint8_t *keyboard_state;

void init_keyboard_inputs(void){
    keyboard_state = SDL_GetKeyboardState(NULL);
}

int32_t key_binding_get_state(KeyBinding *binding){
    if(keyboard_state[binding->physical_key] == 0) binding->state = binding->state == BUTTON_STATE_JUST_RELEASED ? BUTTON_STATE_RELEASED : BUTTON_STATE_JUST_RELEASED;
    else binding->state = binding->state == BUTTON_STATE_JUST_PRESSED ? BUTTON_STATE_PRESSED : BUTTON_STATE_JUST_PRESSED;

    return binding->state;
}

float key_binding_get_axis(KeyBinding *negative, KeyBinding *positive){
    float result = 0.0f;
    if(key_binding_get_state(negative) >= BUTTON_STATE_JUST_PRESSED) result -= 1.0f;
    if(key_binding_get_state(positive) >= BUTTON_STATE_JUST_PRESSED) result += 1.0f;
    return result;
}

void mouse_get_relative_motion(float *relative_motion) {
    // FIXME: remove hardcoded viewport resolution.
    int32_t x;
    int32_t y;
    SDL_GetRelativeMouseState(&x, &y);
    relative_motion[0] = (float)x/800.0f;
    relative_motion[1] = (float)y/600.0f;
}