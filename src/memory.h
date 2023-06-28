//
// Created by josue on 2023-05-29.
//

#ifndef TOYBOX_SRC_MEMORY_H_
#define TOYBOX_SRC_MEMORY_H_

#include <stdlib.h>

#define MALLOC malloc
#define CALLOC calloc
#define FREE free

#if MSVC
#define MEMCPY(D,DS,S,C) memcpy_s(D,DS,S,C)
#define FOPEN(F,P,M) fopen_S(&(F),P,M)
#define FREAD() fread_s()
#else
#define MEMCPY(D,DS,S,C) memcpy(D,S,C)
#define FOPEN(F,P,M) F = fopen(P,M)
#define FREAD() fread()
#endif

#endif //TOYBOX_SRC_MEMORY_H_
