#!/bin/bash

if g++ widget.cpp -o ./a.out -std=c++0x -L ./lib -I ./include -l graphics -l controls -l SDL -l SDL_ttf; then
    ./a.out --release
fi
