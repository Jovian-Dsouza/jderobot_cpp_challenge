#!/bin/bash
rm -rf build
mkdir build && cd build
cmake ..
make

echo 
echo "Running Test case : $1"
./labyrinth ../test/input$1.txt ../test/output$1.txt
