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
#include "memory.h"

size_t get_file_size(const char* file_path) {
    struct stat file_status;
    if(stat(file_path, &file_status) < 0) return -1;

    return file_status.st_size;
}

size_t read_file(const char* filename, char **buffer) {
    size_t file_size = get_file_size(filename);

    FILE *file;
    fopen_s(&file, filename, "r");
    if(!file) return 0;

    *buffer = (char*)MALLOC(file_size + 1);
    if(!(*buffer)) return 0;

    size_t readLength = fread_s((*buffer), file_size + 1, sizeof(char), file_size, file);
    (*buffer)[readLength] = '\0';

    fclose(file);
    return file_size + 1;
}

size_t read_png_file(const char *filename, uint8_t **buffer) {
    int32_t x, y, n;
    size_t file_size = 0;
    uint8_t *data = stbi_load(filename, &x, &y, &n, 1);
    if (data != NULL){
        file_size = x * y;
        *buffer = MALLOC(x * y);
        memcpy_s(*buffer, file_size, data, file_size);
    }
    stbi_image_free(data);

    return file_size;
}
