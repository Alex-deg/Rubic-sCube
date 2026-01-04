#!/bin/bash

cd build
cmake ..
make

if [ ! -d "shaders" ]; then
    cp -r ../shaders .
fi

if [ ! -d "media" ]; then
    cp -r ../media .
fi

# Запускаем программу
./RubiksCubeProject