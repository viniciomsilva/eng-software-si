#!/bin/bash

if [ ! -d "../bin" ]; then
    mkdir -p ../bin
fi


gcc main.c src/*.c ../utils/utils.c -I include -o ../bin/battleship

if [ $? -eq 0 ]; then
    ../bin/battleship
fi
