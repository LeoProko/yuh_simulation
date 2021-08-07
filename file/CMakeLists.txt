project(file)
add_project()

target_link_libraries(${PROJECT_NAME}
    map
    nlohmann_json::nlohmann_json
    parameters
)
