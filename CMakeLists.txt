cmake_minimum_required(VERSION 3.15)
project(fifo LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE "Debug")
add_compile_options(-Wall -Wextra -Wshadow -Wunused -Wpedantic -Wnull-dereference -Wsign-conversion)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_link_options(-fsanitize=address -fsanitize=leak -pthread)

file(GLOB sources src/*.c)

include_directories("include")


#add_compile_definitions(DEBUG_LOG)

add_executable(fifo ${sources})
