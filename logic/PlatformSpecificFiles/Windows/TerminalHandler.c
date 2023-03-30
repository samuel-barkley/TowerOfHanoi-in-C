//
// Created by samue on 29/03/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "TerminalHandler.h"
#include "../../main.h"


void initTerminal() {
    // Windows doesn't inherently need initializing for per character reading.
}


char *getDownKeys(short *keepPlaying) {
    char * pressedKeys = malloc(101);   // Can be made smaller. Probably don't need a 100 char long buffer between update functions. 😅

    if (kbhit()) {
        int c = getch();
        char ch = (char) c;
        printf("%c\n", (char) c);
        switch (c) {
            case (int) 'w':
            case (int) 'a':
            case (int) 's':
            case (int) 'd':
                printf("%llu\r\n", sizeof(ch));
                if (strnlen(pressedKeys, 110) < 100) {
                    strncat(pressedKeys, &ch, sizeof(ch));
                    printf("Added the char: %c to the array", (char) c);
                }
                break;
            case esc:
                printf("Exiting...\n");
                *keepPlaying = 0;
                break;
            default:
                // nothing special has been pressed.
                break;
        }
    }

    return pressedKeys;
}
