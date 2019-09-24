#include "make_reflect.hpp"

#include "ctp_registry.hpp"

#include <folly/logging/xlog.h>

using namespace clang;
using namespace clang::driver;
using namespace clang::tooling;
using namespace llvm;
using namespace clang::ast_matchers;
using clang::tooling::CommonOptionsParser;
using clang::tooling::Replacement;
using llvm::StringRef;

const char* typeclass_instance(
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl,
    const std::vector<cxxctp::parsed_func>& args) {
    XLOG(DBG9) << "typeclass_instance called...";

    std::map<std::string, std::any> cxtpl_params;

    std::string typeclassBaseName = get_func_arg(args, "typeclass_instance", 0);

    XLOG(DBG9) << "typeclassBaseName = " << typeclassBaseName;
    if(typeclassBaseName.empty()) {
        return "";
    }

    if(reflection::ReflectionRegistry::getInstance()->
      reflectionCXXRecordRegistry.find(typeclassBaseName)
        == reflection::ReflectionRegistry::getInstance()->reflectionCXXRecordRegistry.end())
    {
        XLOG(DBG9) << "typeclassBaseName = "
          << typeclassBaseName << " not found!";
        return "";
    }

    const reflection::ReflectionCXXRecordRegistry* ReflectedBaseTypeclass = reflection::ReflectionRegistry::getInstance()->reflectionCXXRecordRegistry[typeclassBaseName].get();

    const clang::CXXRecordDecl *node =
        matchResult.Nodes.getNodeAs<clang::CXXRecordDecl>("bind_gen");

    if (!node) {
        XLOG(DBG9) << "CXXRecordDecl not found "
                      "for typeclassBaseNode " << typeclassBaseName;
        return "";
    }

    XLOG(DBG9) << "reflect is record = " << node->getNameAsString();

    cxtpl_params.emplace("ReflectedBaseTypeclass",
                         std::make_any<reflection::ClassInfoPtr>(ReflectedBaseTypeclass->classInfoPtr_));

    cxtpl_params.emplace("ImplTypeclassName",
                         std::make_any<std::string>(node->getNameAsString()));

    cxtpl_params.emplace("BaseTypeclassName",
                         std::make_any<std::string>(ReflectedBaseTypeclass->classInfoPtr_->name));

    SourceManager &SM = rewriter.getSourceMgr();
    const auto fileID = SM.getMainFileID();
    const auto fileEntry = SM.getFileEntryForID(SM.getMainFileID());
    std::string original_full_file_path = fileEntry->getName();

    XLOG(DBG9) << "original_full_file_path = " << original_full_file_path;

    {
        std::string gen_hpp_name
            = node->getNameAsString() + ".typeclass_instance.generated.hpp";
        std::string gen_base_typeclass_hpp_name
            = ReflectedBaseTypeclass->classInfoPtr_->name + ".typeclass.generated.hpp";
        cxtpl_params.emplace("generator_path",
                             std::make_any<std::string>("typeclass_instance_gen_hpp.cxtpl"));
        cxtpl_params.emplace("generator_includes",
                             std::make_any<std::vector<std::string>>(
                                 std::vector<std::string>{
                                     /// \TODO
                                     R"raw(#include "../resources/type_erasure_common.hpp")raw",
                                     wrapLocalInclude(gen_base_typeclass_hpp_name).c_str(),
                                     wrapLocalInclude(original_full_file_path).c_str()
                                 })
                             );

        std::string cxtpl_output;

/// \note generated file
#include "../../resources/cxtpl/generated/typeclass_instance_gen_hpp.cxtpl.cpp"

        cxxctp::utils::writeToFile(cxtpl_output, gen_hpp_name);
    }
  return ""; // TODO
}
