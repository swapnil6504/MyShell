@echo off
echo Compiling MyShell...

REM Compile with g++ (requires MinGW or similar)
g++ -std=c++17 -O2 -Wall -Wextra myshell.cpp -o myshell.exe -lshell32

if %ERRORLEVEL% == 0 (
    echo Compilation successful!
    echo Run with: myshell.exe
) else (
    echo Compilation failed!
    echo Make sure you have g++ installed and in your PATH
    echo Alternative: Use Visual Studio Developer Command Prompt with:
    echo cl /std:c++17 /EHsc myshell.cpp shell32.lib
)

pause
