//
// Created by josue on 2022-12-13.
//

#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

size_t get_file_size(const char* file_path) {
    struct stat file_status;
    if(stat(file_path, &file_status) < 0) return -1;

    return file_status.st_size;
}

size_t read_file(const char* filename, char **buffer) {
    size_t file_size = get_file_size(filename);

    FILE *file;
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
