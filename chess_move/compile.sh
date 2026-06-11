#!/bin/bash

if [ ! -d "../bin" ]; then
    mkdir -p ../bin
fi

gcc main.c src/*.c ../utils/utils.c -I include -o ../bin/chess_move

if [ $? -eq 0 ]; then
    ../bin/chess_move
fi
