project(move)

file(GLOB_RECURSE LIB_CXX_SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE LIB_HEADERS ${PROJECT_SOURCE_DIR}/*.h)

add_library(${PROJECT_NAME} ${LIB_CXX_SOURCES})
add_library(sub::map ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    bot
    map
    parameters
)
