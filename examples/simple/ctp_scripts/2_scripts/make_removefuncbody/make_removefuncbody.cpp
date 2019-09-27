#include "make_removefuncbody.hpp"

#include <folly/logging/xlog.h>

const char* make_removefuncbody(
    const cxxctp::parsed_func& func_with_args,
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl,
    const std::vector<cxxctp::parsed_func>& all_func_with_args) {
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
