#!/bin/bash
cd "$(dirname "$0")"
mkdir -p build
cd ./build  
cmake ..
ln -s cmake/compile_commands.json ../   
make
