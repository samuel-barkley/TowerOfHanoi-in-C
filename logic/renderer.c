//
// Created by samue on 25/03/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "renderer.h"
#include "main.h"


/*struct SMALL_RECT {
    short Left;
    short Top;
    short Right;
    short Bottom;
};*/

void render(double t_delta) {
    static unsigned int terminalWidth = 300;
    static unsigned int terminalHeight = 300;
    // setTerminalSize(terminalWidth, terminalHeight);

    // clearTerminal();    // TODO: This will not work properly. This will flicker. make a double buffer system.
    // printf("Update, %f\n", t_delta);
}

void setTerminalSize(unsigned int width, unsigned int height) {
    //printf("\e[8;50;150t");
    printf("hihi");
    system("mode con:cols=10 lines=20");
}
