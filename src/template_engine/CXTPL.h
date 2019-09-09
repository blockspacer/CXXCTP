#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <streambuf>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <functional>
#include <unordered_map>
#include <map>
#include <condition_variable>
#include <cstdio>
#include <functional>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>
//#include <filesystem>
#include <memory>
#include <numeric>
#include <string_view>
#include <optional>
#include <condition_variable>
// Standard includes
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <iterator>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <streambuf>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <functional>
#include <unordered_map>
#include <map>
#include <condition_variable>
#include <cstdio>
#include <functional>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

#include "../utils.h"
#include "../DispatchQueue.h"

#include "../funcParser.h"
#include "../inputThread.h"
#include "../clangUtils.h"
#include "../clangPipeline.h"
#include "../ClingInterpreterModule.h"

#define ARG_REF_TO_CLING(varType, varName) argRefToCling(varType, #varName, (varName))

class CXTPL {
 public:
  typedef std::function<void(std::unique_ptr<std::string> res)> interp_callback;

  void createFromFile(const std::string& path);

  void createFromString(const std::string& code);

  void buildToFile(const std::string& path);

  void loadBuiltFromString(const string &code);

  void loadBuiltFromFile(const string &path);

  std::string buildToString();

  /*std::unique_ptr<std::string> interpretToString(
    bool& bVar, bool& cVar, std::vector<std::string>& carNames);*/

  void interpretToFile(const string &path,
    bool& bVar, bool& cVar, std::vector<std::string>& carNames);

  /*std::unique_ptr<std::string> compileToString(
    bool& bVar, bool& cVar, std::vector<std::string>& carNames);

  void compileToFile(const std::string& path,
    bool& bVar, bool& cVar, std::vector<std::string>& carNames);*/

 private:
  void rebuild();

  std::string loadClingArgs(bool& bVar, bool& cVar,
    std::vector<std::string>& carNames);

  // TODO: WASM & Node.js support
  // TODO: filtering
  // TODO: parse-time code exec
  // TODO: both runtime cling exec & native compile run support
  // TODO: error reporting with line numbers
  // TODO: unit tests
  // TODO: open/close tag customization
  // TODO: refactor
  // TODO: multithreaded transpiling of templates
  // TODO: docs, sanitize, iwyu, examples, CI/CD
  // TODO: support library, ranges-style
  // TODO: similar projects
  // + https://github.com/burner/sweet.hpp/tree/master/amber
  // TODO: example with includes workaround
  // TODO: example with external function call workaround
  std::string buildFromString(const std::string& input);

  template <typename T>
  std::string argRefToCling(const std::string varType,
      const std::string varName, const T& arg) {
    std::ostringstream sstr;
    sstr << " ; \n const " << varType << " & " << varName << " = ";
    sstr << "*(const " << varType << "*)("
            // Pass a pointer into cling as a string.
         << std::hex << std::showbase
         << reinterpret_cast<size_t>(&arg) << "); \n";
    return sstr.str();
  }

  // see
  // https://bits.theorem.co/how-to-write-a-template-library/
  // https://lambda.xyz/blog/maud-is-fast/
  // https://dzone.com/articles/modern-type-safe-template-engines
  // http://www.wilxoft.com/
  // https://github.com/djc/askama
  // https://www.reddit.com/r/rust/comments/b06z9m/cuach_a_compiletime_html_template_system/
  std::string prepareForCling(const std::string& input/*, const std::string& clinja_args*/);

  void runInInterpreter(
    const interp_callback& callback,  const std::string& inStr,
    bool& bVar, bool& cVar, std::vector<std::string>& carNames);

  std::string code_before_build_;
  std::string code_after_build_;
  std::string code_for_cling_after_build_;
};
