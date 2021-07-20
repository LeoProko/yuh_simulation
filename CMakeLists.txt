cmake_minimum_required(VERSION 3.5)

project(hyu_simulation CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Werror)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

add_subdirectory(cell)
add_subdirectory(genes)
add_subdirectory(map)
add_subdirectory(position)
