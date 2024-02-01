cmake_minimum_required(VERSION 3.27)
project(Universe)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-lSDL2 -Wall -Wextra -I${CMAKE_SOURCE_DIR}/inc")


add_executable(${PROJECT_NAME}
        ${CMAKE_SOURCE_DIR}/src/main.cpp
        ${CMAKE_SOURCE_DIR}/inc/Window.h
)
