#pragma once

#include <iostream>
#include <map>
#include <string>
#include <any>
#include <vector>

template <typename M>
M GetWithDefault(const std::map<std::string, std::any>& m, const std::string& key, const M& defval) {
    auto it = m.find( key );
    if ( it == m.end() ) {
        return defval;
    } else {
        return std::any_cast<M>(it->second);
    }
}
