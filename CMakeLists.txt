cmake_minimum_required(VERSION 3.5)
project(doronin_homework)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE SRC
    src/*.hpp
    src/*.cpp
    include/*.hpp
    include/*.cpp
)
add_executable(homework ${SRC})
target_include_directories(homework PUBLIC include)
