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
#include <any>

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

#include "I_Dict.hpp"
#include "../utils.hpp"
#include "../DispatchQueue.hpp"

#include "../funcParser.hpp"
#include "../inputThread.hpp"
#include "../clangUtils.hpp"
#include "../clangPipeline.hpp"
#include "../ClingInterpreterModule.hpp"

#define ARG_REF_TO_CLING(varType, varName) argRefToCling(varType, #varName, (varName))

namespace cxtpl_util {

struct AnyDict {
  std::map<std::string, std::any> cxtpl_params;
};

template<>
class Dict<AnyDict> : public I_Dict {
 public:
  ~Dict<AnyDict>();

  /*std::unique_ptr<std::string> interpretToString(
    bool& bVar, bool& cVar, std::vector<std::string>& carNames);*/

  void interpretToFile(const string &path,
                       const std::map<std::string, std::any>& cxtpl_params,
                       const std::string &includes_code);

  /*std::unique_ptr<std::string> compileToString(
    bool& bVar, bool& cVar, std::vector<std::string>& carNames);*/

  /*void compileToFile(const std::string& path,
    const std::map<std::string, std::any>& cxtpl_params);*/

 private:

  std::string loadClingArgs(const std::string& appende,
                            const std::map<std::string, std::any>& cxtpl_params);

  void runInInterpreter(
    const interp_callback& callback,  const std::string& inStr,
    const std::map<std::string, std::any>& cxtpl_params,
    const std::string &includes_code);
};

} // namespace cxtpl_util
