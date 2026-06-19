@echo off
chcp 65001 >nul
setlocal enabledelayedexpansion
cd /d "%~dp0"
echo =====================================================
echo lec4 Linked Lists - C++ SVG Animation Generator
echo Compile C++ and generate step-by-step SVG frames
echo =====================================================
if not exist bin mkdir bin
if not exist output mkdir output
for %%f in (src\*.cpp) do (
  echo Compiling %%~nxf
  g++ -std=c++17 -O2 -I src "%%f" -o "bin\%%~nf.exe"
  if errorlevel 1 (
    echo Compile failed: %%~nxf
    pause
    exit /b 1
  )
)
for %%e in (bin\*.exe) do (
  echo Running %%~nxe
  "%%e"
)
echo.
echo Generate HTML...
call GENERATE_HTML.bat
echo.
echo Done.
pause
