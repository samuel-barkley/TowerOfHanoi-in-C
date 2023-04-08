#include <stdlib.h>
#include <string.h>
#include "logic/Headers/main.h"
#include "logic/Headers/renderer.h"
#include "logic/structs/Game.h"
#include "logic/Headers/InputProcessing.h"
#include "logic/Headers/TimeHelper.h"

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
    handleInputProcessing(downKeys, game);

     long long timeDifference = time(NULL) - *gameClockAccumulator;

     if (timeDifference >= 1) {
         game->time += timeDifference;
         *gameClockAccumulator = time(NULL);
     }
}
