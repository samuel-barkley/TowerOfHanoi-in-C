cmake_minimum_required(VERSION 3.22)
project(TowerOfHanoi C)
set(CMAKE_C_STANDARD 11)

INCLUDE (CheckIncludeFiles)

CHECK_INCLUDE_FILES (termios.h HAVE_TERMIOS_H)
CHECK_INCLUDE_FILES (conio.h HAVE_CONIO_H)

if (HAVE_CONIO_H)
    add_executable(TowerOfHanoi main.c logic/renderer.c logic/Headers/renderer.h logic/Headers/main.h logic/structs/StackNode.c logic/structs/StackNode.h logic/structs/Game.c logic/structs/Game.h logic/PlatformSpecificFiles/Windows/TerminalHandler.c logic/PlatformSpecificFiles/Windows/TerminalHandler.h logic/structs/DtosHelper.c logic/structs/DtosHelper.h logic/InputProcessing.c logic/Headers/InputProcessing.h logic/TimeHelper.c logic/Headers/TimeHelper.h)
else (HAVE_TERMIOS_H)
    add_executable(TowerOfHanoi main.c logic/renderer.c logic/Headers/renderer.h logic/Headers/main.h logic/structs/StackNode.c logic/structs/StackNode.h logic/structs/Game.c logic/structs/Game.h logic/PlatformSpecificFiles/MacOS/TerminalHandler.c logic/PlatformSpecificFiles/MacOS/TerminalHandler.h logic/structs/DtosHelper.c logic/structs/DtosHelper.h logic/InputProcessing.c logic/Headers/InputProcessing.h logic/TimeHelper.c logic/Headers/TimeHelper.h)
endif (HAVE_CONIO_H)

