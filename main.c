#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <strings.h>
#include <termios.h>
#include "logic/main.h"
#include "logic/renderer.h"
#include "logic/structs/StackNode.h"
#include "logic/structs/Game.h"

void clearConsole();
double microToMilliSec(double microSeconds);
double microToSec(double microSeconds);
double getTimeInSeconds(clock_t t);
clock_t getTimeInTicks(double t);
Game getInitGame(short height);
char * getDownKeys();
void set_conio_terminal_mode();
int kbhit();
int getch();
void update(Game * game);

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

    // TODO: Set size of the terminal in those that support printer control sequences.  printf("\e[8;50;150t");
    // TODO: Set size of terminal in windows if it doesn't support printer control sequences.   SMALL_RECT windowSize = {0 , 0 , 77 , 47} //change the values
    //    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize)


    Game game = getInitGame(3);

    set_conio_terminal_mode();
    short playing = 1;

    while (playing) {
        t_delta = getTimeInSeconds(clock()) - t_lastUpdate;
        t_lastUpdate += t_delta;
        t_accumulator += t_delta;

        char keysDown[10];
        strncpy(keysDown, getDownKeys(), sizeof(keysDown) / sizeof(char));

        while (t_accumulator > t_slice) {
            update(&game);
            t_accumulator -= t_slice;
        }

        render(t_delta);
    }

    return 0;
}

void update(Game * game) {
    printf("%u\n", game->score);
}

Game getInitGame(short height) {
    node_t * peg0 ;//= (node_t *) malloc(sizeof(node_t));
    node_t * peg1 = (node_t *) malloc(sizeof(node_t));
    node_t * peg2 = (node_t *) malloc(sizeof(node_t));

    push(&peg0, 3);
    push(&peg0, 2);
    push(&peg0, 1);

    for (int i = 0; i < height; i++) {
        push(&peg0, height - i);
    }

    Game game;
    game.score = 0;
    game.pegs[0] = peg0;
    game.pegs[2] = peg1;
    game.pegs[1] = peg2;
    return game;
}

char * getDownKeys() {
    char * testString = "";

    if (kbhit()) {
        char c = getch();
        printf("%d\n", c);
        switch (c) {
            case esc:
                printf("Exiting...");
                exit(0);
        }
    }

    return testString;
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

struct termios orig_termios;

void reset_terminal_mode()
{
    tcsetattr(0, TCSANOW, &orig_termios);
}

void set_conio_terminal_mode()
{
    struct termios new_termios;

    /* take two copies - one for now, one for later */
    tcgetattr(0, &orig_termios);
    memcpy(&new_termios, &orig_termios, sizeof(new_termios));

    /* register cleanup handler, and set the new terminal mode */
    atexit(reset_terminal_mode);
    cfmakeraw(&new_termios);
    tcsetattr(0, TCSANOW, &new_termios);
}

int kbhit()
{
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv) > 0;
}

int getch()
{
    int r;
    unsigned char c;
    if ((r = read(0, &c, sizeof(c))) < 0) {
        return r;
    } else {
        return c;
    }
}
