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

const char* typeclass_instance(
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl,
    const std::vector<cxxctp::parsed_func>& args) {
    printf("typeclass_instance called...\n");

    std::map<std::string, std::any> cxtpl_params;

    std::string typeclassBaseName = get_func_arg(args, "typeclass_instance", 0);

    printf("typeclassBaseName = %s...\n", typeclassBaseName.c_str());
    if(typeclassBaseName.empty()) {
        return "";
    }

    if(reflection::ReflectionRegistry::getInstance()->
      reflectionCXXRecordRegistry.find(typeclassBaseName)
        == reflection::ReflectionRegistry::getInstance()->reflectionCXXRecordRegistry.end())
    {
        printf("typeclassBaseName = %s not found!\n", typeclassBaseName.c_str());
        return "";
    }

    const reflection::ReflectionCXXRecordRegistry* ReflectedBaseTypeclass = reflection::ReflectionRegistry::getInstance()->reflectionCXXRecordRegistry[typeclassBaseName].get();

    const clang::CXXRecordDecl *node =
        matchResult.Nodes.getNodeAs<clang::CXXRecordDecl>("bind_gen");

    if (!node) {
        printf("CXXRecordDecl not found for typeclassBaseNode = %s!\n", typeclassBaseName.c_str());
        return "";
    }

    printf("reflect is record %s\n", node->getNameAsString().c_str());

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

    std::cout << "original_full_file_path is " << original_full_file_path << "\n";

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
