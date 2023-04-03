//
// Created by samue on 29/03/2023.
//

#ifndef TOWEROFHANOI_TERMINALHANDLER_H
#define TOWEROFHANOI_TERMINALHANDLER_H

#include "termios.h"
#include "../../structs/DtosHelper.h"

void initTerminal();
char * getDownKeys(short *keepPlaying, char *pressedKeys);
void clearTerminal();
Point getTerminalSize();

#endif //TOWEROFHANOI_TERMINALHANDLER_H
