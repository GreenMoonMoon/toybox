//
// Created by josue on 2023-02-09.
//

#include "simple_string.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void free_string_buffer(String *string) {
    free(string->buffer);
    string->buffer = NULL;
    string->capacity = 0;
    string->fill = 0;
}

bool allocate_string_buffer(String *string, size_t capacity) {
    size_t count_over = capacity % STRING_ALLOC_CHUNK_SIZE > 0 ? 1 : 0;
    size_t allocation_capacity = (capacity / STRING_ALLOC_CHUNK_SIZE + count_over) * STRING_ALLOC_CHUNK_SIZE;

    string->buffer = calloc(allocation_capacity, sizeof(char));
    if(string->buffer == NULL){
        fprintf(stderr, "GLTF: Out of memory");
        return false;
    }

    string->capacity = allocation_capacity;
    string->fill = 0;
    return true;
}

bool expand_string_buffer(String *string) {
    size_t next_capacity = (string->capacity + STRING_ALLOC_CHUNK_SIZE);
    char *next_buffer = realloc(string->buffer, next_capacity * sizeof(char));
    if(next_buffer == NULL){
        fprintf(stderr, "GLTF: Out of memory");
        free_string_buffer(string);
        return false;
    }

    string->buffer = next_buffer;
    string->capacity = next_capacity;
    return true;
}

StringView append_string(const char *str, size_t length, String *string) {
    for(int i = 0; string->fill + length >= string->capacity && i < STRING_EXPAND_ATTEMPT_LIMIT; i++) {
        expand_string_buffer(string);
    }

    uintptr_t string_offset = string->fill;

    memcpy_s(&string->buffer[string->fill], string->capacity, str, length);
    string->fill += length;
    if(string->buffer[string->fill] != '\0') string->buffer[string->fill] = '\0';
    string->fill++;

    return (StringView) {
            string,
            string_offset,
    };
}

const char* get_char_array(StringView string_view) {
    return &string_view.string->buffer[string_view.offset];
}