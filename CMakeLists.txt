cmake_minimum_required(VERSION 3.5)
project(doronin_homework)

file(GLOB_RECURSE SRC src/*.hpp src/*.cpp)
add_executable(homework ${SRC})
