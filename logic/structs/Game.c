//
// Created by Samuel Barkley on 26/03/2023.
//

#include <stdio.h>
#define _OPEN_SYS_ITOA_EXT
#include <stdlib.h>
#include <string.h>
#include "Game.h"
#include "../main.h"

short comparePeg(node_t * a_peg, node_t * b_peg);
void addRingPart(char ** ringString, char * blockToAdd);

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

    if (a.score != b.score) {
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

char * generateRing(int size) {
    char * ringString = malloc(size * 4);   // * 4 for unicode characters

    if (size == 1) {
        addRingPart(&ringString, full_block);
    }

    addRingPart(&ringString, right_half_block);
    for (int i = 1; i < size - 1; i++) {
        addRingPart(&ringString, full_block);
    }
    addRingPart(&ringString, left_half_block);

    return ringString;
}

void addRingPart(char ** ringString, char * blockToAdd) {
    for (short i = 0; i < (short) strlen(blockToAdd); i++) {
        *ringString[i] = blockToAdd[i];
    }
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
    itoa(number, numberArray, 10); // check how unsigned ints convert to signed ints
    // short numberOfChars = getNumberLength(number);
    // int i = 0;
    // int test = sizeof(char);
    // char * numberArray = calloc(numberOfChars, sizeof(char));
    // for (i = numberOfChars-1; i>=0; --i, number /= 10) {
    //     char hihi = (number % 10) + '0';
    //     numberArray[i] = (number % 10) + '0';
    // }
    return numberArray;
}
