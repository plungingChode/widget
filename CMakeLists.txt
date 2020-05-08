cmake_minimum_required(VERSION 2.8.9)
project(widget)

include_directories(include)
file(GLOB SOURCES src/*)

add_compile_options(-Wall -Wshadow)

add_executable(a.out widget.cpp ${SOURCES})
target_link_libraries(a.out graphics SDL SDL_ttf)