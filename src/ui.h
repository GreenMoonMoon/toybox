//
// Created by josue on 2023-06-20.
//

#ifndef TOYBOX_SRC_UI_H_
#define TOYBOX_SRC_UI_H_

#include "viewport.h"
#include "SDL.h"

enum nk_anti_aliasing;
struct nk_context;
struct nk_font_atlas;
struct Viewport;

struct nk_context* ui_init(struct Viewport *viewport);
void ui_load_fonts(struct nk_context *ctx, struct nk_font_atlas *atlas);
int ui_handle_event(SDL_Event *event);
void ui_draw(enum nk_anti_aliasing AA, int max_vertex_buffer, int max_element_buffer);
void ui_delete(void);
void ui_device_delete(void);
void ui_device_create(void);
void ui_draw_demo(struct nk_context *context);

#endif //TOYBOX_SRC_UI_H_
