#!/bin/bash

g++ widget.cpp -o ./a.out -std=c++0x -L ./lib -I $(pwd) -I ./include -l graphics -l controls -l SDL -l SDL_ttf

./a.out
