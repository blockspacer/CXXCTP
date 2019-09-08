#pragma once

#include <fstream>
#include <string>

#include "reflect/jinja2_reflection.h"

const std::string
getFileContent(const std::string& path);

std::string readWholeFile(const std::string& file_path);

void writeToFile(const std::string& str, const std::string& path);

jinja2::Value reflectClassInfoPtr(reflection::ClassInfoPtr);
