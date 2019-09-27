#pragma once

#include "ctp_scripts/1_utils/CXTPL_STD/CXTPL_STD.hpp"
#include "ctp_scripts/1_utils/CXXCTP_STD/CXXCTP_STD.hpp"

#include <clang/Rewrite/Core/Rewriter.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>

const char* make_removefuncbody(
    const cxxctp::parsed_func& func_with_args,
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl,
    const std::vector<cxxctp::parsed_func>& all_func_with_args);
