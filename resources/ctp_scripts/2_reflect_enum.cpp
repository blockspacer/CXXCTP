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

const char* reflect_enum(
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl,
    const std::vector<cxxctp::parsed_func>& args) {
  printf("reflect_enum called...\n");

  clang::EnumDecl const *node =
      matchResult.Nodes.getNodeAs<clang::EnumDecl>("bind_gen");

  if (node) {
    printf("reflect is record %s\n", node->getNameAsString().c_str());

    std::map<std::string, std::any> cxtpl_params;

    std::unordered_map<std::string, std::string> GeneratedEnumItems;

    GeneratedEnumItems.emplace("NONE", std::to_string(0));

    LangOptions LO;
    PrintingPolicy PrintPolicy(LO);
    PrintPolicy.AnonymousTagLocations = false;
    PrintPolicy.SuppressTagKeyword = true;

    PresumedLoc pLoc = node->getASTContext()
                           .getSourceManager()
                           .getPresumedLoc(node->getLocation());

    std::string nameString = node->getNameAsString();
    if(nameString.empty()) {
      printf("ERROR (reflect_enum): "
             "can`t handle enum without name [%s:%d]\n",
              pLoc.getFilename(), pLoc.getLine());
    }
    std::string typeString = "int";
    const QualType QT = node->getIntegerType();
    if(!QT.isNull()) {
      typeString = QT.getAsString(); // getTypeClassName
    }
    printf("%s : %s [%s:%d]\n",
      nameString.c_str(), typeString.c_str(),
      pLoc.getFilename(), pLoc.getLine());

    int64_t maxval = std::numeric_limits<int64_t>::min();
    for (auto iter = node->enumerator_begin();
         iter != node->enumerator_end(); iter++)
    {
        printf("    %s %ld\n", iter->getNameAsString().c_str(),
          iter->getInitVal().getExtValue());
        GeneratedEnumItems.emplace(
            iter->getNameAsString(),
            std::to_string(
                iter->getInitVal().getExtValue()));
        maxval = std::max(maxval, iter->getInitVal().getExtValue());
    }
    printf("\n");

    GeneratedEnumItems.emplace(
        "TOTAL", std::to_string(maxval + 1));

      cxtpl_params["GeneratedEnumItems"] =
        std::make_any<std::unordered_map<std::string, std::string>>(GeneratedEnumItems);
      cxtpl_params["GeneratedEnumName"] =
          std::make_any<std::string>(nameString);
      cxtpl_params["GeneratedEnumType"] =
          std::make_any<std::string>(typeString);

    std::string gen_hpp_name = node->getNameAsString() + ".enum.generated.hpp";

    {
      cxtpl_params["generator_path"] =
          std::make_any<std::string>("enum_gen_cpp.cxtpl");
      cxtpl_params["generator_includes"] =
          std::make_any<std::vector<std::string>>(
              std::vector<std::string>{
                  wrapLocalInclude(gen_hpp_name)
              });

      std::string cxtpl_output;

/// \note generated file
#include "../../resources/cxtpl/generated/enum_gen_cpp.cxtpl.cpp"

      cxxctp::utils::writeToFile(cxtpl_output, node->getNameAsString() + ".enum.generated.cpp");
    }

    {
      cxtpl_params["generator_path"] =
          std::make_any<std::string>("enum_gen_hpp.cxtpl");
      cxtpl_params["generator_includes"] =
          std::make_any<std::vector<std::string>>(
              std::vector<std::string>{});

      std::string cxtpl_output;

#include "../../resources/cxtpl/generated/enum_gen_hpp.cxtpl.cpp"

      cxxctp::utils::writeToFile(cxtpl_output, gen_hpp_name);
    }
  }

  return "";
}
