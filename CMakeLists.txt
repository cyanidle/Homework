cmake_minimum_required(VERSION 3.5)
project(doronin_homework)

set(CMAKE_CXX_STANDARD 17)

add_library(common INTERFACE)
target_include_directories(common INTERFACE include)

file(GLOB_RECURSE headers include/*)

function(add_dz dir)
    file(GLOB_RECURSE src ${dir}/*)
    add_executable(${dir} ${src} ${headers})
    target_link_libraries(${dir} PRIVATE common)
endfunction()

add_dz(dz1)
add_dz(dz2)
add_dz(dz3)
add_dz(dz4)
add_dz(dz5)
add_dz(dz6)
add_dz(dz7)
add_dz(dz8)
add_dz(dz9)
add_dz(dz10)

add_executable(salted-caesar salted-caesar/main.cpp)
target_link_libraries(salted-caesar PRIVATE common)
