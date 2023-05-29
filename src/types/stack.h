//
// Created by josue on 2023-02-01.
//

#ifndef SUPERMARIO_STACK_H
#define SUPERMARIO_STACK_H

#include <stdbool.h>
#include <stdint.h>

#define INTEGER_STACK_SIZE 32
#define INTEGER_STACK_EMPTY INT_MIN

typedef struct IntegerStack {
    unsigned head;
    int stack[INTEGER_STACK_SIZE];
} IntegerStack;

bool push(int value, IntegerStack *stack) {
    if (stack->head >= INTEGER_STACK_SIZE) return false;
    stack->stack[stack->head++] = value;
    return true;
}

int pop(IntegerStack *stack) {
    if (stack->head <= 1) return INTEGER_STACK_EMPTY;
    return stack->stack[--stack->head];
}

#endif //SUPERMARIO_STACK_H
