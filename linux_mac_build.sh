#!/bin/
build_type=$(Debug)
if [ "$1" = "Release" ]; then
    build_type=$($1)
fi

if [ ! -d "build" ]; then
    mkdir build
fi

cd build

echo **********************************************************************
echo ** CMake -G Makefile build type build_type
echo **********************************************************************
cmake -DCMAKE_BUILD_TYPE=build_type ..

make

cd ..