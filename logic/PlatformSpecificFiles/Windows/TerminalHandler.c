//
// Created by samue on 29/03/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "TerminalHandler.h"
#include "../../main.h"

char * getDownKeys() {
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
    }
}