//
// Created by Samuel Barkley on 26/03/2023.
//

#ifndef TOWEROFHANOI_GAME_H
#define TOWEROFHANOI_GAME_H

#include "StackNode.h"

typedef struct {
    long long time;
    node_t * pegs[3];
    short hoveredPegPos;
    int selectedRing;
    short height;
} Game;

short compareGame(Game a, Game b);
short getNumberLength(unsigned int number);
char * getNumberCharArray(unsigned int number);
char * generateRing(int size);
Game getInitGame(short height);
void copy_game(Game * src, Game * dest);

#endif //TOWEROFHANOI_GAME_H
