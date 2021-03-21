#!/usr/bin/zsh

g++ --std=c++17 -I"/home/fanrende/Documents/code/class2021/game_engine/HW1_ref/include" src/*.cpp "/home/fanrende/Documents/code/class2021/game_engine/glad/src/glad.c" -lGL -lGLU -lglfw3 -pthread -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -ldl -lXcursor && ./a.out
