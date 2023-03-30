//
// Created by samue on 29/03/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "TerminalHandler.h"
#include "../../main.h"

void addCharToList(char * pressedKeys, char newKey);

void initTerminal() {
    // Windows doesn't inherently need initializing for per character reading.
}


void getDownKeys(short *keepPlaying, char * pressedKeys) {
    if (kbhit()) {
        int c = getch();
        char ch = (char) c;
        printf("%d\r\n", c);
        switch (c) {
            case (int) 'w':
            case (int) 'a':
            case (int) 's':
            case (int) 'd':
            case space:
                addCharToList(pressedKeys, ch);
                break;
            case esc:
                printf("Exiting...\r\n");
                *keepPlaying = 0;
                break;
            default:
                // nothing special has been pressed.
                break;
        }
    }
}

void addCharToList(char * pressedKeys, char newKey) {
    if (strnlen(pressedKeys, 110) < 100) {
        strncat(pressedKeys, &newKey, sizeof(newKey));
        printf("Added the char: %c to the array\r\n", newKey);
    }
}
