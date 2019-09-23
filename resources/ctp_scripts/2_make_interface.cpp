#include "make_interface.hpp"

#include "src/ctp_registry.hpp"

using namespace clang;
using namespace clang::driver;
using namespace clang::tooling;
using namespace llvm;
using namespace clang::ast_matchers;
using clang::tooling::CommonOptionsParser;
using clang::tooling::Replacement;
using llvm::StringRef;

// see https://blog.jetbrains.com/clion/2017/11/towards-a-more-powerful-and-simpler-cpp-with-herb-sutter/
// see https://herbsutter.com/2017/07/26/metaclasses-thoughts-on-generative-c/
// see https://www.fluentcpp.com/2018/03/09/c-metaclasses-proposal-less-5-minutes/
const char* make_interface(
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl,
    const std::vector<cxxctp::parsed_func>& args) {
  printf("make_interface called...\n");

  clang::CXXRecordDecl const *record =
      matchResult.Nodes.getNodeAs<clang::CXXRecordDecl>("bind_gen");
  if (record) {
    printf("is record %s\n", record->getNameAsString().c_str());

    // TODO:
    // see https://stackoverflow.com/questions/24706053/how-to-find-move-constructors-in-codebase-using-clang-ast-tools/32082812#32082812
    // compiler.require(!f.is_copy() && !f.is_move(), "interfaces may not copy or move; consider a virtual clone() instead"); // 3.1

    // see https://github.com/crdelozier/ironclad/blob/master/tools/refactoring-tool/Translator.hpp#L327
    // see https://dl.khadas.com/test/github/external/v8/tools/clang/plugins/FindBadConstructsConsumer.cpp
    // see https://github.com/crosswalk-project/chromium-crosswalk/blob/master/tools/clang/plugins/FindBadConstructsConsumer.cpp
    // see https://github.com/csmith-project/creduce/blob/master/clang_delta/RemoveUnusedOuterClass.cpp#L68
    if (!record->hasUserDeclaredDestructor()) {
      printf("ERROR: found interface %s without virtual destructor\n",
        record->getNameAsString().c_str());
      //rewriter.InsertText(PureInsertionPoint,
      //  "\nvirtual ~CLASSNAME_HERE() noexcept {}\n");
    } else if (!record->getDestructor()->isVirtual()) {
      printf("ERROR: found not-virtual destructor in interface %s\n",
        record->getNameAsString().c_str());
    }

    for(auto fld = record->fields().begin();
      fld!= record->fields().end(); ++fld)
    {
        printf("ERROR: found data %s in interface %s\n",
          fld->getNameAsString().c_str(),
          record->getNameAsString().c_str());
    }


    for(auto fct = record->method_begin();
      fct!= record->method_end(); ++fct)
    {
      if(!fct->isInvalidDecl() && !fct->getNameAsString().empty()) {
        // check
        if(fct->isModulePrivate()) {
          printf("ERROR: found private function %s in interface %s\n",
            fct->getNameAsString().c_str(),
            record->getNameAsString().c_str());
        }

        // check
        if(fct->hasBody()) {
          printf("ERROR: found function %s with body in interface %s\n",
            fct->getNameAsString().c_str(),
            record->getNameAsString().c_str());
        }

        // modify
        if(!fct->isPure()) {
          //fct->setPure(true);
          printf("INFO: made pure function %s in interface %s\n",
            fct->getNameAsString().c_str(),
            record->getNameAsString().c_str());
          //clang::CXXMethodDecl f =
          //findInsertionPoint()

          clang::SourceLocation PureInsertionPoint =
              findPureInsertionPoint(*fct, *matchResult.Context);
          rewriter.InsertText(PureInsertionPoint, " = 0");
        }

        // modify
        if(!fct->isVirtual()) {
          //fct->setPure(true);
          printf("INFO: made virtual function %s in interface %s\n",
            fct->getNameAsString().c_str(),
            record->getNameAsString().c_str());
          //clang::CXXMethodDecl f =
          //findInsertionPoint()

          clang::SourceLocation VirtualInsertionPoint =
              findVirtualInsertionPoint(*fct, *matchResult.Context);
          rewriter.InsertText(VirtualInsertionPoint, "virtual ");
        }
      }
    }
  }

  clang::FieldDecl const *field =
    matchResult.Nodes.getNodeAs<clang::FieldDecl>("bind_gen");
  if (field) {
    printf("is field\n");
  }

  clang::FunctionDecl const *function =
      matchResult.Nodes.getNodeAs<clang::FunctionDecl>("bind_gen");
  if (function) {
    printf("is function\n");
  }

  return "";
}
