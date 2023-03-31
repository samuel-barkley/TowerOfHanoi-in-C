//
// Created by samue on 25/03/2023.
//

#ifndef TOWEROFHANOI_RENDERER_H
#define TOWEROFHANOI_RENDERER_H

#include "structs/DtosHelper.h"
#include "structs/Game.h"

void render(double t_delta, Game * game);
void setTerminalSize(unsigned int width, unsigned int height);
void handleGameUpdating(Game * game, Game previousGameState);
#endif //TOWEROFHANOI_RENDERER_H
