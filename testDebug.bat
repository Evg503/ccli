@echo off
pushd build
ctest -C Debug  --output-on-failure
::ctest --rerun-failed --output-on-failure
popd