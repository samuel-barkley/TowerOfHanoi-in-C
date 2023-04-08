//
// Created by samue on 29/03/2023.
//

#include "../../Headers/main.h"
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include "TerminalHandler.h"

struct termios orig_termios;

void reset_terminal_mode();

void set_conio_terminal_mode();

int unix_kbhit();

int unix_getch();

void addCharToList(char *pressedKeys, char newKey);

void initTerminal() {
    set_conio_terminal_mode();
}

char *getDownKeys(short *keepPlaying, char *pressedKeys) {
    char *testString = "";

    if (unix_kbhit()) {
        int c = unix_getch();
        char ch = (char) c;
        // printf("%d\r\n", c);

        // TODO: Something is wrong with capturing arrow keys.
        switch (c) {
            case (int) 'w':
            case (int) 'a':
            case (int) 's':
            case (int) 'd':
            case space:
                addCharToList(pressedKeys, ch);
                break;
            case esc:
                // printf("Exiting...");
                *keepPlaying = 0;
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

void clearTerminal() {
    system("clear");
}

Point getTerminalSize() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    // printf ("lines %d\r\n", w.ws_row);
    // printf ("columns %d\r\n", w.ws_col);

    Point size;
    size.x = w.ws_col;
    size.y = w.ws_row;

    return size;
}

void addCharToList(char *pressedKeys, char newKey) {
    if (strnlen(pressedKeys, 110) < 100) {
        strncat(pressedKeys, &newKey, sizeof(newKey));
        // printf("Added the char: %c to the array\r\n", newKey);
    }
}
