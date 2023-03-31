//
// Created by samue on 25/03/2023.
//

#ifndef TOWEROFHANOI_RENDERER_H
#define TOWEROFHANOI_RENDERER_H

#include "structs/DtosHelper.h"

void render(double t_delta);
void setTerminalSize(unsigned int width, unsigned int height);
void setTerminalBufferSize(Point newTerminalSize);
#endif //TOWEROFHANOI_RENDERER_H
