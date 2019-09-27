#include "make_interface.hpp"

#include <folly/logging/xlog.h>

// see https://blog.jetbrains.com/clion/2017/11/towards-a-more-powerful-and-simpler-cpp-with-herb-sutter/
// see https://herbsutter.com/2017/07/26/metaclasses-thoughts-on-generative-c/
// see https://www.fluentcpp.com/2018/03/09/c-metaclasses-proposal-less-5-minutes/
const char* make_interface(
    const cxxctp::parsed_func& func_with_args,
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl,
    const std::vector<cxxctp::parsed_func>& all_func_with_args) {
  XLOG(DBG9) << "make_interface called...";

  clang::CXXRecordDecl const *record =
      matchResult.Nodes.getNodeAs<clang::CXXRecordDecl>("bind_gen");
  if (record) {
    XLOG(DBG9) << "is record " << record->getNameAsString();

    // TODO:
    // see https://stackoverflow.com/questions/24706053/how-to-find-move-constructors-in-codebase-using-clang-ast-tools/32082812#32082812
    // compiler.require(!f.is_copy() && !f.is_move(), "interfaces may not copy or move; consider a virtual clone() instead"); // 3.1

    // see https://github.com/crdelozier/ironclad/blob/master/tools/refactoring-tool/Translator.hpp#L327
    // see https://dl.khadas.com/test/github/external/v8/tools/clang/plugins/FindBadConstructsConsumer.cpp
    // see https://github.com/crosswalk-project/chromium-crosswalk/blob/master/tools/clang/plugins/FindBadConstructsConsumer.cpp
    // see https://github.com/csmith-project/creduce/blob/master/clang_delta/RemoveUnusedOuterClass.cpp#L68
    if (!record->hasUserDeclaredDestructor()) {
      XLOG(DBG9) << "ERROR: found interface without virtual destructor " <<
        record->getNameAsString();
    } else if (!record->getDestructor()->isVirtual()) {
      XLOG(DBG9) << "ERROR: found not-virtual destructor in interface" <<
        record->getNameAsString();
    }

    for(auto fld = record->fields().begin();
      fld!= record->fields().end(); ++fld)
    {
        XLOG(DBG9) << "ERROR: found data "
          << fld->getNameAsString().c_str()
          << " in interface"
          << record->getNameAsString();
    }

    for(auto fct = record->method_begin();
      fct!= record->method_end(); ++fct)
    {
      if(!fct->isInvalidDecl() && !fct->getNameAsString().empty()) {
        // check
        if(fct->isModulePrivate()) {
          XLOG(DBG9) << "ERROR: found private function "
            << fct->getNameAsString() << " in interface"
            << record->getNameAsString();
        }

        // check
        if(fct->hasBody()) {
           XLOG(DBG9) << "ERROR: found function "
             << fct->getNameAsString()
             << " with body in interface "
             << record->getNameAsString();
        }

        // modify
        if(!fct->isPure()) {
          //fct->setPure(true);
          XLOG(DBG9) << "INFO: made pure function " <<
            fct->getNameAsString() << " in interface "
            << record->getNameAsString();

          clang::SourceLocation PureInsertionPoint =
              findPureInsertionPoint(*fct, *matchResult.Context);
          rewriter.InsertText(PureInsertionPoint, " = 0");
        }

        // modify
        if(!fct->isVirtual()) {
          XLOG(DBG9) << "INFO: made virtual function "
            << fct->getNameAsString()
            << " in interface"
            << record->getNameAsString();

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
    XLOG(DBG9) << "is field";
  }

  clang::FunctionDecl const *function =
      matchResult.Nodes.getNodeAs<clang::FunctionDecl>("bind_gen");
  if (function) {
    XLOG(DBG9) << "is function";
  }

  return "";
}
