//
// Created by josue on 2023-01-31.
//

#ifndef SUPERMARIO_MAP_H
#define SUPERMARIO_MAP_H

typedef struct PointerMap {
    void *data;
    size_t element_size;
    size_t element_count;
} PointerMap;

unsigned hash_str(const char *string, unsigned table_size);

#endif //SUPERMARIO_MAP_H
