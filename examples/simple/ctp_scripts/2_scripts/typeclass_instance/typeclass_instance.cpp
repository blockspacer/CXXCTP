#include "typeclass_instance.hpp"

#include <folly/logging/xlog.h>

#include "reflect/ReflectionCache.hpp"
#include "reflect/ReflectAST.hpp"

#include "utils.hpp"

#include "options/ctp/options.hpp"

#include <algorithm>
#include <string>

const char* typeclass_instance(
    const cxxctp::parsed_func& func_with_args,
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl,
    const std::vector<cxxctp::parsed_func>& all_func_with_args) {
    XLOG(DBG9) << "typeclass_instance called...";

    cxxctp::args typeclassBaseNames =
      func_with_args.parsed_func_.args_;

    std::string targetName;

    const clang::CXXRecordDecl *node =
        matchResult.Nodes.getNodeAs<clang::CXXRecordDecl>("bind_gen");

    if (node) {
        targetName = node->getNameAsString();
    }

    for(const auto& tit : typeclassBaseNames.as_vec_) {
      if(tit.name_ =="target") {
        targetName = tit.value_;
        prepareTplArg(targetName);
      }
    }

    if (targetName.empty()) {
        XLOG(ERR) << "target for typeclass instance not found ";
        return "";
    }

    for(const auto& tit : typeclassBaseNames.as_vec_) {
      if(tit.name_ =="target") {
        continue;
      }

      std::map<std::string, std::any> cxtpl_params;

      std::string typeclassBaseName = tit.value_;
      prepareTplArg(typeclassBaseName);

      XLOG(DBG9) << "typeclassBaseName = " << typeclassBaseName;
      XLOG(DBG9) << "target = " << targetName;

      if(typeclassBaseName.empty()) {
          return "";
      }

      if(reflection::ReflectionRegistry::getInstance()->
        reflectionCXXRecordRegistry.find(typeclassBaseName)
          == reflection::ReflectionRegistry::getInstance()->
            reflectionCXXRecordRegistry.end())
      {
          XLOG(ERR) << "ERROR: typeclassBaseName = "
            << typeclassBaseName << " not found!";
          return "";
      }

      const reflection::ReflectionCXXRecordRegistry*
        ReflectedBaseTypeclass =
          reflection::ReflectionRegistry::getInstance()->
            reflectionCXXRecordRegistry[typeclassBaseName].get();

      /*XLOG(DBG9) << "ReflectedBaseTypeclass->classInfoPtr_->name = "
        << ReflectedBaseTypeclass->classInfoPtr_->name;
      XLOG(DBG9) << "typeclassBaseName = "
        << typeclassBaseName;*/

      cxtpl_params.emplace("ImplTypeclassName",
                           std::make_any<std::string>(
                            targetName));

      cxtpl_params.emplace("BaseTypeclassName",
                           std::make_any<std::string>(
                            typeclassBaseName));

        cxtpl_params.emplace("ReflectedBaseTypeclass",
                             std::make_any<reflection::ClassInfoPtr>(
                              ReflectedBaseTypeclass->classInfoPtr_));

      clang::SourceManager &SM = rewriter.getSourceMgr();
      const auto fileID = SM.getMainFileID();
      const auto fileEntry = SM.getFileEntryForID(SM.getMainFileID());
      std::string original_full_file_path = fileEntry->getName();

      XLOG(DBG9) << "original_full_file_path = "
        << original_full_file_path;

      {
          std::string fileTypeclassBaseName = typeclassBaseName;
          cxtpl_utils::prepareFileName(fileTypeclassBaseName);

          fs::path gen_hpp_name = fs::absolute(ctp::Options::res_path
            / (targetName + "_" + fileTypeclassBaseName
              + ".typeclass_instance.generated.hpp"));

          fs::path gen_base_typeclass_hpp_name =
            fs::absolute(ctp::Options::res_path
              / (fileTypeclassBaseName
                + ".typeclass.generated.hpp"));

          cxtpl_params.emplace("generator_path",
                               std::make_any<std::string>(
                               "typeclass_instance_gen_hpp.cxtpl"));
          cxtpl_params.emplace("generator_includes",
                               std::make_any<std::vector<std::string>>(
                                   std::vector<std::string>{
                                       /// \TODO
                                       R"raw(#include "type_erasure_common.hpp")raw",
                                       wrapLocalInclude(
                                        gen_base_typeclass_hpp_name),
                                       wrapLocalInclude(
                                        original_full_file_path)
                                   })
                               );

          std::string cxtpl_output;

  /// \note generated file
  #include "generated/typeclass_instance_gen_hpp.cxtpl.cpp"

          cxxctp::utils::writeToFile(cxtpl_output, gen_hpp_name);
      }
    }

  return ""; // TODO
}
