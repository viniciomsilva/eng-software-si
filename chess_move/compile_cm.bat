@echo off

if not exist ..\bin mkdir ..\bin

gcc main.c src/*.c ../utils/utils.c -I include -o ../bin/chess_move.exe

if %errorlevel% equ 0 (
    ..\bin\chess_move.exe
)
