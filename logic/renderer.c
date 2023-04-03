//
// Created by samue on 25/03/2023.
// Block elements Unicode https://symbl.cc/en/unicode/blocks/block-elements/
//

#include <stdio.h>
#include <string.h>
#include "renderer.h"
#include "main.h"

void handleTerminalCheckingAndResizing(Point terminalSize);
void updateSelectedRing(Game game);
void setCursorToPos(Point pos);
void updateScore(Game game);

Point scoreBasePos = {00, 0};
Point centralPegBasePos = {0, 0};

void render(double t_delta, Game * game) {
    Point terminalSize = getTerminalSize();
    handleTerminalCheckingAndResizing(terminalSize);

    static Game previousGameState;
    handleGameUpdating(game, previousGameState);

    previousGameState = *game;

}

void updateElementBasePositions(Point newSize) {
    scoreBasePos.x = newSize.x / 2;
    scoreBasePos.y = 0;

    centralPegBasePos.x = newSize.x / 2;
    centralPegBasePos.y = newSize.y - 1;
}

void setTerminalSize(unsigned int width, unsigned int height) {
    // TODO: Probably should be deleted, windows terminal doesn't support it => all windows users => not cross platform enough.
    //printf("\e[8;50;150t");

    // Can't find how to do this at the moment.

    // printf("hihi");
    // system("mode con:cols=10 lines=20");
}

void handleTerminalCheckingAndResizing(Point terminalSize) {
    static Point previousTerminalSize;
    if (comparePoint(previousTerminalSize, terminalSize) == 0) {
        updateElementBasePositions(terminalSize);
        previousTerminalSize = terminalSize;
    }
}

void handleGameUpdating(Game * game, Game previousGameState) {
    if (compareGame(*game, previousGameState) == 1) {
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
        updateScore(*game);
    }
}

void updateSelectedRing(Game game) {
    // TODO: Remove the selected ring from the peg and hold it at the top.
    setCursorToPos(centralPegBasePos);
}

void updateScore(Game game) {
    // printf("updating score logic has been called.\r\n");
    char scoreToPrint[11];
    memset(scoreToPrint, '\0', sizeof(scoreToPrint));

    char * numberCharArray = getNumberCharArray(game.score);
    short stringLength = (short) strlen(numberCharArray);

    strncpy(scoreToPrint, numberCharArray, stringLength);

    Point adjustedPos;
    adjustedPos.x = scoreBasePos.x - ((int) strnlen(scoreToPrint, 11));

    setCursorToPos(adjustedPos);

    printf("Score: %s", scoreToPrint);
}

void setCursorToPos(Point pos) {
    printf("\033[%d;%dH" , pos.y, pos.x);
    // printf("set the cursor pos\r\n");
}

void printThing() {
    printf(" %s", right_half_block);
    printf("%s", full_block);
    printf("%s\r\n", left_half_block);

    printf(" %s", full_block);
    printf("%s", full_block);
    printf("%s\r\n", full_block);

    printf("%s", right_half_block);
    printf("%s", full_block);
    printf("%s", full_block);
    printf("%s", full_block);
    printf("%s\r\n", left_half_block);
}
