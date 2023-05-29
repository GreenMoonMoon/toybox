//
// Created by josue on 2023-02-03.
//

#ifndef SUPERMARIO_POOL_H
#define SUPERMARIO_POOL_H

#include <stdint.h>
#include <stdbool.h>

typedef struct Pool {
    uint8_t *data;
    size_t data_size;
    size_t capacity;
    size_t count;
} Pool;

bool allocate_list(Pool *pool, size_t capacity, size_t size);

void free_list(Pool *pool);

size_t get_next_index(Pool *pool);

size_t get_new_array_index(Pool *pool, size_t count);

char *get_element_at(size_t index);

#endif //SUPERMARIO_POOL_H
