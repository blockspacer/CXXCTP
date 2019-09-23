#include "make_reflect.hpp"

#include "src/ctp_registry.hpp"

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
  printf("make_removefuncbody called...\n");

  clang::CXXRecordDecl const *record =
      matchResult.Nodes.getNodeAs<clang::CXXRecordDecl>("bind_gen");
  if (record) {
    printf("is record %s\n", record->getNameAsString().c_str());
    for(auto fct = record->method_begin();
      fct!= record->method_end(); ++fct)
    {
      if(fct->hasBody() && !fct->getNameAsString().empty()) {
          printf("INFO: removed body from function %s in CXXRecordDecl %s\n",
            fct->getNameAsString().c_str(),
            record->getNameAsString().c_str());
          rewriter.RemoveText(findFuncBodyRange(*fct, *matchResult.Context));
        }
    }
  }
  return "";
}
