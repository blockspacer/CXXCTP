#pragma once

#include "ctp_scripts/1_utils/CXTPL_STD/CXTPL_STD.hpp"
#include "ctp_scripts/1_utils/CXXCTP_STD/CXXCTP_STD.hpp"

#include <clang/Rewrite/Core/Rewriter.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>

cxxctp_callback_result make_interface(
    const cxxctp_callback_args& callback_args);
