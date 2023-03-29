//
// Created by samue on 29/03/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "TerminalHandler.h"
#include "../../main.h"


void initTerminal() {

}

char *getDownKeys(short *keepPlaying) {
    char *pressedKeys = "";
    if (kbhit()) {
        int c = getch();
        printf("%d\n", c);
        switch (c) {
            case esc:
                printf("Exiting...\n");
                *keepPlaying = 0;
        }
    }

    return pressedKeys;
}
