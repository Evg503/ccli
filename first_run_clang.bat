@ECHO OFF

echo Cleaning build directory...
if exist build rmdir /s /q build


cmake -G "Ninja Multi-Config" -B build -DCMAKE_C_COMPILER=clang %*