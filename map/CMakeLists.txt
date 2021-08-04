project(map)

file(GLOB_RECURSE LIB_CXX_SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE LIB_HEADERS ${PROJECT_SOURCE_DIR}/*.h)

add_library(${PROJECT_NAME} ${LIB_CXX_SOURCES})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    bot
    cell
    position
    rand
)
