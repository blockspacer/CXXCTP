#include "typeclass.hpp"

#include <folly/logging/xlog.h>

#include "reflect/ReflectionCache.hpp"
#include "reflect/ReflectAST.hpp"

#include "utils.hpp"

#include "options/ctp/options.hpp"

#include <regex>

// see https://github.com/tlatkdgus1/llvm-code_obfuscate/blob/c4d0641f95704fb9909e2ac09500df1b6bc5d017/tools/clang/lib/AST/DeclPrinter.cpp#L447
// see https://github.com/root-project/root/blob/331efa4c00fefc38980eaaf7b41b8e95fcd1a23b/interpreter/llvm/src/tools/clang/lib/AST/DeclPrinter.cpp#L474
const char* typeclass(
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl,
    const std::vector<cxxctp::parsed_func>& args) {

  reflection::NamespacesTree m_namespaces; // TODO

  XLOG(DBG9) << "typeclass called...";

  const clang::CXXRecordDecl *node =
      matchResult.Nodes.getNodeAs<clang::CXXRecordDecl>("bind_gen");

  if (node) {
    XLOG(DBG9) << "reflect is record = "
      << node->getNameAsString();

    std::map<std::string, std::any> cxtpl_params;

    {
        XLOG(DBG9) << "reflector... for record "
          << node->getNameAsString();
        reflection::AstReflector reflector(matchResult.Context);

        XLOG(DBG9) << "ClassInfoPtr... for record"
          << node->getNameAsString();
        reflection::ClassInfoPtr structInfo = reflector.ReflectClass(node, &m_namespaces);

        XLOG(DBG9) << "reflectClassInfoPtr... for record"
          << node->getNameAsString();

        cxtpl_params.emplace("ReflectedStructInfo",
                       std::make_any<reflection::ClassInfoPtr>(structInfo));
        XLOG(DBG9) << "methods count: " << structInfo->methods.size();

        for(auto mit : structInfo->methods){
            std::cout << "methods: " << mit->name;
            for(auto it : mit->params){
                XLOG(DBG9) << "methods params: "
                  << it.name << it.fullDecl;
            }
        }

        XLOG(DBG9) << "ReflectionRegistry... for record" <<
          node->getNameAsString();

        reflection::ReflectionRegistry::getInstance()->reflectionCXXRecordRegistry[node->getNameAsString()] = std::make_unique<reflection::ReflectionCXXRecordRegistry>(node->getNameAsString(), /*node,*/ structInfo);

      // see https://github.com/asutton/clang/blob/master/lib/AST/DeclPrinter.cpp#L502

      clang::SourceLocation startLoc = decl->getLocStart();
      clang::SourceLocation endLoc = decl->getLocEnd();
      clang_utils::expandLocations(startLoc, endLoc, rewriter);

      auto codeRange = clang::SourceRange{startLoc, endLoc};

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
        fs::path gen_hpp_name = fs::absolute(ctp::Options::res_path
          / (node->getNameAsString() + ".typeclass.generated.hpp"));

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
#include "generated/typeclass_gen_hpp.cxtpl.cpp"

        cxxctp::utils::writeToFile(cxtpl_output, gen_hpp_name);
      }
    }
  }

  return "";
}
