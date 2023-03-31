//
// Created by Samuel Barkley on 26/03/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "../main.h"

short comparePeg(node_t * a_peg, node_t * b_peg);

short compareGame(Game a, Game b) {
    if (a.hoveredPegPos != b.hoveredPegPos) {
        return 0;
    }

    if (a.selectedRing != b.selectedRing) {
        return 0;
    }

    if (a.score != b.score) {
        return 0;
    }

    for (unsigned long long i = 0; i < sizeof(a.pegs)/sizeof(a.pegs[0]); i++) {
        if (comparePeg(a.pegs[i], b.pegs[i]) == 0) {
            return 0;
        }
    }

    return 1;
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
    short numberOfChars = getNumberLength(number);
    int i;
    char * numberArray = calloc(numberOfChars, sizeof(char));
    for (i = numberOfChars-1; i>=0; --i, number /= 10) {
        numberArray[i] = (number % 10) + '0';
    }
    return numberArray;
}
