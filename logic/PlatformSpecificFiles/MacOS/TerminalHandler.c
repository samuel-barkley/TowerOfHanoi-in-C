//
// Created by samue on 29/03/2023.
//

#include "../../main.h"
#include <string.h>
#include <stdlib.h>
#include <winsock.h>
#include <io.h>
#include <stdio.h>
#include "TerminalHandler.h"

struct termios orig_termios;

void reset_terminal_mode();
void set_conio_terminal_mode();
int unix_kbhit();
int unix_getch();

void initTerminal() {
    set_conio_terminal_mode();
}

char * getDownKeys(short *keepPlaying) {
    char *testString = "";

    if (unix_kbhit()) {
        char c = unix_getch();
        printf("%d\n", c);
        switch (c) {
            case esc:
                printf("Exiting...");
                exit(0);
        }
    }

    return testString;
}

void reset_terminal_mode() {
    tcsetattr(0, TCSANOW, &orig_termios);
}

void set_conio_terminal_mode() {
    struct termios new_termios;

    /* take two copies - one for now, one for later */
    tcgetattr(0, &orig_termios);
    memcpy(&new_termios, &orig_termios, sizeof(new_termios));

    /* register cleanup handler, and set the new terminal mode */
    atexit(reset_terminal_mode);
    cfmakeraw(&new_termios);
    tcsetattr(0, TCSANOW, &new_termios);
}

int unix_kbhit() {
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv) > 0;
}

int unix_getch() {
    int r;
    unsigned char c;
    if ((r = read(0, &c, sizeof(c))) < 0) {
        return r;
    } else {
        return c;
    }
}