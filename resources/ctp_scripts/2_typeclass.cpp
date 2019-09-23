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

// see https://github.com/tlatkdgus1/llvm-code_obfuscate/blob/c4d0641f95704fb9909e2ac09500df1b6bc5d017/tools/clang/lib/AST/DeclPrinter.cpp#L447
// see https://github.com/root-project/root/blob/331efa4c00fefc38980eaaf7b41b8e95fcd1a23b/interpreter/llvm/src/tools/clang/lib/AST/DeclPrinter.cpp#L474
const char* typeclass(
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl,
    const std::vector<cxxctp::parsed_func>& args) {

  reflection::NamespacesTree m_namespaces; // TODO

  printf("typeclass called...\n");

  const clang::CXXRecordDecl *node =
      matchResult.Nodes.getNodeAs<clang::CXXRecordDecl>("bind_gen");

  if (node) {
    printf("reflect is record %s\n", node->getNameAsString().c_str());

    std::map<std::string, std::any> cxtpl_params;

    {
        printf("reflector... for record %s\n", node->getNameAsString().c_str());
        reflection::AstReflector reflector(matchResult.Context);

        printf("ClassInfoPtr... for record %s\n", node->getNameAsString().c_str());
        reflection::ClassInfoPtr structInfo = reflector.ReflectClass(node, &m_namespaces);

        printf("reflectClassInfoPtr... for record %s\n", node->getNameAsString().c_str());
        //jinja2::Value reflectedJinjaClass = reflectClassInfoPtr(structInfo);
        cxtpl_params.emplace("ReflectedStructInfo",
                       std::make_any<reflection::ClassInfoPtr>(structInfo));
        std::cout << "methods: " << structInfo->methods.size() << "\n";

        for(auto mit : structInfo->methods){
            std::cout << "methods: " << mit->name << "\n";
            for(auto it : mit->params){
                std::cout << "methods params: " << it.name << it.fullDecl << "\n";
            }
        }

        printf("ReflectionRegistry... for record %s\n", node->getNameAsString().c_str());
        reflection::ReflectionRegistry::getInstance()->reflectionCXXRecordRegistry[node->getNameAsString()] = std::make_unique<reflection::ReflectionCXXRecordRegistry>(node->getNameAsString(), /*node,*/ structInfo);

      // see https://github.com/asutton/clang/blob/master/lib/AST/DeclPrinter.cpp#L502

      SourceLocation startLoc = decl->getLocStart();
      SourceLocation endLoc = decl->getLocEnd();
      clang_utils::expandLocations(startLoc, endLoc, rewriter);

      auto codeRange = SourceRange{startLoc, endLoc};

      std::string OriginalTypeclassBaseCode =
        rewriter.getRewrittenText(codeRange);

      // removes $apply(typeclass, e.t.c.)
      std::string CleanOriginalTypeclassBaseCode
        = std::regex_replace(OriginalTypeclassBaseCode,
            std::regex("\\$apply([^(]*)\\([^)]*\\)(.*)"), "$1$2");

      cxtpl_params.emplace("OriginalTypeclassBaseCode",
                           std::make_any<std::string>(CleanOriginalTypeclassBaseCode));

      cxtpl_params.emplace("GeneratedTypeclassName",
                     std::make_any<std::string>(node->getNameAsString()));

      {
        std::string gen_hpp_name
            = node->getNameAsString() + ".typeclass.generated.hpp";
        cxtpl_params.emplace("generator_path",
                       std::make_any<std::string>("typeclass_gen_hpp.cxtpl"));
        cxtpl_params.emplace("generator_includes",
                             std::make_any<std::vector<std::string>>(
                                 std::vector<std::string>{
                                     wrapLocalInclude(R"raw(../resources/type_erasure_common.hpp)raw")
                                 })
                             );

        std::string cxtpl_output;

/// \note generated file
#include "../../resources/cxtpl/generated/typeclass_gen_hpp.cxtpl.cpp"

        cxxctp::utils::writeToFile(cxtpl_output, gen_hpp_name);
      }
    }
  }

  return "";
}
