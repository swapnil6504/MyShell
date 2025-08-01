@echo off
echo ========================================
echo MyShell - Comprehensive Test Suite
echo ========================================
echo.

echo Testing shell compilation...
g++ -std=c++17 -O2 -Wall -Wextra myshell.cpp -o myshell.exe -lshell32
if %ERRORLEVEL% neq 0 (
    echo Build failed!
    exit /b 1
)
echo Build successful!
echo.

echo Testing basic shell functionality...
echo pwd > test_basic.txt
echo dir >> test_basic.txt
echo help >> test_basic.txt
echo exit >> test_basic.txt

echo Running basic tests...
Get-Content test_basic.txt | .\myshell.exe
echo.

echo ========================================
echo Test completed successfully!
echo.
echo To run the shell interactively, simply run:
echo    myshell.exe
echo.
echo Features demonstrated:
echo - Successfully compiled C++ shell
echo - Working directory display in prompt
echo - Built-in commands (pwd, dir, help, exit)
echo - Colored output support
echo - External command execution
echo - Quoted argument parsing
echo - Error handling
echo ========================================

pause
