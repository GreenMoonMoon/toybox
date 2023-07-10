//
// Created by josue on 2023-01-27.
//

#ifndef TOYBOX_INPUTS_H
#define TOYBOX_INPUTS_H

#include <stdint.h>
#include <stdbool.h>
#include "keycodes.h"
#include "SDL.h"

typedef enum ButtonState {
  BUTTON_STATE_JUST_RELEASED,
  BUTTON_STATE_RELEASED,
  BUTTON_STATE_JUST_PRESSED,
  BUTTON_STATE_PRESSED,
} ButtonState;

typedef struct KeyBinding {
  PhysicalKey physical_key;
  uint8_t state;
} KeyBinding;

void init_keyboard_inputs(void);
void clean_keyboard_inputs(void);

int32_t key_binding_get_state(KeyBinding *binding);

float key_binding_get_axis(KeyBinding *negative, KeyBinding *positive);

void mouse_get_relative_motion(float *relative_motion);


#endif //TOYBOX_INPUTS_H
