//
// Created by josue on 2023-05-29.
//

#ifndef TOYBOX_SRC_VIEWPORT_H_
#define TOYBOX_SRC_VIEWPORT_H_

#include <stdbool.h>
#include <stdint.h>
#include "types.h"

typedef struct Viewport Viewport;

enum ViewportMouseMode {
  MOUSE_MODE_CAPTURED,
  MOUSE_MODE_FREE,
};

Viewport *viewport_new(const i32 width, const i32 height, const char *name);
void viewport_delete(Viewport *viewport);

bool viewport_should_close(Viewport *viewport);
void viewport_set_is_closing(struct Viewport *viewport);

void *get_window_handle();
void viewport_process_events(Viewport *viewport);
double viewport_get_delta_time(Viewport *viewport);
void start_frame();
void end_frame();
void set_clear_color(f32 r, f32 g, f32 b, f32 a);
void set_mouse_mode(enum ViewportMouseMode mode);

#endif //TOYBOX_SRC_VIEWPORT_H_
