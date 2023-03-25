#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "logic/main.h"
#include "logic/renderer.h"

#define esc 27

void clearConsole();

int main() {
    while(1) {
        if (kbhit()) {
            char c = getch();
            printf("%d\n", c);

            switch (c) {
                case esc:
                    printf("Exiting...");
                    exit(0);
            }
        }
        //printf("Testing before");
        //clearConsole();
    }

    return 0;
}

void clearConsole() {
    if (PLATFORM_NAME == "windows") {
        system("cls");
    } else {
        system("clear");
    }
}
