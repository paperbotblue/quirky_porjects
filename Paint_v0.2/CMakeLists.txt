cmake_minimum_required(VERSION 3.27)
project(Paint_v0_2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-lSDL2 -Wall -Wextra -I${CMAKE_SOURCE_DIR}/inc")

add_executable(Paint_v0_2 src/main.cpp
        inc/Shapes.h
        inc/button.h
)
