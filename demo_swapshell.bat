@echo off
echo ==============================================
echo         SWAPSHELL DEMO SCRIPT
echo ==============================================
echo.

echo Testing SwapShell custom commands...
echo.

echo *** Testing COFFEE command ***
echo coffee | .\swapshell.exe | head -6
echo.

echo *** Testing QUOTE command ***
echo quote | .\swapshell.exe | head -6
echo.

echo *** Testing WHOAMI command ***
echo whoami | .\swapshell.exe | head -6
echo.

echo *** Testing MOOD command ***
echo mood | .\swapshell.exe | head -6
echo.

echo *** Testing HI command ***
echo hi | .\swapshell.exe | head -6
echo.

echo Demo completed! All SwapShell features are working.
pause
