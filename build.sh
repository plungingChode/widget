#!/bin/bash

if g++ widget.cpp -o ./a.out -std=c++11 -Iinclude -Llib -lcontrols -lgraphics -lSDL -lSDL_ttf; then
    ./a.out
fi
