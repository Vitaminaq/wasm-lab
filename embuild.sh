#!/bin/sh

rm -rf build

mkdir build

cd build

emcmake cmake ..

# 最大32个文件并行编译
emmake make -j32
