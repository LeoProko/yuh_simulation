project(map)
add_project()

target_link_libraries(${PROJECT_NAME}
    bot
    cell
    parameters
    position
)
