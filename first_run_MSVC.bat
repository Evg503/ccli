@ECHO OFF

echo Cleaning build directory...
if exist build rmdir /s /q build


cmake -G "Visual Studio 17 2022" -B build %*