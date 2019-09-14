#pragma once

#include <iostream>
#include <map>
#include <string>
#include <any>
#include <vector>

#include "../../src/reflect/ReflTypes.h"

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
