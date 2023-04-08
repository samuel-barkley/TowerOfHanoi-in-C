//
// Created by samue on 25/03/2023.
// Block elements Unicode https://symbl.cc/en/unicode/blocks/block-elements/
//

#include <stdio.h>
#include <string.h>
#include "Headers/renderer.h"
#include "Headers/main.h"

void handleTerminalCheckingAndResizing(Game game, Point terminalSize);

void updateSelectedRing(Game game);

void setCursorToPos(Point pos);

void updateTime(Game game);

void refreshScreen(Game game);

void updatePegSelector(Game game);

void clearRingSelections(Game game);

void clearBlocksAtPos(short size, Point basePos);

void clearPegSelectors();

void printBlocksAtPos(short size, Point basePos);

void drawPeg(Game game, short pegNumber);

void drawAllPegs(Game game);

void clearTopRing(Game game);

void updateElementBasePositions(Point newSize);

void clearFps();

void drawFps(double t_delta);

Point scoreBasePos = {0, 0};
Point centralPegBasePos = {0, 0};
Point fpsPos = {0, 0};
unsigned int pegDistance = 0;
short heightBuffer = 3;

void render(double t_delta, Game *game) {
    Point terminalSize = getTerminalSize();
    handleTerminalCheckingAndResizing(*game, terminalSize);

    static short shouldInit = 1;
    if (shouldInit == 1) {
        clearTerminal();
        updateElementBasePositions(terminalSize);
        pegDistance = game->height + 10;
        updateSelectedRing(*game);
        updateTime(*game);
        updatePegSelector(*game);
        drawAllPegs(*game);
        shouldInit = 0;
    }

    static Game previousGameState;
    handleGameUpdating(game, previousGameState);
    drawFps(t_delta);

    previousGameState = *game;
}

void updateElementBasePositions(Point newSize) {
    scoreBasePos.x = newSize.x / 2;
    scoreBasePos.y = 0;

    centralPegBasePos.x = newSize.x / 2;
    centralPegBasePos.y = newSize.y;
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
        if (game->selectedRing == undefined) {
            clearRingSelections(*game);
            clearTopRing(*game);
        }
        drawPeg(*game, game->hoveredPegPos);
    }

    if (game->hoveredPegPos != previousGameState.hoveredPegPos) {
        updatePegSelector(*game);
        if (game->selectedRing != undefined) {
            updateSelectedRing(*game);
        }
    }

    if (game->time != previousGameState.time) {
        updateTime(*game);
    }
}

void updateSelectedRing(Game game) {
    if (game.selectedRing == undefined) {
        return;
    }
    clearRingSelections(game);

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
    adjustedPos.x = centralPegBasePos.x + (pegDistance * multiplier);
    adjustedPos.y = centralPegBasePos.y - game.height - heightBuffer;

    printBlocksAtPos(game.selectedRing, adjustedPos);
    clearTopRing(game);
}

void clearTopRing(Game game) {
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

    Point adjustedClearPos;
    // adjustedClearPos.x =
    //         (centralPegBasePos.x + ((int) pegDistance) * multiplier) - (game.pegs[game.hoveredPegPos]->value / 2) + 1;
    adjustedClearPos.x = centralPegBasePos.x + (pegDistance * multiplier);
    // - 1 is because the ring to be deleted has already been removed
    adjustedClearPos.y = centralPegBasePos.y - getNodeCountExclBase(game.pegs[game.hoveredPegPos]) - 1;

    clearBlocksAtPos(game.height + 2, adjustedClearPos);
}

void updateTime(Game game) {
    char timeToPrint[11];
    memset(timeToPrint, '\0', sizeof(timeToPrint));

    char *numberCharArray = getNumberCharArray(game.time);
    short stringLength = (short) strlen(numberCharArray);

    strncpy(timeToPrint, numberCharArray, stringLength);

    Point adjustedPos;
    adjustedPos.x = scoreBasePos.x - ((int) strnlen(timeToPrint, 11));
    adjustedPos.y = scoreBasePos.y;

    setCursorToPos(adjustedPos);

    printf("Time: %s", timeToPrint);
    fflush(stdout);
}

