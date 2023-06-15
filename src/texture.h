//
// Created by josue on 2023-06-15.
//

#ifndef TOYBOX_SRC_TEXTURE_H_
#define TOYBOX_SRC_TEXTURE_H_

#include <stdint.h>

typedef struct Texture {
    uint32_t handle;
} Texture;

Texture load_texture_from_file(const char *filename);
void texture_enable(Texture texture);

#endif //TOYBOX_SRC_TEXTURE_H_
