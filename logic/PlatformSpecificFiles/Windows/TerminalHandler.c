//
// Created by samue on 29/03/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "TerminalHandler.h"
#include "../../main.h"


void initTerminal() {

}


char *getDownKeys(short *keepPlaying, char * pressedKeys) {
    // char pressedKeys[100];
    // memset(pressedKeys,0,strlen(pressedKeys));


    printf("test hihi\r\n");
    printf("%llu\r\n", strnlen(pressedKeys, 1000));
    char thing = 'a';
    char otherthing[2]; // 1 + null terminator.
    otherthing[0] = 'b';
    printf("length: %llu \r\n", strnlen(otherthing, 100));
    printf("test0\r\n");
    char dest[20]="Hello";
    char src[20]="World";
    strncat(dest,otherthing,3);
    printf("%s\n",dest);
    strncat(dest,otherthing,20);
    printf("%s\n",dest);
    strncat(pressedKeys, otherthing, 1);
    printf("test1");
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
                strncat(pressedKeys, &ch, sizeof(ch));
                printf("Added the char: %c to the array", (char) c);
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
