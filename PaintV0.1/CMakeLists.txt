cmake_minimum_required(VERSION 3.27)
project(PaintV0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-lSDL2 -Wall -Wextra -I${CMAKE_SOURCE_DIR}/inc")


add_executable(${PROJECT_NAME}
        ${CMAKE_SOURCE_DIR}/src/main.cpp
        ${CMAKE_SOURCE_DIR}/inc/Window.h
)
