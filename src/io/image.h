//
// Created by josue on 2023-06-16.
//

#ifndef TOYBOX_SRC_IO_IMAGE_H_
#define TOYBOX_SRC_IO_IMAGE_H_

#include "stdint.h"


typedef struct Image {
    int32_t width;
    int32_t height;
    int8_t channel;
    size_t size;
    uint8_t *buffer;
} Image;

void image_load_png8_file(Image *image, const char *filename);
void image_delete(Image image);

#endif //TOYBOX_SRC_IO_IMAGE_H_
