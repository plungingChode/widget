#!/bin/bash

# $1 = archive source files, $2 = archive name, $3... = link libs

if [[ ! -d ./obj ]]; then
    mkdir ./obj
fi

libs=""
for lib in ${*:3}; do
    libs="-l $lib $libs"
done

compile_ok=true
obj=""
for f in $1/*.cpp; do
    o=${f%.*}
    o=${o##*/}
    o="./obj/$o.o"
    obj="$obj $o"
    if ! g++ -c $f -o $o -I ./include $libs; then
        echo 'Compilation unsuccessful. Aborting...'
        exit 1
    fi
done

if [[ ! -d ./lib ]]; then
    mkdir ./lib
fi

ar rvs ./lib/lib$2.a $obj
