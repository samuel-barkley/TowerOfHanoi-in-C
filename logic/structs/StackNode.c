//
// Created by samue on 25/03/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "StackNode.h"

int pop(node_t ** head) {
    int retval = -1;
    node_t * next_node = NULL;

    if (*head == NULL) {
        return -1;
    }

    next_node = (*head)->next;
    retval = (*head)->value;
    free(*head);
    *head = next_node;

    return retval;
}

void push(node_t ** head, int value) {
    node_t * new_node;
    new_node = (node_t *) malloc(sizeof(node_t));

    new_node->value = value;
    new_node->next = *head;
    *head = new_node;
}