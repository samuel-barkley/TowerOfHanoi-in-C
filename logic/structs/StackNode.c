//
// Created by samue on 25/03/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "StackNode.h"
#include "../Headers/main.h"

int pop(node_t ** head) {
    int retval = undefined;
    node_t * next_node = NULL;

    if (*head == NULL) {
        return undefined;
    }

    next_node = (*head)->next;
    retval = (*head)->value;
    free(*head);
    *head = next_node;

    return retval;
}

void push(node_t ** head, int value) {
    if ((*head)->value == -1) {
        (*head)->next = NULL;
    }

    node_t * new_node;
    new_node = (node_t *) malloc(sizeof(node_t));

    new_node->value = value;
    new_node->next = *head;
    *head = new_node;
}

unsigned int getNodeCountExclBase(node_t * head) {
    if (head == NULL || head->value == undefined) {
        return 0;
    }

    unsigned int nodeCount = 1;
    while (head->next->value != undefined) {
        nodeCount++;
        head = head->next;
    }

    return nodeCount;
}
