#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <pthread.h>
#include "logic/main.h"
#include "logic/renderer.h"
#include "logic/structs/StackNode.h"
#define esc 27

void clearConsole();
double microToMilliSec(double microSeconds);
double microToSec(double microSeconds);
double getTimeInSeconds(clock_t t);
clock_t getTimeInTicks(double t);
void update();

typedef struct {
    unsigned int score;
    node_t pegs[3];
} Game;

int main() {
    /* while(1) {
    //     if (kbhit()) {
    //         char c = getch();
    //         printf("%d\n", c);

    //         switch (c) {
    //             case esc:
    //                 printf("Exiting...");
    //                 exit(0);
    //         }
    //     }
     }*/

    double t_delta;
    double t_lastUpdate = getTimeInSeconds(clock());
    double t_accumulator = getTimeInSeconds(clock());
    double t_slice = 1;

    // usleep(microToSec(3));


    while (1) {
        t_delta = getTimeInSeconds(clock()) - t_lastUpdate;
        t_lastUpdate += t_delta;
        t_accumulator += t_delta;

        printf("t_delta: %f \n", t_delta);
        while (t_accumulator > t_slice) {
            update(t_delta);
            t_accumulator -= t_slice;
        }
    }

    getchar();
    return 0;
}

void update(double t_delta) {


    render(t_delta);
}

double getTimeInSeconds(clock_t t) {
    return ((double)t)/CLOCKS_PER_SEC;
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
