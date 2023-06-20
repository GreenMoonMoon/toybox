//
// Created by josue on 2023-06-20.
//

#include "ui.h"
#include "memory.h"
#define NK_IMPLEMENTATION
#include "nuklear.h"

void ui_init(Viewport *viewport) {
    struct nk_context ctx;
    size_t memory_size = 0;
    void *memory = CALLOC(1, memory_size);
//    nk_init_fixed(&ctx, memory, memory_size, );
}
