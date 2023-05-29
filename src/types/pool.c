//
// Created by josue on 2023-02-03.
//

#include "pool.h"
#include <stdlib.h>

bool allocate_list(Pool *pool, size_t capacity, size_t size) {
    pool->data = malloc(capacity * size);
    if(pool->data == NULL) return false;

    pool->capacity = capacity;
    pool->data_size = size;
    pool->count = 0;

    return true;
}

void free_list(Pool *pool) {
    free(pool->data);
    pool->data = NULL;
    pool->count = pool->data_size = pool->capacity = 0;
}

void expand_list_allocation(Pool *pool){
    realloc(pool->data, 2 * pool->capacity * pool->data_size);
    pool->capacity *= 2;
}

size_t get_next_index(Pool *pool) {
    if(pool->count == pool->capacity){
        expand_list_allocation(pool);
    }
    return pool->count++;
}

size_t get_new_array_index(Pool *list, size_t count){
    if(list->element_count + count >= list->element_capacity){
        expand_list_allocation(list);
    }
    void *array = &list->pool[list->element_count * list->element_size];
    list->element_count += count;
    return array;
}

char *get_element_at(size_t index, Pool *list) {
    if(index > )
    return
}
