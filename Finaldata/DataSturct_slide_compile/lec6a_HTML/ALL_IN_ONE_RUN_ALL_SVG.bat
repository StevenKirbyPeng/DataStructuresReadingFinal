@echo off
chcp 65001 >nul
setlocal enabledelayedexpansion
cd /d "%~dp0"
if not exist bin mkdir bin
if not exist output mkdir output

echo =====================================================
echo lec6a Graphs Part I - C++ SVG Animation Generator
echo Compile C++ and generate step-by-step SVG frames
echo =====================================================

for %%F in (src\*.cpp) do (
  echo Compiling %%~nxF
  g++ -std=c++17 -O0 -I src "%%F" -o "bin\%%~nF.exe"
  if errorlevel 1 (
    echo Compile failed: %%~nxF
    pause
    exit /b 1
  )
)

for %%E in (bin\*.exe) do (
  echo Running %%~nxE
  "%%E"
  if errorlevel 1 (
    echo Run failed: %%~nxE
    pause
    exit /b 1
  )
)

call GENERATE_HTML.bat
echo Done.
pause
