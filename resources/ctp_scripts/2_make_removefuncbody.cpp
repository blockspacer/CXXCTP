#include "make_reflect.hpp"

#include "ctp_registry.hpp"

#include <folly/logging/xlog.h>

using namespace clang;
using namespace clang::driver;
using namespace clang::tooling;
using namespace llvm;
using namespace clang::ast_matchers;
using clang::tooling::CommonOptionsParser;
using clang::tooling::Replacement;
using llvm::StringRef;

const char* make_removefuncbody(
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl,
    const std::vector<cxxctp::parsed_func>& args) {
  XLOG(DBG9) << "make_removefuncbody called...";

  clang::CXXRecordDecl const *record =
      matchResult.Nodes.getNodeAs<clang::CXXRecordDecl>("bind_gen");
  if (record) {
    XLOG(DBG9) << "is record " << record->getNameAsString();
    for(auto fct = record->method_begin();
      fct!= record->method_end(); ++fct)
    {
      if(fct->hasBody() && !fct->getNameAsString().empty()) {
          XLOG(DBG9) << "INFO: removed body from function " <<
            fct->getNameAsString() << " in CXXRecordDecl " <<
              record->getNameAsString();
          rewriter.RemoveText(findFuncBodyRange(*fct, *matchResult.Context));
        }
    }
  }
  return "";
}
