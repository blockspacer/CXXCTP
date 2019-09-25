#include "reflect_enum.hpp"

#include <folly/logging/xlog.h>

#include "utils.hpp"

#include "options/ctp/options.hpp"

const char* reflect_enum(
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl,
    const std::vector<cxxctp::parsed_func>& args) {
  XLOG(DBG9) << "reflect_enum called...";

  clang::EnumDecl const *node =
      matchResult.Nodes.getNodeAs<clang::EnumDecl>("bind_gen");

  if (node) {
    XLOG(DBG9) << "reflect is record" << node->getNameAsString();

    std::map<std::string, std::any> cxtpl_params;

    std::unordered_map<std::string, std::string> GeneratedEnumItems;

    GeneratedEnumItems.emplace("NONE", std::to_string(0));

    clang::LangOptions LO;
    clang::PrintingPolicy PrintPolicy(LO);
    PrintPolicy.AnonymousTagLocations = false;
    PrintPolicy.SuppressTagKeyword = true;

    clang::PresumedLoc pLoc = node->getASTContext()
                           .getSourceManager()
                           .getPresumedLoc(node->getLocation());

    std::string nameString = node->getNameAsString();
    if(nameString.empty()) {
      XLOG(DBG9) << "ERROR (reflect_enum): "
             "can`t handle enum without name [" <<
             pLoc.getFilename() << ", " << pLoc.getLine() << "]";
    }
    std::string typeString = "int";
    const clang::QualType QT = node->getIntegerType();
    if(!QT.isNull()) {
      typeString = QT.getAsString(); // getTypeClassName
    }
    XLOG(DBG9) << nameString << " : " << typeString
      << " [" << pLoc.getFilename() << ":" << pLoc.getLine() << "]";

    int64_t maxval = std::numeric_limits<int64_t>::min();
    for (auto iter = node->enumerator_begin();
         iter != node->enumerator_end(); iter++)
    {
        XLOG(DBG9) << "    " << iter->getNameAsString() << " " <<
          iter->getInitVal().getExtValue();
        GeneratedEnumItems.emplace(
            iter->getNameAsString(),
            std::to_string(
                iter->getInitVal().getExtValue()));
        maxval = std::max(maxval, iter->getInitVal().getExtValue());
    }

    GeneratedEnumItems.emplace(
        "TOTAL", std::to_string(maxval + 1));

      cxtpl_params["GeneratedEnumItems"] =
        std::make_any<std::unordered_map<std::string, std::string>>(GeneratedEnumItems);
      cxtpl_params["GeneratedEnumName"] =
          std::make_any<std::string>(nameString);
      cxtpl_params["GeneratedEnumType"] =
          std::make_any<std::string>(typeString);

    fs::path gen_hpp_name = fs::absolute(ctp::Options::res_path
      / (node->getNameAsString() + ".enum.generated.hpp"));

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
#include "generated/enum_gen_cpp.cxtpl.cpp"

    fs::path gen_cpp_name = fs::absolute(ctp::Options::res_path
      / (node->getNameAsString() + ".enum.generated.cpp"));

      cxxctp::utils::writeToFile(cxtpl_output, gen_cpp_name);
    }

    {
      cxtpl_params["generator_path"] =
          std::make_any<std::string>("enum_gen_hpp.cxtpl");
      cxtpl_params["generator_includes"] =
          std::make_any<std::vector<std::string>>(
              std::vector<std::string>{});

      std::string cxtpl_output;

#include "generated/enum_gen_hpp.cxtpl.cpp"

      cxxctp::utils::writeToFile(cxtpl_output, gen_hpp_name);
    }
  }

  return "";
}
