#!/bin/bash
cd "$(dirname "$0")"
cd ../
mkdir -p build
cd ./build  
cmake ../cmake
#ln -s cmake/compile_commands.json ../ 
make
ctest --output-on-failure
