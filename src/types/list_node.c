//
// Created by josue on 2023-01-31.
//

#include "list_node.h"

#include <stdlib.h>

void allocate_list_node_pool(ListNode **list_node_pool, size_t count) {
    *list_node_pool = calloc(count, sizeof(ListNode));

    //Set all nodes in the free list;
    for (int i = 0; i < count; i++) {
        ListNode *current_node = &(*list_node_pool)[i];
        size_t next_i = (i + 1) % count;
        ListNode *next_node = &(*list_node_pool)[next_i];

        current_node->head = next_node;
        next_node->tail = current_node;
    }
}

void free_list_node_pool(ListNode *list_node_pool) {
    free(list_node_pool);
}

ListNode *get_available_node(ListNode *unused_list_nodes) {
    if (unused_list_nodes == NULL) return NULL;

    ListNode *node = unused_list_nodes->tail;

    // Close the link cycle
    unused_list_nodes->tail = node->tail;
    node->tail = unused_list_nodes;

    node->tail = NULL;
    node->head = NULL;

    return node;
}

void remove_node(ListNode *node, ListNode *unused_nodes) {
    if (unused_nodes == NULL){
        unused_nodes = node;
        unused_nodes->tail = node;
        unused_nodes->head = node;
    } else {
        node->tail = unused_nodes->tail;
        node->head = unused_nodes;
        unused_nodes->tail = node;
        node->tail->head = node;
    }
}
