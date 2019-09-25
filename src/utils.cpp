#include "utils.hpp"

#include <string>
#include <fstream>

// __has_include is currently supported by GCC and Clang. However GCC 4.9 may have issues and
// returns 1 for 'defined( __has_include )', while '__has_include' is actually not supported:
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=63662
#if __has_include(<filesystem>)
#include <filesystem>
#else
#include <experimental/filesystem>
#endif // __has_include

#if __has_include(<filesystem>)
namespace fs = std::filesystem;
#else
namespace fs = std::experimental::filesystem;
#endif // __has_include

namespace cxxctp {

namespace utils {

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
    fs::create_directories(fs::path(file_path).parent_path());

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

} // namespace utils

} // namespace cxxctp
