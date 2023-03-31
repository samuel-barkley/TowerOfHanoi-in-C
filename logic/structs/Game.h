//
// Created by Samuel Barkley on 26/03/2023.
//

#ifndef TOWEROFHANOI_GAME_H
#define TOWEROFHANOI_GAME_H

#include "StackNode.h"

typedef struct {
    unsigned int score;
    node_t * pegs[3];
    short hoveredPegPos;
    int selectedRing;
} Game;

short compareGame(Game a, Game b);
short getNumberLength(unsigned int number);
char * getNumberCharArray(unsigned int number);

#endif //TOWEROFHANOI_GAME_H
