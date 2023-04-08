//
// Created by Samuel Barkley on 08/04/2023.
//

#include <string.h>
#include "Headers/InputProcessing.h"
#include "structs/Game.h"
#include "Headers/main.h"

void removeFirstCharIfPresent(char *charBuffer);

void handleInputProcessing(char * downKeys, Game * game) {
    if (downKeys[0] != '\0') {
        switch (downKeys[0]) {
            case 'w':
                if (game->selectedRing == undefined && game->pegs[game->hoveredPegPos]->value != undefined) {
                    game->selectedRing = pop(&(game->pegs[game->hoveredPegPos]));
                }
                break;
            case 'a':
                if (game->hoveredPegPos != 0) {
                    game->hoveredPegPos--;
                }
                break;
            case 's':
                if (game->selectedRing != undefined && (game->pegs[game->hoveredPegPos]->value > game->selectedRing || game->pegs[game->hoveredPegPos]->value == undefined)) {
                    push(&game->pegs[game->hoveredPegPos], game->selectedRing);
                    game->selectedRing = undefined;
                }
                break;
            case 'd':
                if (game->hoveredPegPos != sizeof(game->pegs) / sizeof(game->pegs[0]) - 1) {
                    game->hoveredPegPos++;
                }
                break;
            case space:
                // Probably won't need this anytime soon.
                break;

        }
    }

    removeFirstCharIfPresent(downKeys);
}

void removeFirstCharIfPresent(char *charBuffer) {
    if (charBuffer[0] != '\0') {
        memmove(charBuffer, charBuffer + 1, strlen(charBuffer));
    }
}
