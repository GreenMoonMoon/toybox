//
// Created by josue on 2023-06-16.
//

#include "image.h"
#include <string.h>
#include <assert.h>
#include "memory.h"
#include "stb_image.h"

void image_load_png8_file(Image *image, const char *filename) {
    int32_t x;
    int32_t y;
    int32_t n;

    uint8_t *data = stbi_load(filename, &x, &y, &n, 4); // Always return RGBA
    if (data != NULL){
        image->size = x * y * n;
        image->buffer = MALLOC(x * y);
        assert(image->buffer == NULL);
        MEMCPY(image->buffer, image->size, data, image->size);
    }
    stbi_image_free(data);
}

void image_delete(Image image) {
    if (image.buffer) FREE(image.buffer);
}

size_t read_png_file(const char *filename, uint8_t **buffer, int32_t *width, int32_t *height) {
    int32_t x, y, n;
    size_t buffer_size = 0;
    uint8_t *data = stbi_load(filename, &x, &y, &n, 4);
    if (data != NULL){
        buffer_size = x * y * 4; // width * height * channel
        *buffer = MALLOC(buffer_size);
        MEMCPY(*buffer, buffer_size, data, buffer_size);
    } else {
        perror("Error while loading texture");
        return 0;
    }
    stbi_image_free(data);

    *width = x;
    *height = y;
    return buffer_size;
}

size_t read_png_file_r(const char *filename, uint8_t **buffer) {
    int32_t x, y, n;
    size_t file_size = 0;
    uint8_t *data = stbi_load(filename, &x, &y, &n, 1);
    if (data != NULL){
        file_size = x * y;
        *buffer = MALLOC(x * y);
        MEMCPY(*buffer, file_size, data, file_size);
    }
    stbi_image_free(data);

    return file_size;
}