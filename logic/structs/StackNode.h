//
// Created by samue on 25/03/2023.
//

#ifndef TOWEROFHANOI_STACKNODE_H
#define TOWEROFHANOI_STACKNODE_H
typedef struct node {
    int value;
    struct node * next;
} node_t;

int pop(node_t ** head);
void push(node_t ** head, int value);
unsigned int getNodeCountExclBase(node_t * head);

#endif //TOWEROFHANOI_STACKNODE_H
