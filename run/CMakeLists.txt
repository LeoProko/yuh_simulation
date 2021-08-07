project(run)
add_project()

target_link_libraries(${PROJECT_NAME}
    bot
    file
    map
    move
    parameters
    nlohmann_json::nlohmann_json
)
