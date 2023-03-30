//
// Created by samue on 29/03/2023.
//

#ifndef TOWEROFHANOI_TERMINALHANDLER_H
#define TOWEROFHANOI_TERMINALHANDLER_H

#include "conio.h"

void initTerminal();

/// \param keepPlaying
/// \param pressedKeys  This is the out param. The currently pressed keys will be added to this char array. (as long as it doesn't exceed the array buffer size.)
void getDownKeys(short *keepPlaying, char * pressedKeys);
void clearTerminal();

#endif //TOWEROFHANOI_TERMINALHANDLER_H
