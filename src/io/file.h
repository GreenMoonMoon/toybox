//
// Created by josue on 2022-12-13.
//

#ifndef VERTEX32_FILE_IO_H
#define VERTEX32_FILE_IO_H

/// Return the length of a file in bytes.
/// \param file_path
/// \return
size_t get_file_size(const char* file_path);

/// Read a file and return the its length
/// \param filename
/// \param buffer
/// \return
size_t read_file(const char* filename, char **buffer);

#endif //VERTEX32_FILE_IO_H
