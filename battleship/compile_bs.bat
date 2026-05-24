@echo off

if not exist ..\bin mkdir ..\bin

gcc main.c src/*.c -I include -o ../bin/battleship.exe

if %errorlevel% equ 0 (
    ..\bin\battleship.exe
)
