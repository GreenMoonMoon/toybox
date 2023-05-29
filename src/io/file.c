//
// Created by josue on 2022-12-13.
//

#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

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

    *buffer = (char*)malloc(file_size + 1);
    if(!(*buffer)) return 0;

    size_t readLength = fread_s((*buffer), file_size + 1, sizeof(char), file_size, file);
    (*buffer)[readLength] = '\0';

    fclose(file);
    return file_size + 1;
}
