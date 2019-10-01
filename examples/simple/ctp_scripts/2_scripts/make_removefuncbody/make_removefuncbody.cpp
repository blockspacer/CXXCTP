#include "make_removefuncbody.hpp"

#include <folly/logging/xlog.h>

cxxctp_callback_result make_removefuncbody(
  const cxxctp_callback_args& callback_args) {

  XLOG(DBG9) << "make_removefuncbody called...";

  clang::CXXRecordDecl const *record =
    callback_args.matchResult.Nodes.getNodeAs<
      clang::CXXRecordDecl>("bind_gen");

  if (record) {
    XLOG(DBG9) << "is record " << record->getNameAsString();
    for(auto fct = record->method_begin();
      fct!= record->method_end(); ++fct)
    {
      if(fct->hasBody() && !fct->getNameAsString().empty()) {
          XLOG(DBG9) << "INFO: removed body from function " <<
            fct->getNameAsString() << " in CXXRecordDecl " <<
              record->getNameAsString();
          callback_args.rewriter.RemoveText(
            findFuncBodyRange(*fct,
              *callback_args.matchResult.Context));
        }
    }
  }
  return cxxctp_callback_result{""};
}
