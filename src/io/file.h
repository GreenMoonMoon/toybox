//
// Created by josue on 2022-12-13.
//

#ifndef VERTEX32_FILE_IO_H
#define VERTEX32_FILE_IO_H

#include <stdint.h>
#include <stdlib.h>

/// Return the length of a file in bytes.
/// \param file_path
/// \return
size_t get_file_size(const char* file_path);

/// Read a file and return the its length
/// \param filename
/// \param buffer
/// \return
size_t read_file(const char* filename, char **buffer);

size_t read_png_file(const char* filename, uint8_t **buffer, int32_t *width, int32_t *height);

size_t read_png_file_r(const char* filename, uint8_t **buffer);

#endif //VERTEX32_FILE_IO_H
