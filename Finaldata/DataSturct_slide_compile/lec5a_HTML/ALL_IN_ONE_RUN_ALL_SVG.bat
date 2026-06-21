@echo off
chcp 65001 >nul
setlocal enabledelayedexpansion

echo =====================================================
echo lec5_a Trees Part I - STEP BY STEP SVG Generator
echo Compile all C++ and generate topic-based SVG frames
echo =====================================================

if not exist bin mkdir bin
if not exist output mkdir output

echo.
echo [Step 1/3] Compile all C++...
for %%f in (src\*.cpp) do (
    echo Compiling %%~nxf ...
    g++ -std=c++17 "%%f" -o "bin\%%~nf.exe"
    if errorlevel 1 (
        echo Compile failed: %%~nxf
        pause
        exit /b 1
    )
)

echo.
echo [Step 2/3] Run all programs...
for %%f in (bin\*.exe) do (
    echo Running %%~nxf ...
    "%%f"
    if errorlevel 1 (
        echo Program failed: %%~nxf
        pause
        exit /b 1
    )
)

echo.
echo.
echo [Step 3/3] Generate auto HTML...
call "%~dp0GENERATE_HTML.bat"
if errorlevel 1 (
    echo Auto HTML generation failed.
    pause
    exit /b 1
)

echo.
echo Finished. Step-by-step SVG frames are in output\topic_steps folders.
echo HTML files: index.html and auto_generated_index.html
echo No Graphviz is required.
pause
