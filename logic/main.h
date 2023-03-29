//
// Created by samue on 25/03/2023.
//

#ifndef TOWEROFHANOI_MAIN_H
#define TOWEROFHANOI_MAIN_H
#if defined(_WIN32)
#define PLATFORM_NAME "windows" // Windows
    #include "./PlatformSpecificFiles/Windows/TerminalHandler.h"
#elif defined(_WIN64)
    #define PLATFORM_NAME "windows" // Windows
    #include "./PlatformSpecificFiles/Windows/TerminalHandler.h"
#elif defined(__linux__)
    #define PLATFORM_NAME "linux" // Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos and other
#elif defined(__APPLE__) && defined(__MACH__) // Apple OSX and iOS (Darwin)
    #include <TargetConditionals.h>
    #if TARGET_OS_MAC == 1
        #define PLATFORM_NAME "osx" // Apple OSX
        #include "./PlatformSpecificFiles/MacOS/TerminalHandler.h"
    #endif
#else
#define PLATFORM_NAME NULL
#endif

#include "time.h"
#include "./structs/Game.h"

double microToMilliSec(double microSeconds);
double microToSec(double microSeconds);
double getTimeInSeconds(clock_t t);
clock_t getTimeInTicks(double t);
Game getInitGame(short height);
void set_conio_terminal_mode();
void update(Game *game);

#define esc 27

#endif //TOWEROFHANOI_MAIN_H
