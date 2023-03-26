//
// Created by samue on 25/03/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "renderer.h"
#include "main.h"

struct SMALL_RECT {
    short Left;
    short Top;
    short Right;
    short Bottom;
};

void render(double t_delta) {
    // clearConsole();
    // printf("Update, %f\n", t_delta);
}

void clearConsole() {
    if (strncmp(PLATFORM_NAME, "windows", 10) == 0) {
        system("cls");
    } else {
        system("clear");
    }
}


