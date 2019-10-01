#include "typeclass_combo.hpp"

#include <folly/logging/xlog.h>

#include "reflect/ReflectionCache.hpp"
#include "reflect/ReflectAST.hpp"

#include "utils.hpp"

#include "options/ctp/options.hpp"

#include <regex>

// see https://github.com/tlatkdgus1/llvm-code_obfuscate/blob/c4d0641f95704fb9909e2ac09500df1b6bc5d017/tools/clang/lib/AST/DeclPrinter.cpp#L447
// see https://github.com/root-project/root/blob/331efa4c00fefc38980eaaf7b41b8e95fcd1a23b/interpreter/llvm/src/tools/clang/lib/AST/DeclPrinter.cpp#L474
const char* typeclass_combo(
    const cxxctp::parsed_func& func_with_args,
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl,
    const std::vector<cxxctp::parsed_func>& all_func_with_args) {

  XLOG(DBG9) << "typeclass_combo called...";

  cxxctp::args typeclassBaseNames =
    func_with_args.parsed_func_.args_;

  std::string combinedTypeclassNames;
  std::vector<std::string> typeclassNames;
  std::vector<reflection::ClassInfoPtr> ReflectedTypeclasses;
  std::vector<std::string> generator_includes;

  const size_t typeclassBaseNamesSize
    = typeclassBaseNames.as_vec_.size();

  size_t titIndex = 0;
  for(const auto& tit : typeclassBaseNames.as_vec_) {
      const std::string typeclassBaseName = tit.value_;
      XLOG(DBG9) << "typeclassBaseName = " << typeclassBaseName;
      if(typeclassBaseName.empty()) {
          return "";
      }

      if(reflection::ReflectionRegistry::getInstance()->
        reflectionCXXRecordRegistry.find(typeclassBaseName)
          == reflection::ReflectionRegistry::getInstance()->
            reflectionCXXRecordRegistry.end())
      {
          XLOG(ERR) << "typeclassBaseName = "
            << typeclassBaseName << " not found!";
          return "";
      }

      const reflection::ReflectionCXXRecordRegistry*
        ReflectedBaseTypeclass =
          reflection::ReflectionRegistry::getInstance()->
            reflectionCXXRecordRegistry[typeclassBaseName].get();

      combinedTypeclassNames += typeclassBaseName
        + (titIndex < (typeclassBaseNamesSize - 1) ? "_" : "");

      typeclassNames.push_back(typeclassBaseName);
      generator_includes.push_back(
        wrapLocalInclude(
          typeclassBaseName + R"raw(.typeclass.generated.hpp)raw"));

      /*XLOG(DBG9) << "ReflectedBaseTypeclass->classInfoPtr_->name = "
        << ReflectedBaseTypeclass->classInfoPtr_->name;
      XLOG(DBG9) << "typeclassBaseName = "
        << typeclassBaseName;*/

      XLOG(DBG9) << "ReflectedBaseTypeclass is record = "
        << ReflectedBaseTypeclass->classInfoPtr_->name;

      if(reflection::ReflectionRegistry::getInstance()->
        reflectionCXXRecordRegistry.find(typeclassBaseName)
          == reflection::ReflectionRegistry::getInstance()->
            reflectionCXXRecordRegistry.end())
      {
          XLOG(ERR) << "typeclassBaseName = "
            << typeclassBaseName << " not found!";
          return "";
      }

      ReflectedTypeclasses.push_back(
        ReflectedBaseTypeclass->classInfoPtr_);

      titIndex++;
  }

  if(typeclassNames.empty()) {
    XLOG(ERR) << "typeclassNames = empty!";
    return "";
  }

  // see https://github.com/asutton/clang/blob/master/lib/AST/DeclPrinter.cpp#L502

  clang::SourceLocation startLoc = decl->getLocStart();
  clang::SourceLocation endLoc = decl->getLocEnd();
  clang_utils::expandLocations(startLoc, endLoc, rewriter);

  auto codeRange = clang::SourceRange{startLoc, endLoc};

  std::string OriginalTypeclassBaseCode =
    rewriter.getRewrittenText(codeRange);

  // removes $apply(typeclass, e.t.c.)
  /*std::string CleanOriginalTypeclassBaseCode
    = std::regex_replace(OriginalTypeclassBaseCode,
        std::regex("\\$apply([^(]*)\\([^)]*\\)(.*)"), "$1$2");*/

  fs::path gen_hpp_name = fs::absolute(ctp::Options::res_path
    / (combinedTypeclassNames + ".typeclass_combo.generated.hpp"));

  {
    std::map<std::string, std::any> cxtpl_params;

    cxtpl_params.emplace("typeclassNames",
                   std::make_any<std::vector<std::string>>(
                    typeclassNames));

    cxtpl_params.emplace("ReflectedTypeclasses",
                   std::make_any<std::vector<reflection::ClassInfoPtr>>(
                    ReflectedTypeclasses));

    cxtpl_params.emplace("generator_path",
                   std::make_any<std::string>(
                    "typeclass_combo_gen_hpp.cxtpl"));

    generator_includes.push_back(
      wrapLocalInclude(R"raw(type_erasure_common.hpp)raw"));

    cxtpl_params.emplace("generator_includes",
                         std::make_any<std::vector<std::string>>(
                             std::move(generator_includes))
                         );

    std::string cxtpl_output;

/// \note generated file
#include "generated/typeclass_combo_gen_hpp.cxtpl.cpp"

    cxxctp::utils::writeToFile(cxtpl_output, gen_hpp_name);
  }

  {
    fs::path gen_cpp_name = fs::absolute(ctp::Options::res_path
      / (combinedTypeclassNames + ".typeclass_combo.generated.cpp"));

    std::map<std::string, std::any> cxtpl_params;

    cxtpl_params.emplace("typeclassNames",
                   std::make_any<std::vector<std::string>>(
                    typeclassNames));

    cxtpl_params.emplace("ReflectedTypeclasses",
                   std::make_any<std::vector<reflection::ClassInfoPtr>>(
                    ReflectedTypeclasses));

    cxtpl_params.emplace("generator_path",
                   std::make_any<std::string>(
                    "typeclass_combo_gen_cpp.cxtpl"));

    generator_includes.push_back(
      wrapLocalInclude(R"raw(type_erasure_common.hpp)raw"));

    generator_includes.push_back(
      wrapLocalInclude(gen_hpp_name));

    cxtpl_params.emplace("generator_includes",
                         std::make_any<std::vector<std::string>>(
                             std::move(generator_includes))
                         );

    std::string cxtpl_output;

/// \note generated file
#include "generated/typeclass_combo_gen_cpp.cxtpl.cpp"

    cxxctp::utils::writeToFile(cxtpl_output, gen_cpp_name);
  }

  return "";
}
