//
// Created by josue on 2022-12-13.
//

#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

size_t get_file_size(const char* file_path) {
    struct stat file_status;
    if(stat(file_path, &file_status) < 0) return -1;

    return file_status.st_size;
}

size_t read_file(const char* filename, char **buffer) {
    size_t file_size = get_file_size(filename);

    FILE *file;
//    fopen(file, filename, "r");
    file = fopen(filename, "r");
    if(!file) return 0;

    *buffer = (char*)malloc(file_size + 1);
    if(!(*buffer)) return 0;

    size_t read_length = fread((*buffer), 1, file_size, file);
    (*buffer)[read_length] = '\0';
    if (ferror(file)) fprintf(stderr, "ERROR FILE READ\n");

    fclose(file);
    return file_size + 1;
}

size_t read_png_file(const char *filename, uint8_t **buffer, int32_t *width, int32_t *height) {
    int32_t x, y, n;
    size_t buffer_size = 0;
    uint8_t *data = stbi_load(filename, &x, &y, &n, 4);
    if (data != NULL){
        buffer_size = x * y * 4; // width * height * channel
        *buffer = malloc(buffer_size);
        memcpy(*buffer, buffer_size, data, buffer_size);
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
        *buffer = malloc(x * y);
        memcpy(*buffer, file_size, data, file_size);
    }
    stbi_image_free(data);

    return file_size;
}
