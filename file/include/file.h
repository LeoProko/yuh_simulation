#include <fstream>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>
#include <utility>

#include "map.h"
#include "parameters.h"

class File {
private:
    std::fstream file_;

public:
    File() = default;

    File(const std::string& file_name);

    File& operator=(File& other);

    File& operator=(File&& other);

    void print(const std::string& output);

    void print(const nlohmann::json& output);

    ~File();
};

void to_json(nlohmann::json& json_file, const Map& map);
