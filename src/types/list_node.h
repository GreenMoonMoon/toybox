//
// Created by josue on 2023-01-31.
//

#ifndef SUPERMARIO_LIST_NODE_H
#define SUPERMARIO_LIST_NODE_H

typedef struct ListNode {
    struct ListNode *head;
    struct ListNode *tail;
} ListNode;

void allocate_list_node_pool(ListNode **list_node_pool, size_t count);

void free_list_node_pool(ListNode *list_node_pool);

ListNode *get_available_node(ListNode *unused_list_nodes);

#endif //SUPERMARIO_LIST_NODE_H
