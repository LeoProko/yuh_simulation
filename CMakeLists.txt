cmake_minimum_required(VERSION 3.5)

project(hyu_simulation)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Werror)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

function(add_project)
    file(GLOB_RECURSE LIB_CXX_SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)
    file(GLOB_RECURSE LIB_HEADERS ${PROJECT_SOURCE_DIR}/*.h)

    add_library(
        ${PROJECT_NAME} ${LIB_CXX_SOURCES}
    )

    target_include_directories(${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include
    )
endfunction()

include(FetchContent)
FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.7.3
)
FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

add_subdirectory(bot)
add_subdirectory(cell)
add_subdirectory(file)
add_subdirectory(main)
add_subdirectory(map)
add_subdirectory(move)
add_subdirectory(parameters)
add_subdirectory(position)
add_subdirectory(run)
