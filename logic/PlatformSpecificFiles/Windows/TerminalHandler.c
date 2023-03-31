//
// Created by samue on 29/03/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>
#include "TerminalHandler.h"
#include "../../main.h"

void addCharToList(char *pressedKeys, char newKey);

void initTerminal() {
    // Windows doesn't inherently need initializing for per character reading.
}


void getDownKeys(short *keepPlaying, char *pressedKeys) {
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
                // printf("Exiting...\r\n");
                *keepPlaying = 0;
                break;
            default:
                // nothing special has been pressed.
                break;
        }
    }
}

void clearTerminal() {
    if (strncmp(PLATFORM_NAME, "windows", 7) == 0) {
        system("cls");
    }
}

Point getTerminalSize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    // printf("columns: %d\n", columns);
    // printf("rows: %d\n", rows);

    Point size = {columns, rows};

    return size;
}

void addCharToList(char *pressedKeys, char newKey) {
    if (strnlen(pressedKeys, 110) < 100) {
        strncat(pressedKeys, &newKey, sizeof(newKey));
        // printf("Added the char: %c to the array\r\n", newKey);
    }
}
