//
// Created by Samuel Barkley on 26/03/2023.
//

#ifndef TOWEROFHANOI_GAME_H
#define TOWEROFHANOI_GAME_H

#include "StackNode.h"

typedef struct {
    unsigned int score;
    node_t * pegs[3];
} Game;
#endif //TOWEROFHANOI_GAME_H
