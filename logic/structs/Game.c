//
// Created by Samuel Barkley on 26/03/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Game.h"
#include "../Headers/main.h"

short comparePeg(node_t * a_peg, node_t * b_peg);
node_t * copyList(node_t * head);

Game getInitGame(short height) {
    node_t *peg0 = (node_t *) malloc(sizeof(node_t));
    node_t *peg1 = (node_t *) malloc(sizeof(node_t));
    node_t *peg2 = (node_t *) malloc(sizeof(node_t));

    peg0->value = undefined;
    peg0->next = NULL;
    peg1->value = undefined;
    peg1->next = NULL;
    peg2->value = undefined;
    peg2->next = NULL;

    for (int i = 0; i < height; i++) {
        push(&peg0, height - i);
    }

    Game *game = (Game *) malloc(sizeof(Game));
    game->time = 0;
    game->pegs[0] = peg0;
    game->pegs[2] = peg1;
    game->pegs[1] = peg2;
    game->hoveredPegPos = 0;
    game->selectedRing = undefined;
    game->height = height;
    return *game;
}

/// \param a
/// \param b
/// \return will return 1 if the provided games are the same.
short compareGame(Game a, Game b) {
    if (a.hoveredPegPos != b.hoveredPegPos) {
        return 0;
    }

    if (a.selectedRing != b.selectedRing) {
        return 0;
    }

    if (a.time != b.time) {
        return 0;
    }

    // max loop size should be 3 (games with more pegs don't make sense.)
    for (short i = 0; i < (short) (sizeof(a.pegs)/ sizeof(a.pegs[0])); i++) {
        if (comparePeg(a.pegs[i], b.pegs[i]) == 0) {
            return 0;
        }
    }

    return 1;
}

node_t * copyList(node_t * src)
{
    if (src == NULL) {
        return NULL;
    }
    else {

        // Allocate the memory for new Node
        // in the heap and set its data
        node_t * newNode = (node_t*)malloc(sizeof(node_t));

        newNode->value = src->value;

        // Recursively set the next pointer of
        // the new Node by recurring for the
        // remaining nodes
        newNode->next = copyList(src->next);

        return newNode;
    }
}

void copy_game(Game * src, Game * dest) {
    dest->hoveredPegPos = src->hoveredPegPos;
    dest->time = src->time;
    dest->height = src->height;
    dest->selectedRing = src->selectedRing;

    dest->pegs[0] = copyList(src->pegs[0]);
    dest->pegs[1] = copyList(src->pegs[1]);
    dest->pegs[2] = copyList(src->pegs[2]);
}

short comparePeg(node_t * a_peg, node_t * b_peg) {
    while (1) {
        if (a_peg->value == undefined && b_peg->value == undefined) {
            return 1;
        }

        // Checking if both pegs are the same length
        if ((a_peg->value == undefined && b_peg->value != undefined) || (a_peg->value != undefined && b_peg->value == undefined)) {
            return 0;
        }

        if (a_peg->value != b_peg->value) {
            return 0;
        }

        a_peg = a_peg->next;
        b_peg = b_peg->next;
    }
}

short getNumberLength(unsigned int number) {
    short count = 0;

    if (number == 0) {
        return 1;
    }

    while (number != 0) {
        number /= 10;
        count++;
    }
    return count;
}

char * getNumberCharArray(unsigned int number) {
    char * numberArray = calloc(getNumberLength(number), sizeof(char) * getNumberLength(number) + 1);

    sprintf(numberArray, "%u", number);

    return numberArray;
}
