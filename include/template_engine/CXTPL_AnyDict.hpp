#pragma once

#include <map>
#include <string>
#include <any>

#include "I_Dict.hpp"

#if defined(CLING_IS_ON)
#include "../ClingInterpreterModule.hpp"
#endif // CLING_IS_ON

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

  void interpretToFile(const std::string &path,
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
