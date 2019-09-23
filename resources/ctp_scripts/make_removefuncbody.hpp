#pragma once

#include "CXTPL_STD.hpp"
#include "CXXCTP_STD.hpp"

const char* make_removefuncbody(
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl,
    const std::vector<cxxctp::parsed_func>& args);
