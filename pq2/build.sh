#!/bin/sh


rm -rf build
rm -rf bin
mkdir build
cd build

cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_VERBOSE_MAKEFILE=0 ../
#cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_VERBOSE_MAKEFILE=0 ../
make

cd ..
