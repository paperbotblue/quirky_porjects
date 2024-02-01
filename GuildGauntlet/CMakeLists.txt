cmake_minimum_required(VERSION 3.27)
project(GuildGauntlet)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -g -I${CMAKE_SOURCE_DIR}/inc -lGLEW -lglfw -lGLU -lGL")

add_executable(GuildGauntlet src/main.cpp)
