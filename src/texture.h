//
// Created by josue on 2023-06-15.
//

#ifndef TOYBOX_SRC_TEXTURE_H_
#define TOYBOX_SRC_TEXTURE_H_

#include <stdint.h>

typedef struct Texture {
    uint32_t texture_handle;
    uint32_t sampler_handle;
} Texture;

Texture load_texture_from_png(const char *filename);
void texture_unload(Texture texture);
void texture_enable(Texture texture, int32_t unit);

#endif //TOYBOX_SRC_TEXTURE_H_
