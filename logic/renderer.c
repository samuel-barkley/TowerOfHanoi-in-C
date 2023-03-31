//
// Created by samue on 25/03/2023.
//

#include <stdio.h>
#include <windows.h>
#include "renderer.h"
#include "main.h"

void handleTerminalCheckingAndResizing(Point terminalSize);
void updateSelectedRing(Game game);
void setCursorToPos(Point pos);

Point scoreBasePos = {0, 0};
Point centralPegBasePos = {0, 0};

void render(double t_delta, Game * game) {
    Point terminalSize = getTerminalSize();
    handleTerminalCheckingAndResizing(terminalSize);

    static Game previousGameState;
    handleGameUpdating(game, previousGameState);

    previousGameState = *game;
}

void setTerminalBufferSize(Point newTerminalSize) {
    // TODO: To be removed, don't think double buffer will work in terminal.
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

void handleGameUpdating(Game * game, Game previousGameState) {
    if (compareGame(*game, previousGameState) == 0) {
        return; // nothing changed
    }

    if (game->selectedRing != previousGameState.selectedRing) {
        updateSelectedRing(*game);
    }

    if (game->hoveredPegPos != previousGameState.hoveredPegPos) {
        // TODO: Move the arrow pointing to the hovered peg
        // TODO: If a ring is selected. Move the selected ring to hover above the proper ring.
    }

    if (game->score != previousGameState.score) {
        // TODO: Update the score counter.

        setCursorToPos(scoreBasePos);
        char * scoreToPrint = "          ";
        for (short i = 0; i < getNumberLength(game->score); i++) {

        }
        printf("%d", game->score);
        fflush(stdout);
    }
}

void updateSelectedRing(Game game) {
    // TODO: Remove the selected ring from the peg and hold it at the top.
    setCursorToPos(centralPegBasePos);
}

void setCursorToPos(Point pos) {
    printf("\033[%d;%dH" , pos.y, pos.x);
}
