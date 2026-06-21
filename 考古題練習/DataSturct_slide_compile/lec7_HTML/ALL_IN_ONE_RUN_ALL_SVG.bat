@echo off
chcp 65001 > nul
cd /d "%~dp0"
if not exist bin mkdir bin
if not exist output mkdir output
for %%f in (src\*.cpp) do (
 echo Compiling %%~nxf
 g++ -std=c++17 -O2 "%%f" -o "bin\%%~nf.exe" || goto fail
)
for %%e in (bin\*.exe) do (
 echo Running %%~nxe
 "%%e" || goto fail
)
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0generate_auto_html.ps1" || goto fail
echo Done. Open index.html
pause
exit /b 0
:fail
echo Failed.
pause
exit /b 1
