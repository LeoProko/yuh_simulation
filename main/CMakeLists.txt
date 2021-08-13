project(main)

file(GLOB_RECURSE sources ${PROJECT_SOURCE_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME}
    parameters
    run
)
