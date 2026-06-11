#!/bin/bash

if [ ! -d "../bin" ]; then
    mkdir -p ../bin
fi

gcc super_trumps.c -o ../bin/super_trumps

if [ $? -eq 0 ]; then
    ../bin/super_trumps
fi
