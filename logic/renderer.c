//
// Created by samue on 25/03/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "renderer.h"
#include "main.h"

void handleTerminalCheckingAndResizing(Point terminalSize);

void render(double t_delta) {
    Point terminalSize = getTerminalSize();
    handleTerminalCheckingAndResizing(terminalSize);


}

void setTerminalBufferSize(Point newTerminalSize) {

}

void setTerminalSize(unsigned int width, unsigned int height) {
    //printf("\e[8;50;150t");

    // Can't find how to do this at the moment.

    // printf("hihi");
    // system("mode con:cols=10 lines=20");
}

void handleTerminalCheckingAndResizing(Point terminalSize) {
    static Point previousTerminalSize;
    if (comparePoint(previousTerminalSize, terminalSize) == 0) {
        setTerminalBufferSize(terminalSize);
        previousTerminalSize = terminalSize;
    }
}
