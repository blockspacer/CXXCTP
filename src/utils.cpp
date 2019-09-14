#include "utils.h"

#include <string>

const std::string
getFileContent(const std::string& path)
{
    std::ifstream file(path);
    if(!file.is_open()) {
        // TODO: better error reporting
        printf("ERROR: can`t read file %s\n", path.c_str());
        return "";
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    return content;
}

void writeToFile(const std::string& str, const std::string& file_path) {
    std::ofstream ofs(file_path);
    if(!ofs) {
        // TODO: better error reporting
        printf("ERROR: can`t write to file %s\n", file_path.c_str());
        return;
    }
    ofs << str;
    ofs.close();
    if(!ofs)    //bad() function will check for badbit
    {
        printf("ERROR: writing to file failed %s\n", file_path.c_str());
        return;
    }
}

std::string readWholeFile(const std::string &file_path) {
    std::ifstream file_stream(file_path, std::ios::binary);
    if(!file_stream.is_open()) {
        // TODO: better error reporting
        printf("ERROR: can`t read from file %s\n", file_path.c_str());
        return "";
    }
    return std::string((std::istreambuf_iterator<char>(file_stream)),
                       std::istreambuf_iterator<char>());
}
