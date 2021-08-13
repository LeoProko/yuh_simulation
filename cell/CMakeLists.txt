project(cell)
add_project()

target_link_libraries(${PROJECT_NAME}
    bot
    parameters
    position
    ${CMAKE_THREAD_LIBS_INIT}
)
