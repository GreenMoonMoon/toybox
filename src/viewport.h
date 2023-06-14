//
// Created by josue on 2023-05-29.
//

#ifndef TOYBOX_SRC_VIEWPORT_H_
#define TOYBOX_SRC_VIEWPORT_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct Viewport Viewport;

void viewport_init(uint32_t width, uint32_t height, const char *name, Viewport **viewport);
void viewport_delete(Viewport *viewport);

bool viewport_is_closing(Viewport *viewport);
void viewport_close(Viewport *viewport);

void viewport_process_events(Viewport *viewport);
double viewport_get_delta_time(Viewport *viewport);
void viewport_clear();
void viewport_set_clear_color(float r, float g, float b, float a);
void viewport_swap_window(Viewport *viewport);

#endif //TOYBOX_SRC_VIEWPORT_H_
