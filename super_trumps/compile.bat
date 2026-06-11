@echo off

if not exist ..\bin mkdir ..\bin

gcc super_trumps.c -o ../bin/super_trumps

if %errorlevel% equ 0 (
    ..\bin\super_trumps
)
