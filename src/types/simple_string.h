//
// Created by josue on 2023-02-09.
//

#ifndef SUPERMARIO_SIMPLE_STRING_H
#define SUPERMARIO_SIMPLE_STRING_H

#include "stdbool.h"

#ifndef STRING_ALLOC_CHUNK_SIZE
#define STRING_ALLOC_CHUNK_SIZE 512
#endif //DEFAULT_STRING_ALLOC_CHUNK_SIZE

#ifndef STRING_EXPAND_ATTEMPT_LIMIT
#define STRING_EXPAND_ATTEMPT_LIMIT 2
#endif //DEFAULT_STRING_EXPAND_TRY_LIMIT

/// Represent the buffer for a collection of string
typedef struct String {
    char *buffer;
    size_t capacity;
    size_t fill;
} String;

/// Represent null character terminated section of a String.
typedef struct StringView {
    String *string;
    size_t offset;
} StringView;

/// Free a String allocated memory.
/// \param string
void free_string_buffer(String *string);

/// Allocate a String with at least the requested initial memory. Memory is allocated in chunk of
///  DEFAULT_STRING_ALLOC_CHUNK_SIZE, which can be redefined if needed.
/// \param string
/// \param capacity Initial requested space, allocated memory is large enough to accommodate it.
/// \return Return false if the allocation failed.
bool allocate_string_buffer(String *string, size_t capacity);

/// Expand a String's allocated memory.
/// \param string
/// \return Return false if the reallocation failed.
bool expand_string_buffer(String *string);

/// Append a array of char at the end of the String.
/// \param str char pointer to the string data
/// \param length number of character contained in the string
/// \param string
/// \return A StringView object
StringView append_string(const char *str, size_t length, String *string);

/// Retrieves the char pointer of the passed StringView
/// \param string_view
/// \return
const char* get_char_array(StringView string_view);

#endif //SUPERMARIO_SIMPLE_STRING_H