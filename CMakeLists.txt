cmake_minimum_required(VERSION 3.24)
project(TowerOfHanoi C)

set(CMAKE_C_STANDARD 11)

add_executable(TowerOfHanoi main.c logic/renderer.c logic/renderer.h logic/main.h logic/structs/StackNode.c logic/structs/StackNode.h)
