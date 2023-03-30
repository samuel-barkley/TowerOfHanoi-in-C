//
// Created by samue on 29/03/2023.
//

#ifndef TOWEROFHANOI_TERMINALHANDLER_H
#define TOWEROFHANOI_TERMINALHANDLER_H

#include "termios.h"

void initTerminal();
char * getDownKeys(short *keepPlaying);
void clearTerminal();

#endif //TOWEROFHANOI_TERMINALHANDLER_H
