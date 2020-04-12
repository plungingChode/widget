#!/bin/bash

if [[ ! -d ./obj ]]; then
    mkdir ./obj
fi

compile_ok=true
obj=""
for f in src/*.cpp; do
    o=${f%.*}
    o=${o##*/}
    o="./obj/$o.o"
    obj="$obj $o"
    if ! g++ -c $f -o $o -std=c++11 -Wall -Iinclude -lgraphics -lSDL -lSDL_ttf; then
        echo 'Compilation unsuccessful. Aborting...'
        exit 1
    fi
done

if [[ ! -d ./lib ]]; then
    mkdir ./lib
fi

ar rvs ./lib/libcontrols.a $obj
