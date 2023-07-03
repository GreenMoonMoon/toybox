//
// Created by josue on 2023-05-29.
//

#include "viewport.h"
#include <stdio.h>
#include "glad/gl.h"
#include "debug.h"
#include "SDL.h"

// NOTE: currently handling only one
static SDL_Window *window_handle;
static i32 window_width;
static i32 window_height;

struct Viewport {
  SDL_GLContext context;
  u64 last_frame_time;
  bool is_closing;
  bool is_main_viewport;
};

void init_sdl(const i32 width, const i32 height, const char *window_title) {
    SDL_Init(SDL_INIT_VIDEO);
    window_width = width;
    window_height = height;

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window_handle = SDL_CreateWindow(window_title,
                                     SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED,
                                     window_width,
                                     window_height,
                                     SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
}

void shutdown_sdl() {
    SDL_DestroyWindow(window_handle);
    SDL_Quit();
}

/// Create a new viewport and make its context current. If no window were created yet, a new
///  window will be created, the viewport width, height and name will be used for the window
///  dimension and title.
/// \param width viewport width
/// \param height viewport height
/// \param name viewport name
/// \return struct Viewport
Viewport *viewport_new(const i32 width, const i32 height, const char *name) {
    struct Viewport *viewport = malloc(sizeof(struct Viewport));
    // TODO: print error
    if(!viewport) return NULL;

    if (!window_handle) {
        init_sdl(width, height, name);
        viewport->is_main_viewport = true;
    }

    viewport->context = SDL_GL_CreateContext(window_handle);

    // Check version
    int version = gladLoadGL((GLADloadfunc) SDL_GL_GetProcAddress);
    assert(GLAD_VERSION_MAJOR(version) == 4);
    assert(GLAD_VERSION_MINOR(version) == 6);

    SDL_GL_MakeCurrent(window_handle, viewport->context);

#ifndef NDEBUG
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(print_graphic_error_callback, NULL);
#endif

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    viewport->is_closing = false;
    viewport->last_frame_time = SDL_GetPerformanceCounter();

    return viewport;
}

void viewport_delete(struct Viewport *viewport) {
    SDL_GL_DeleteContext(viewport->context);
    if(viewport->is_main_viewport) shutdown_sdl();
}

void *get_window_handle() {
    return window_handle;
}

bool viewport_should_close(struct Viewport *viewport) {
    return viewport->is_closing;
}

void viewport_set_is_closing(struct Viewport *viewport) {
    viewport->is_closing = true;
}

void viewport_process_events(Viewport *viewport) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:viewport->is_closing = true;
                break;
            case SDL_KEYUP:if (event.key.keysym.sym == SDLK_ESCAPE) viewport->is_closing = true;
                break;
        }
    }
}

double viewport_get_delta_time(Viewport *viewport) {
    uint64_t current_frame_time = SDL_GetPerformanceCounter();
    double
        delta_time = (double) (current_frame_time - viewport->last_frame_time) / (double) SDL_GetPerformanceFrequency();
    viewport->last_frame_time = current_frame_time;
    return delta_time;
}

void start_frame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void end_frame() {
    SDL_GL_SwapWindow(window_handle);
}

void set_clear_color(const float r, const float g, const float b, const float a) {
    glClearColor(r, g, b, a);
}

void set_mouse_mode(enum ViewportMouseMode mode) {
    switch (mode){
        case MOUSE_MODE_CAPTURED:
            SDL_SetRelativeMouseMode(SDL_TRUE);
            break;
        case MOUSE_MODE_FREE:
            SDL_SetRelativeMouseMode(SDL_FALSE);
            break;
    }
}
