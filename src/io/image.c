//
// Created by josue on 2023-06-16.
//

#include "image.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "stb_image.h"

void image_load_png8_file(Image *image, const char *filename) {
    int32_t x;
    int32_t y;
    int32_t n;

    uint8_t *data = stbi_load(filename, &x, &y, &n, 4); // Always return RGBA
    if (data != NULL){
        image->size = x * y * n;
        image->buffer = malloc(x * y);
        assert(image->buffer == NULL);
        memcpy(image->buffer, image->size, data, image->size);
    }
    stbi_image_free(data);
}

void image_delete(Image image) {
    if (image.buffer) free(image.buffer);
}