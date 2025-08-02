@echo off
echo Testing SwapShell Custom Commands
echo.
echo Starting SwapShell...
echo.

echo help > commands.txt
echo coffee >> commands.txt
echo jaggi >> commands.txt
echo quote >> commands.txt
echo whoami >> commands.txt
echo mood >> commands.txt
echo chai >> commands.txt
echo hi >> commands.txt
echo date >> commands.txt
echo sneaker >> commands.txt
echo swapgpt >> commands.txt
echo thanks >> commands.txt
echo bug >> commands.txt
echo devtip >> commands.txt
echo ls >> commands.txt
echo sudo >> commands.txt
echo sing >> commands.txt
echo swapify >> commands.txt
echo exit >> commands.txt

echo Running SwapShell with test commands...
type commands.txt | .\swapshell.exe

del commands.txt
echo.
echo Test completed!
pause
