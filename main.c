#include <stdlib.h>
#include <string.h>
#include "logic/main.h"
#include "logic/renderer.h"
#include "logic/structs/StackNode.h"
#include "logic/structs/Game.h"

int main() {
    double t_delta;
    double t_lastUpdate = getTimeInSeconds(clock());
    double t_accumulator = getTimeInSeconds(clock());
    double t_slice = 0.1;
    long long startTime = time(NULL);
    long long gameClockAccumulator = startTime;

    Game game = getInitGame(8);

    short playing = 1;
    // Can be made smaller. Probably don't need a 100 char long buffer between update functions. 😅
    char *downKeys = malloc(101);
    strcpy(downKeys, "");

    initTerminal();
    getTerminalSize();

    while (playing == 1) {
        t_delta = getTimeInSeconds(clock()) - t_lastUpdate;
        t_lastUpdate += t_delta;
        t_accumulator += t_delta;

        getDownKeys(&playing, downKeys);

        while (t_accumulator > t_slice) {
            update(&game, downKeys, &gameClockAccumulator);
            t_accumulator -= t_slice;
        }

        render(t_delta, &game);
    }

    return 0;
}

void update(Game *game, char *downKeys, long long * gameClockAccumulator) {
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

     long long timeDifference = time(NULL) - *gameClockAccumulator;

     if (timeDifference >= 1) {
         game->time += timeDifference;
         *gameClockAccumulator = time(NULL);
     }
}

Game getInitGame(short height) {
    node_t *peg0 = (node_t *) malloc(sizeof(node_t));
    node_t *peg1 = (node_t *) malloc(sizeof(node_t));
    node_t *peg2 = (node_t *) malloc(sizeof(node_t));

    peg0->value = undefined;
    peg0->next = NULL;
    peg1->value = undefined;
    peg1->next = NULL;
    peg2->value = undefined;
    peg2->next = NULL;

    for (int i = 0; i < height; i++) {
        push(&peg0, height - i);
    }

    Game *game = (Game *) malloc(sizeof(Game));
    game->time = 0;
    game->pegs[0] = peg0;
    game->pegs[2] = peg1;
    game->pegs[1] = peg2;
    game->hoveredPegPos = 0;
    game->selectedRing = undefined;
    game->height = height;
    return *game;
}

void removeFirstCharIfPresent(char *charBuffer) {
    if (charBuffer[0] != '\0') {
        memmove(charBuffer, charBuffer + 1, strlen(charBuffer));
    }
}

double getTimeInSeconds(clock_t t) {
    return ((double) t) / CLOCKS_PER_SEC;
}

clock_t getTimeInTicks(double t) {
    return (clock_t) t * CLOCKS_PER_SEC;
}

double microToMilliSec(double microSeconds) {
    return microSeconds * 1000.0;
}

double microToSec(double microSeconds) {
    return microSeconds * 1000.0 * 1000.0;
}
