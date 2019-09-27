#include "make_reflect.hpp"

#include <folly/logging/xlog.h>

/// \note that example used
const char* make_reflect(
    const cxxctp::parsed_func& func_with_args,
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl,
    const std::vector<cxxctp::parsed_func>& all_func_with_args) {
  XLOG(DBG9) << "make_removefuncbody called...";

  std::string indent = "  ";
  std::string output{};
  output.append("\n");
  output.append(indent
                  + "public:");
  indent.append("  ");
  output.append("\n");

  std::map<std::string, std::string> fields;
  std::map<std::string, std::string> methods;

  clang::CXXRecordDecl const *record =
      matchResult.Nodes.getNodeAs<clang::CXXRecordDecl>("bind_gen");
  if (record) {
    XLOG(DBG9) << "reflect is record " << record->getNameAsString().c_str();

    // see https://github.com/Papierkorb/bindgen/blob/b55578e517a308778f5a510de02af499b353f15d/clang/src/record_match_handler.cpp
    for (clang::Decl *decl : record->decls()) {
      if (clang::CXXMethodDecl *method
            = llvm::dyn_cast<clang::CXXMethodDecl>(decl)) {
        //runOnMethod(method, isSignal);
        XLOG(DBG9) << "reflect is CXXMethodDecl " <<
          method->getNameInfo().getName().getAsString().c_str() << " " <<
          method->getReturnType().getAsString().c_str() << " " <<
          method->getType().getUnqualifiedType().getAsString().c_str() << " " <<
          method->getNameAsString().c_str();
        if(isReflectable(method)) {
          methods[method->getNameInfo().getName().getAsString()] =
            method->getReturnType().getAsString().c_str();
        }
      } else if (clang::AccessSpecDecl *spec
                    = llvm::dyn_cast<clang::AccessSpecDecl>(decl)) {
        //isSignal = AccessSpecDecl(spec);
        //XLOG(DBG9) << ("is CXXMethodDecl %s\n", spec->getNameAsString().c_str());
      } else if (clang::FieldDecl *field
                    = llvm::dyn_cast<clang::FieldDecl>(decl)) {
        //runOnField(field);
        XLOG(DBG9) << "reflect is FieldDecl" <<
          field->getType().getUnqualifiedType().getAsString().c_str() << " " <<
          field->getNameAsString().c_str();
        if(isReflectable(field)) {
          fields[field->getNameAsString()] =
            field->getType().getUnqualifiedType().getAsString().c_str();
        }
      }
    }

    // TODO: use template

    output.append(indent
                    + "static std::map<std::string, std::string> fields");
    output.append(" = {");
    output.append("\n");
    for(const auto& [key, value] : fields) {
      output.append(indent
                      + indent + "{ ");
      output.append("\"" + key + "\"");
      output.append(", ");
      output.append("\"" + value + "\"");
      output.append(" }");
      output.append("\n");
    }
    output.append("\n");
    output.append(indent
                  + "};");
    output.append("\n");
    // methods
    output.append("\n");
    output.append(indent
                    + "static std::map<std::string, std::string> methods");
    output.append(" = {");
    output.append("\n");
    for(const auto& [key, value] : methods) {
      output.append(indent + indent
                      + "{ ");
      output.append("\"" + key + "\"");
      output.append(", ");
      output.append("\"" + value + "\"");
      output.append(" }");
      output.append("\n");
    }
    output.append("\n");
    output.append(indent +
                    "};");
    output.append("\n");
    auto locEnd = record->getLocEnd();
    rewriter.InsertText(locEnd, output,
      /*InsertAfter=*/true, /*IndentNewLines*/ false);
  }
  return "";
}
