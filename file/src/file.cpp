#include "file.h"

File::File(const std::string& file_name)
    : file_(file_name, file_.out) {
    if (!file_.is_open()) {
        throw std::runtime_error("Cannot open the file");
    }
}

File& File::operator=(File& other) {
    std::swap(file_, other.file_);
    return *this;
}

File& File::operator=(File&& other) {
    std::swap(file_, other.file_);
    return *this;
}

void File::print(const std::string& output) {
    file_ << output;
}

void File::print(const nlohmann::json& output) {
    file_ << output << "\n";
}

File::~File() {
    file_.close();
}

void to_json(nlohmann::json& json_file, const Map& map) {
    json_file = nlohmann::json::array();
    for (int row = 0; row < parameters::map_size; ++row) {
        nlohmann::json new_line = nlohmann::json::array();
        for (const auto& cell : map[row]) {
            new_line.push_back(cell.bot_counter_);
        }
        json_file.push_back(new_line);
    }
}
