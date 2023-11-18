cmake_minimum_required(VERSION 3.5)
project(doronin_homework)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE SRC src/*.hpp src/*.cpp)
add_executable(homework ${SRC})
