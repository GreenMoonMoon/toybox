//
// Created by josue on 2023-06-13.
//

#ifndef TOYBOX_SRC_TYPES_ARRAY_2D_H_
#define TOYBOX_SRC_TYPES_ARRAY_2D_H_

#include "memory.h"

#define ALLOC_ARRAY_2D(type, width, height) MALLOC(width * height * sizeof(type))
#define FREE_ARRAY_2D(array) FREE(array)

#endif //TOYBOX_SRC_TYPES_ARRAY_2D_H_
