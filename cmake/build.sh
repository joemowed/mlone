#!/bin/bash
set -e #terminates script execution if any command returns non-zero status
cd "$(dirname "$0")"
cd ../
mkdir -p build
cd ./build  
cmake ../cmake
#ln -s cmake/compile_commands.json ../ 
make
ctest --output-on-failure
