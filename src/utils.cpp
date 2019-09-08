#include "utils.h"

#include <string>

const std::string
getFileContent(const std::string& path)
{
    std::ifstream file(path);
    if(!file.is_open()) {
        printf("ERROR: can`t read file %s\n", path.c_str());
        return "";
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    return content;
}

void writeToFile(const std::string& str, const std::string& path) {
    std::ofstream file(path);
    if(!file.is_open()) {
        printf("ERROR: can`t write to file %s\n", path.c_str());
        return;
    }
    file << str;
    file.close();
}

std::string readWholeFile(const std::string &file_path) {
    std::ifstream file_stream(file_path, std::ios::binary);
    return std::string((std::istreambuf_iterator<char>(file_stream)),
                       std::istreambuf_iterator<char>());
}

jinja2::Value reflectClassInfoPtr(reflection::ClassInfoPtr ptr)
{
    return jinja2::Reflect(*ptr.get());
}
