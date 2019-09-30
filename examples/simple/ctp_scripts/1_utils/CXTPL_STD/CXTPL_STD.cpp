#include "CXTPL_STD.hpp"

#include <folly/logging/xlog.h>

#include <clang/AST/DeclTemplate.h>

#include <string_view>

namespace cxtpl_utils {

static bool startsWith(const std::string_view& in,
    const std::string& prefix) {
  return !in.compare(0, prefix.size(), prefix);
};

static std::string_view removePrefix(const std::string_view& from,
    const std::string& prefix) {
  return from.substr( prefix.size(), from.size() - prefix.size());
};

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

std::string typenameParamsFullDecls(
  const std::vector<reflection::MethodParamInfo>& params)
{
    std::string out;
    size_t paramIter = 0;
    const size_t methodParamsSize = params.size();
    for(const auto& param: params) {
      paramIter++;
      if(param.type->getAsTemplateParamType()) {
        out += "typename ";
        //out += param.type->getPrintedName();
        out += param.type
          ->getAsTemplateParamType()->decl->getName();
        if(paramIter != methodParamsSize) {
            out += ", ";
        } // paramIter != methodParamsSize
      }
    } // params endfor
    return out;
}

std::string paramsFullDecls(
  const std::vector<reflection::MethodParamInfo>& params)
{
    std::string out;
    size_t paramIter = 0;
    const size_t methodParamsSize = params.size();
    for(const auto& param: params) {
      out += param.fullDecl;
      /*if(param.type->getAsTemplate()
        || param.type->getAsTemplateParamType()) {
        out += " typename ";
      }*/
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

std::string typeclassModelName(const std::string& arg) {
  return "model_for_" + arg;
}

std::string typeclassModelsDecls(
  const std::vector<std::string>& params)
{
    /*const std::string comboType =
      typeclassComboDecls(params);*/
    std::string out;
    for(const auto& param: params) {
      out += "\n"
             "std::shared_ptr<_tc_model_t<";
      out += param;
      out += ">> ";
      out += typeclassModelName(param);
      out += ";"
             "\n";
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

void prepareFileName(std::string &in)
{
  std::replace_if(in.begin(), in.end(), ::ispunct, '_');
  std::replace_if(in.begin(), in.end(), ::isspace, '_');
}

void prepareTypeName(std::string &in)
{
  {
    const std::string prefix = "struct ";
    if(startsWith(in, prefix)) {
      in = removePrefix(in, prefix);
    }
  }
  {
    const std::string prefix = "record ";
    if(startsWith(in, prefix)) {
      in = removePrefix(in, prefix);
    }
  }
}

} // namespace cxtpl_utils

#if defined(CLING_IS_ON)
void CXTPL_STD(){}
#endif
