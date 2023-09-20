#!/usr/bin/zsh

g++ --std=c++17 -I"./include" -I"./glfw-3.3.3/include" src/*.cpp "./src/*.c" "./glfw-3.3.3/src" -lGL -lGLU -lglfw3 -pthread -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -ldl -lXcursor && ./a.out
