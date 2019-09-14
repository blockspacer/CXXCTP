#include "CXTPL_STD.h"

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

std::string paramsFullDecls(const std::vector<reflection::MethodParamInfo>& params)
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

std::string paramsCallDecls(const std::vector<reflection::MethodParamInfo>& params)
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

std::string templateParamsFullDecls(const std::vector<reflection::TemplateParamInfo>& params)
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