void updatePegSelector(Game game) {
    clearPegSelectors();

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

    Point adjustedSelectorPos;
    adjustedSelectorPos.x = centralPegBasePos.x + pegDistance * multiplier;
    adjustedSelectorPos.y = centralPegBasePos.y + 1;
    setCursorToPos(adjustedSelectorPos);

    printf("%s", selector_arrow);

    fflush(stdout);
}

void clearPegSelectors() {
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

void clearRingSelections(Game game) {
    int widthToClear = game.height + 4;
    char clearingBuffer[widthToClear + 1];
    strcpy(clearingBuffer, "");
    for (int i = 0; i < widthToClear; i++) {
        clearingBuffer[i] = ' ';
    }
    clearingBuffer[widthToClear] = '\0';

    Point cursorPos0;
    cursorPos0.x = (centralPegBasePos.x - (int) pegDistance) - (widthToClear / 2) + 1;
    cursorPos0.y = centralPegBasePos.y - game.height - heightBuffer;

    Point cursorPos1;
    cursorPos1.x = centralPegBasePos.x - (widthToClear / 2);
    cursorPos1.y = centralPegBasePos.y - game.height - heightBuffer;

    Point cursorPos2;
    cursorPos2.x = (centralPegBasePos.x + (int) pegDistance) - (widthToClear / 2) + 1;
    cursorPos2.y = centralPegBasePos.y - game.height - heightBuffer;


    setCursorToPos(cursorPos0);
    printf("%s", clearingBuffer);

    setCursorToPos(cursorPos1);
    printf("%s", clearingBuffer);

    setCursorToPos(cursorPos2);
    printf("%s", clearingBuffer);
    fflush(stdout);
}

void setCursorToPos(Point pos) {
    printf("\033[%d;%dH", pos.y, pos.x);
}

void refreshScreen(Game game) {
    clearTerminal();
    updateTime(game);
    drawAllPegs(game);
    updatePegSelector(game);
    updateSelectedRing(game);
}

void drawAllPegs(Game game) {
    drawPeg(game, 0);
    drawPeg(game, 1);
    drawPeg(game, 2);
}

void drawPeg(Game game, short pegNumber) {
    Game game_copy;
    copy_game(&game, &game_copy);

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
        adjustedPos.x = centralPegBasePos.x + (pegDistance * multiplier);
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

void clearBlocksAtPos(short size, Point basePos) {
    short subtractor = 0;
    if (size % 2 == 1) {
        subtractor = 1;
    } else {
        subtractor = 2;
    }

    int sizeOfRing = size - subtractor;

    int clearBufferSize = size + 2;
    char clearBuffer[clearBufferSize + 1];
    for (int i = 0; i < clearBufferSize; i++) {
        clearBuffer[i] = ' ';
    }
    clearBuffer[clearBufferSize] = '\0';

    Point adjustedPos;
    adjustedPos.x = basePos.x - sizeOfRing / 2 - 1;
    adjustedPos.y = basePos.y;

    setCursorToPos(adjustedPos);

    printf("%s", clearBuffer);
    fflush(stdout);
}

void drawFps(double t_delta) {
    unsigned int fps = 1.0 / (t_delta * 1000);
    char fpsString[10];
    if (fps >= 10000) {
        sprintf(fpsString, infinity);
    }
    sprintf(fpsString, "%d", fps);

     clearFps();

     setCursorToPos(fpsPos);
     printf("%s fps", fpsString);
     fflush(stdout);
}

void clearFps() {
    char clearBufferSize = 15;
    char clearBuffer[clearBufferSize + 1];

    for (int i = 0; i < clearBufferSize; i++) {
        clearBuffer[i] = ' ';
    }
    clearBuffer[clearBufferSize] = '\0';

    setCursorToPos(fpsPos);
    printf("%s", clearBuffer);
}
