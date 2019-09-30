#pragma once

#include <iostream>
#include <map>
#include <string>
#include <any>
#include <vector>

#include "reflect/ReflTypes.hpp"

namespace cxtpl_utils {

template <typename M>
M GetWithDefault(const std::map<std::string, std::any>& m, const std::string& key, const M& defval) {
    auto it = m.find( key );
    if ( it == m.end() ) {
        return defval;
    } else {
        return std::any_cast<M>(it->second);
    }
}

std::string startHeaderGuard(const std::string& guardName);

std::string endHeaderGuard(const std::string& guardName);

std::string paramsFullDecls(const std::vector<reflection::MethodParamInfo>& params);

std::string paramsCallDecls(const std::vector<reflection::MethodParamInfo>& params);

std::string templateParamsFullDecls(const std::vector<reflection::TemplateParamInfo>& params);

std::string typeclassModelName(const std::string& arg);

std::string typeclassComboDecls(const std::vector<std::string>& params);

std::string typeclassModelsDecls(const std::vector<std::string>& params);

std::string typenameParamsFullDecls(
  const std::vector<reflection::MethodParamInfo>& params);

void prepareFileName(std::string& in);

void prepareTypeName(std::string& in);

} // namespace cxtpl_utils
