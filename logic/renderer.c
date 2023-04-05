//
// Created by samue on 25/03/2023.
// Block elements Unicode https://symbl.cc/en/unicode/blocks/block-elements/
//

#include <stdio.h>
#include <string.h>
#include <iconv.h>  // might not be supported on windows. if not, create a OS specific unicode printer.
#include <stdlib.h>
#include "renderer.h"
#include "main.h"

void handleTerminalCheckingAndResizing(Game game, Point terminalSize);

void updateSelectedRing(Game game);

void setCursorToPos(Point pos);

void updateScore(Game game);

void refreshScreen(Game game);

void updatePegSelector(Game game);

void clearPegSelectors(short height);

void printThing();

void printBlocksAtPos(short size, Point basePos);

void drawPeg(Game game, short pegNumber);

void drawAllPegs(Game game);

Point scoreBasePos = {0, 0};
Point centralPegBasePos = {0, 0};
unsigned int pegDistance = 0;

void render(double t_delta, Game *game) {
    Point terminalSize = getTerminalSize();
    handleTerminalCheckingAndResizing(*game, terminalSize);

    static short shouldInit = 1;
    if (shouldInit == 1) {
        clearTerminal();
        pegDistance = game->height + 10;
        updateSelectedRing(*game);
        updateScore(*game);
        updatePegSelector(*game);
        drawAllPegs(*game);
        shouldInit = 0;
    }

    static Game previousGameState;
    handleGameUpdating(game, previousGameState);

    previousGameState = *game;

}

void updateElementBasePositions(Point newSize) {
    scoreBasePos.x = newSize.x / 2;
    scoreBasePos.y = 0;

    centralPegBasePos.x = newSize.x / 2;
    centralPegBasePos.y = newSize.y;
}

void setTerminalSize(unsigned int width, unsigned int height) {
    // TODO: Probably should be deleted, windows terminal doesn't support it => all windows users => not cross platform enough.
    //printf("\e[8;50;150t");

    // Can't find how to do this at the moment.

    // printf("hihi");
    // system("mode con:cols=10 lines=20");
}

void handleTerminalCheckingAndResizing(Game game, Point terminalSize) {
    static Point previousTerminalSize;
    if (comparePoint(previousTerminalSize, terminalSize) == 0) {
        updateElementBasePositions(terminalSize);
        refreshScreen(game);
        previousTerminalSize = terminalSize;
    }
}

void handleGameUpdating(Game *game, Game previousGameState) {
    if (compareGame(*game, previousGameState) == 1) {
        return; // nothing changed
    }

    if (game->selectedRing != previousGameState.selectedRing) {
        updateSelectedRing(*game);
    }

    if (game->hoveredPegPos != previousGameState.hoveredPegPos) {
        updatePegSelector(*game);
    }

    if (game->score != previousGameState.score) {
        updateScore(*game);
    }
}

void updateSelectedRing(Game game) {
    // TODO: Remove the selected ring from the peg and hold it at the top.


}

void updateScore(Game game) {
    char scoreToPrint[11];
    memset(scoreToPrint, '\0', sizeof(scoreToPrint));

    char *numberCharArray = getNumberCharArray(game.score);
    short stringLength = (short) strlen(numberCharArray);

    strncpy(scoreToPrint, numberCharArray, stringLength);

    Point adjustedPos;
    adjustedPos.x = scoreBasePos.x - ((int) strnlen(scoreToPrint, 11));
    adjustedPos.y = scoreBasePos.y;

    setCursorToPos(adjustedPos);

    printf("Score: %s", scoreToPrint);
    fflush(stdout);
}

void updatePegSelector(Game game) {
    clearPegSelectors(game.height);


    short multiplier = -1;
    switch (game.hoveredPegPos) {
        case 0:
            multiplier = -1;
            break;
        case 1:
            multiplier = 0;
            break;
        case 2:
            multiplier = 1;
            break;
    }

    Point adjustedPos;
    adjustedPos.x = centralPegBasePos.x + pegDistance * multiplier;
    adjustedPos.y = centralPegBasePos.y + 1;
    setCursorToPos(adjustedPos);

    printf("%s", selector_arrow);

    fflush(stdout);
}

void clearPegSelectors(short height) {
    Point leftPegBase;

    leftPegBase.x = centralPegBasePos.x - (int) pegDistance;
    leftPegBase.y = centralPegBasePos.y + 1;

    Point middlePegBase;
    middlePegBase.x = centralPegBasePos.x;
    middlePegBase.y = centralPegBasePos.y + 1;

    Point rightPegBase;
    rightPegBase.x = centralPegBasePos.x + (int) pegDistance;
    rightPegBase.y = centralPegBasePos.y + 1;

    setCursorToPos(leftPegBase);
    printf("%s", space_char);
    setCursorToPos(middlePegBase);
    printf("%s", space_char);
    setCursorToPos(rightPegBase);
    printf("%s", space_char);
}

void setCursorToPos(Point pos) {
    printf("\033[%d;%dH", pos.y, pos.x);
}

void refreshScreen(Game game) {
    clearTerminal();
    updateScore(game);
}

void drawAllPegs(Game game) {
    drawPeg(game, 0);
    // drawPeg(game, 1);
    // drawPeg(game, 2);
}

void drawPeg(Game game, short pegNumber) {
    Game game_copy;
    copy_game(&game, &game_copy);
    int pegHeight = 0;
    while (1) {
        if (game_copy.pegs[pegNumber]->value == -1) {
            break;
        }
        pop(&game_copy.pegs[pegNumber]);
        pegHeight++;
    }

    while (1) {
        if (pegHeight == 0) {
            break;
        }

        Point adjustedPos;
        adjustedPos.x = centralPegBasePos.x;
        adjustedPos.y = centralPegBasePos.y - pegHeight;
        printBlocksAtPos(game.pegs[pegNumber]->value, adjustedPos);
        game.pegs[pegNumber] = game.pegs[pegNumber]->next;

        pegHeight--;
    }
}

void printBlocksAtPos(short size, Point basePos) {
    char leftEdge[8];
    char rightEdge[4];
    strcpy(leftEdge, "");
    strcpy(rightEdge, "");

    short subtractor = 0;
    if (size % 2 == 1) {
        strncat(leftEdge, full_block, 5);
        strncat(leftEdge, left_half_block, 5);

        strncpy(rightEdge, right_half_block, 4);
        subtractor = 1;
    } else {
        strncpy(leftEdge, full_block, 4);
        strncpy(rightEdge, full_block, 4);
        subtractor = 2;
    }

    int sizeOfRing = size - subtractor;

    Point adjustedPos;
    adjustedPos.x = basePos.x - sizeOfRing / 2 - 1;
    adjustedPos.y = basePos.y;

    setCursorToPos(adjustedPos);

    char fullRing[100] = "";
    strncat(fullRing, rightEdge, 4);
    for (int i = 0; i < size; i++) {
        strncat(fullRing, full_block, 4);
    }
    strncat(fullRing, leftEdge, 8);

    printf("%s", fullRing);
    fflush(stdout);
}
