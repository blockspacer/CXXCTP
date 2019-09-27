#include "CXTPL_STD.hpp"

#include <folly/logging/xlog.h>

namespace cxtpl_utils {

std::string startHeaderGuard(const std::string& guardName) {
    std::string out;
    if(!guardName.empty()) {
        out += "#ifndef ";
        out += guardName;
        out += "\n";
        out += "#define ";
        out += guardName;
        out += "\n";
    } else {
        out += "#pragma once\n";
    } // !guardName.empty()
    return out;
}

std::string endHeaderGuard(const std::string& guardName) {
    std::string out;
    if(!guardName.empty()) {
        out += "#endif // ";
        out += guardName;
        out += "\n";
    }
    return out;
}

#if defined(CLING_IS_ON)
void CXTPL_STD() {
    printf("loaded CXTPL_STD with CLING\n");
}
#endif // CLING_IS_ON

std::string paramsFullDecls(
  const std::vector<reflection::MethodParamInfo>& params)
{
    std::string out;
    size_t paramIter = 0;
    const size_t methodParamsSize = params.size();
    for(const auto& param: params) {
      out += param.fullDecl;
      paramIter++;
      if(paramIter != methodParamsSize) {
          out += ", ";
      } // paramIter != methodParamsSize
    } // params endfor
    return out;
}

std::string paramsCallDecls(
  const std::vector<reflection::MethodParamInfo>& params)
{
    std::string out;
    size_t paramIter = 0;
    const size_t methodParamsSize = params.size();
    for(const auto& param: params) {
        out += param.name;
        paramIter++;
        if(paramIter != methodParamsSize) {
            out += ", ";
        } // paramIter != methodParamsSize
    } // params endfor
    return out;
}

std::string templateParamsFullDecls(
  const std::vector<reflection::TemplateParamInfo>& params)
{
    std::string out;
    size_t paramIter = 0;
    const size_t methodParamsSize = params.size();
    for(const auto& param: params) {
        out += param.tplDeclName;
        paramIter++;
        if(paramIter != methodParamsSize) {
            out += ", ";
        } // paramIter != methodParamsSize
    } // params endfor
    return out;
}

static std::string typeclassModelName(const std::string& arg) {
  return "model_for_" + arg;
}

std::string typeclassModelsDecls(
  const std::vector<std::string>& params)
{
    /*const std::string comboType =
      typeclassComboDecls(params);*/
    std::string out;
    size_t paramIter = 0;
    const size_t methodParamsSize = params.size();
    for(const auto& param: params) {
        paramIter++;
        if(paramIter != methodParamsSize) {
            out += "std::shared_ptr<_tc_model_t<";
            out += param;
            out += ">> ";
            out += typeclassModelName(param);
            out += "; ";
        } // paramIter != methodParamsSize
    } // params endfor
    return out;
}

std::string typeclassReplaceModelsDecls(
  const std::vector<std::string>& params)
{
    /*const std::string comboType =
      typeclassComboDecls(params);*/
    std::string out;
    size_t paramIter = 0;
    const size_t methodParamsSize = params.size();
    for(const auto& param: params) {
        paramIter++;
        if(paramIter != methodParamsSize) {
            out += R"raw(
  template<
  typename T,
  typename std::enable_if<std::is_same<
            )raw";
            out += param;
            out += R"raw(, T>::value>::type* = nullptr
  >
  void replace_model(
    const std::shared_ptr<_tc_model_t<)raw";
            out += param;
            out += R"raw(>> rhs) noexcept {
)raw";
            out += typeclassModelName(param);
            out += R"raw( = rhs;
  }
            )raw";
        } // paramIter != methodParamsSize
    } // params endfor
    return out;
}

std::string typeclassComboDecls(const std::vector<std::string>& params)
{
    std::string out;
    size_t paramIter = 0;
    const size_t methodParamsSize = params.size();
    for(const auto& param: params) {
        out += param;
        paramIter++;
        if(paramIter != methodParamsSize) {
            out += ", ";
        } // paramIter != methodParamsSize
    } // params endfor
    return out;
}

} // namespace cxtpl_utils

#if defined(CLING_IS_ON)
void CXTPL_STD(){}
#endif
