//
// Created by josue on 2023-01-31.
//
#include "map.h"

#include <string.h>

unsigned hash_str(const char *string, unsigned table_size) {
    size_t s = strnlen_s(string, 512);
    unsigned hash_value = 0;
    for (int i = 0; i < s; ++i) {
        hash_value += string[i];
        hash_value = hash_value * string[i];
    }
    return hash_value % table_size;
}

