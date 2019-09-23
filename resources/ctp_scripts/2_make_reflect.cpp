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

const char* make_reflect(
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl,
    const std::vector<cxxctp::parsed_func>& args) {
  printf("make_removefuncbody called...\n");

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
    //printf("reflect is record %s\n", record->getNameAsString().c_str());

    // see https://github.com/Papierkorb/bindgen/blob/b55578e517a308778f5a510de02af499b353f15d/clang/src/record_match_handler.cpp
    for (clang::Decl *decl : record->decls()) {
      if (clang::CXXMethodDecl *method
            = llvm::dyn_cast<clang::CXXMethodDecl>(decl)) {
        //runOnMethod(method, isSignal);
        printf("reflect is CXXMethodDecl %s %s %s %s\n",
          method->getNameInfo().getName().getAsString().c_str(),
          method->getReturnType().getAsString().c_str(),
          method->getType().getUnqualifiedType().getAsString().c_str(),
          method->getNameAsString().c_str());
        if(isReflectable(method)) {
          methods[method->getNameInfo().getName().getAsString()] =
            method->getReturnType().getAsString().c_str();
        }
      } else if (clang::AccessSpecDecl *spec
                    = llvm::dyn_cast<clang::AccessSpecDecl>(decl)) {
        //isSignal = AccessSpecDecl(spec);
        //printf("is CXXMethodDecl %s\n", spec->getNameAsString().c_str());
      } else if (clang::FieldDecl *field
                    = llvm::dyn_cast<clang::FieldDecl>(decl)) {
        //runOnField(field);
        printf("reflect is FieldDecl %s %s\n",
          field->getType().getUnqualifiedType().getAsString().c_str(),
          field->getNameAsString().c_str());
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
