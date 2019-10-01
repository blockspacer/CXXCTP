#pragma once

#include "funcParser.hpp"

#include <string>
#include <vector>

#include <clang/AST/Decl.h>
#include <clang/AST/DeclBase.h>
#include <clang/AST/DeclCXX.h>
#include <clang/AST/ASTContext.h>
#include <clang/Rewrite/Core/Rewriter.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>

struct ReflectedEnumItems {
  std::string name;
  int64_t value;
};

extern std::vector<cxxctp::parsed_func> split_to_funcs(
  std::string const& inStr);

clang::SourceLocation
findPureInsertionPoint(clang::CXXMethodDecl *MethodDecl,
                   const clang::ASTContext &Context);

clang::SourceRange
findFuncBodyRange(clang::CXXMethodDecl *MethodDecl,
                   const clang::ASTContext &Context);

clang::SourceLocation
findVirtualInsertionPoint(clang::CXXMethodDecl *MethodDecl,
                   const clang::ASTContext &Context);
clang::SourceLocation
findCXXRecordNameEndPoint(clang::CXXRecordDecl const *decl,
                   const clang::ASTContext &Context);

const bool isReflectable(clang::DeclaratorDecl* decl);

std::string wrapLocalInclude(const std::string& inStr);

std::string get_func_arg(const std::vector<cxxctp::parsed_func>& args, const std::string& funcName, const int index);

cxxctp::args get_func_args(const std::vector<cxxctp::parsed_func>& args, const std::string& funcName);

void prepareTplArg(std::string& in);

///\note see cxxctp_callback
struct cxxctp_callback_args {
  const cxxctp::parsed_func& func_with_args;
  const clang::ast_matchers::MatchFinder::MatchResult& matchResult;
  clang::Rewriter& rewriter;
  const clang::Decl* decl;
  const std::vector<cxxctp::parsed_func>& all_func_with_args;
};

struct cxxctp_callback_result {
  ///\brief ay be used to replace orginal code
  const char* replacer;
};
