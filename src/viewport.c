//
// Created by josue on 2023-05-29.
//

#include "viewport.h"
#include <stdio.h>
#include "glad/gl.h"
#include "debug.h"
#include "SDL.h"
#include "memory.h"

struct Viewport {
  SDL_Window *window;
  SDL_GLContext context;
  bool closing;
  uint64_t last_frame_time;
};

void viewport_init(struct Viewport **viewport, uint32_t width, uint32_t height, const char *name) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window *window = SDL_CreateWindow(name,
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          width,
                                          height,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    SDL_GLContext context = SDL_GL_CreateContext(window);


    // Check version
    int version = gladLoadGL((GLADloadfunc) SDL_GL_GetProcAddress);
    printf("GL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    SDL_GL_MakeCurrent(window, context);

#ifndef NDEBUG
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(print_graphic_error_callback, NULL);
#endif

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    *viewport = MALLOC(sizeof(Viewport));
    (*viewport)->window = window;
    (*viewport)->context = context;
    (*viewport)->closing = false;
    (*viewport)->last_frame_time = SDL_GetPerformanceCounter();
}

void viewport_delete(struct Viewport *viewport) {
    SDL_GL_DeleteContext(viewport->context);
    SDL_DestroyWindow(viewport->window);
    SDL_Quit();
}

bool viewport_is_closing(struct Viewport *viewport) {
    return viewport->closing;
}

void viewport_close(struct Viewport *viewport) {
    viewport->closing = true;
}

void viewport_process_events(Viewport *viewport) {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                viewport->closing = true;
                break;
            case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_ESCAPE) viewport->closing = true;
                break;
        }
    }
}

double viewport_get_delta_time(Viewport *viewport) {
    uint64_t current_frame_time = SDL_GetPerformanceCounter();
    double delta_time = (double)(current_frame_time - viewport->last_frame_time) / (double)SDL_GetPerformanceFrequency();
    viewport->last_frame_time = current_frame_time;
    return delta_time;
}

void viewport_start_frame(Viewport *viewport) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void set_clear_color(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void viewport_end_frame(Viewport *viewport) {
    SDL_GL_SwapWindow(viewport->window);
}

void viewport_capture_mouse(Viewport *viewport){
    SDL_SetRelativeMouseMode(SDL_TRUE);
}