@echo off
chcp 65001 >nul
setlocal

echo =============================================
echo Generate index.html and auto_generated_index.html from output SVG
echo =============================================

powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0generate_auto_html.ps1"

if errorlevel 1 (
    echo HTML generation failed.
    pause
    exit /b 1
)

echo Done: index.html and auto_generated_index.html
pause
