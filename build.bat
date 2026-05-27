
set CONFIG=Debug

if not "%1"=="" (
set CONFIG="%1"
)                                     


cmake --build build --config %CONFIG%
