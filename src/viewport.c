//
// Created by josue on 2023-05-29.
//

#include "viewport.h"
#include <stdio.h>
#include "glad/gl.h"
#include "SDL.h"
#include "memory.h"

struct Viewport {
  SDL_Window *window;
  SDL_GLContext context;
  bool closing;
};

void viewport_init(uint32_t width, uint32_t height, const char *name, struct Viewport **viewport) {
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

    *viewport = MALLOC(sizeof(Viewport));
    (*viewport)->window = window;
    (*viewport)->context = context;
    (*viewport)->closing = false;
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
