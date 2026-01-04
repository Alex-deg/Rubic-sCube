# Минимальный рабочий CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(RubiksCubeProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    GL
    GLEW
    glfw
    SDL2_mixer
    pthread
    m
    dl
    X11
    Xi
    Xrandr
)

# НИКАКОГО КОПИРОВАНИЯ - делаем это вручную