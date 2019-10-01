#include "typeclass.hpp"

#include <folly/logging/xlog.h>

#include "reflect/ReflectionCache.hpp"
#include "reflect/ReflectAST.hpp"

#include "utils.hpp"

#include "options/ctp/options.hpp"

#include <regex>

// see https://github.com/tlatkdgus1/llvm-code_obfuscate/blob/c4d0641f95704fb9909e2ac09500df1b6bc5d017/tools/clang/lib/AST/DeclPrinter.cpp#L447
// see https://github.com/root-project/root/blob/331efa4c00fefc38980eaaf7b41b8e95fcd1a23b/interpreter/llvm/src/tools/clang/lib/AST/DeclPrinter.cpp#L474
cxxctp_callback_result typeclass(
  const cxxctp_callback_args& callback_args) {

  XLOG(DBG9) << "typeclass called...";

  cxxctp::args typeclassBaseNames =
    callback_args.func_with_args.parsed_func_.args_;

  const clang::CXXRecordDecl *node1 =
    callback_args.matchResult.Nodes.getNodeAs<
      clang::CXXRecordDecl>("bind_gen");

  if (!node1) {
      XLOG(ERR) << "CXXRecordDecl not found ";
      return cxxctp_callback_result{""};
  }

  /*std::string targetName = node1->getNameAsString();

  for(const auto& tit : typeclassBaseNames.as_vec_) {
    if(tit.name_ =="target") {
      targetName = tit.value_;
    }
  }*/

  reflection::NamespacesTree m_namespaces; // TODO

  std::string fullBaseType;

  if (node1) {
      reflection::AstReflector reflector(
        callback_args.matchResult.Context);

      std::vector<clang::CXXRecordDecl *> nodes;
      std::vector<reflection::ClassInfoPtr> structInfos;
      reflection::ClassInfoPtr structInfo;

      for(const auto& it : node1->bases()) {
        //node = it.getType()->getAsCXXRecordDecl();//<clang::RecordDecl>();

        if(it.getType()->getAsCXXRecordDecl()) {
          nodes.push_back(
            it.getType()->getAsCXXRecordDecl());

          const auto refled
            = reflector.ReflectClass(
              it.getType()->getAsCXXRecordDecl(),
              &m_namespaces, false);

          structInfos.push_back(refled);

          if(!structInfo) {
            structInfo = refled;
          } else {
            for(const auto& it : refled->members) {
              structInfo->members.push_back(it);
            }
            for(const auto& it : refled->methods) {
              structInfo->methods.push_back(it);
            }
            for(const auto& it : refled->innerDecls) {
              structInfo->innerDecls.push_back(it);
            }
          }

          std::string preparedFullBaseType
            = it.getType().getAsString();
          cxtpl_utils::prepareTypeName(
            preparedFullBaseType);

          structInfo->compoundId.push_back(
            preparedFullBaseType);

          fullBaseType += preparedFullBaseType;
          fullBaseType += ",";
          //break;
        }
      }

      // remove last comma
      if (!fullBaseType.empty()) {
        fullBaseType.pop_back();
      }

      if(nodes.empty() || structInfos.empty()
         || !structInfo) {
        return cxxctp_callback_result{""};
      }

/*if(node1->getDescribedClassTemplate())
    XLOG(DBG9) << "reflectTpl is record = "
      << node->getDescribedClassTemplate()->getDeclName().getAsString();
*/
    {
        /*XLOG(DBG9) << "reflector... for record "
          << node->getNameAsString();

        XLOG(DBG9) << "ClassInfoPtr... for record"
          << node->getNameAsString();

        XLOG(DBG9) << "reflectClassInfoPtr... for record"
          << node->getNameAsString();*/

        /*for(auto mit : structInfo->methods){
            XLOG(DBG9) << "methods: " << mit->name;
            for(auto it : mit->params){
                XLOG(DBG9) << "methods params: "
                  << it.name << it.fullDecl;
            }
        }*/

        XLOG(DBG9) << "ReflectionRegistry... for record " <<
          fullBaseType;

        reflection::ReflectionRegistry::getInstance()->
          reflectionCXXRecordRegistry[fullBaseType]
            = std::make_unique<
                reflection::ReflectionCXXRecordRegistry>(
                  fullBaseType, /*node,*/ structInfo);

        XLOG(DBG9) << "templateParams.size"
          << structInfo->templateParams.size();
        XLOG(DBG9) << "genericParts.size"
          << structInfo->genericParts.size();
#if 0
        /*XLOG(DBG9) << "getDepth"
          << structInfo->
          decl->getTypeForDecl()->
          getAs<clang::TemplateTypeParmType>()->getDepth();*/
       //XLOG(DBG9) << "getDepth" << TemplateParameterList(0).;

        XLOG(DBG9) << "getDeclName"
          << structInfo->decl->
            getQualifiedNameAsString();


        if(structInfo->decl->getDescribedClassTemplate()) {

          XLOG(DBG9) << "getDescribedClassTemplate"
            << structInfo->decl->
              getQualifiedNameAsString();
          clang::TemplateDecl* templateDecl =
            structInfo->decl->getDescribedClassTemplate();
          std::string tmpl="<";
          clang::TemplateParameterList *tp =
            templateDecl->getTemplateParameters();
          for(clang::NamedDecl *p: *tp) {
              //cout << "  TMPL " << get_template_type(p) << " " << get_template_name(p) << endl;
              if (tmpl.size()>1) tmpl = tmpl+",";
              tmpl = tmpl+"TMPL_"+p->getNameAsString();
          XLOG(DBG9) << "p->getNameAsString() "
            << p->getNameAsString();
              //if (templateCodeTemp.size()>0) templateCodeTemp = templateCodeTemp+", ";
              //templateCodeTemp = templateCodeTemp+get_template_type(p)+" TMPL_"+get_template_name(p);
          }
          tmpl = tmpl+">";
        }
#endif
 /* clang::TypeAliasDecl const *TemplateType =
      structInfo->decl->getTypeForDecl()
      ->getAs<clang::TypeAliasDecl>();
  if (TemplateType) {
    XLOG(DBG9) << "TemplateType";
  }*/


       /*if(!structInfo->decl->isCompleteDefinition()) {
          for (clang::CXXRecordDecl::base_class_const_iterator I
                = structInfo->decl->bases_begin(),
            E = structInfo->decl->bases_end(); I != E; ++I) {
            const clang::CXXBaseSpecifier *BS = I;
            const clang::Type *Ty = BS->getType().getTypePtr();
            const clang::TemplateTypeParmType *ParmTy
              = Ty->getAs<clang::TemplateTypeParmType>();
            if (!ParmTy)
              continue;
            const clang::TemplateTypeParmDecl *ParmD =
              ParmTy->getDecl();
            XLOG(DBG9) << "Parameters"
              << ParmD->getNameAsString();
          }
       }*/

       /*TypeInfo::Create(structInfo->decl->getTypeForDecl(),
        m_astContext);*/

      // see https://github.com/asutton/clang/blob/master/lib/AST/DeclPrinter.cpp#L502

      /*clang::SourceLocation startLoc = decl->getLocStart();
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
                     std::make_any<std::string>(node->getNameAsString()));*/

      std::string fileTargetName = fullBaseType;
      cxtpl_utils::prepareFileName(fileTargetName);

      fs::path gen_hpp_name = fs::absolute(
        ctp::Options::res_path
        / (fileTargetName + ".typeclass.generated.hpp"));

      fs::path gen_cpp_name = fs::absolute(
        ctp::Options::res_path
        / (fileTargetName + ".typeclass.generated.cpp"));

      {
        clang::SourceManager &SM
          = callback_args.rewriter.getSourceMgr();
        const auto fileID = SM.getMainFileID();
        const auto fileEntry = SM.getFileEntryForID(
          SM.getMainFileID());
        std::string full_file_path = fileEntry->getName();
        XLOG(DBG9) << "full_file_path is "
          << full_file_path;

        std::map<std::string, std::any> cxtpl_params;

        cxtpl_params.emplace("ReflectedStructInfo",
                       std::make_any<
                        reflection::ClassInfoPtr>(structInfo));
        //XLOG(DBG9) << "methods count: " << structInfo->methods.size();

        cxtpl_params.emplace("fullBaseType",
                       std::make_any<std::string>(
                        fullBaseType));

        cxtpl_params.emplace("generator_path",
                       std::make_any<std::string>(
                        "typeclass_gen_hpp.cxtpl"));
        cxtpl_params.emplace("generator_includes",
                             std::make_any<
                               std::vector<std::string>>(
                                 std::vector<std::string>{
                                     wrapLocalInclude(
                                      full_file_path),
                                     wrapLocalInclude(
                                      R"raw(type_erasure_common.hpp)raw")
                                 })
                             );

        std::string cxtpl_output;

/// \note generated file
#include "generated/typeclass_gen_hpp.cxtpl.cpp"

        cxxctp::utils::writeToFile(cxtpl_output, gen_hpp_name);
      }

      {
        std::map<std::string, std::any> cxtpl_params;

        cxtpl_params.emplace("ReflectedStructInfo",
                       std::make_any<
                        reflection::ClassInfoPtr>(structInfo));
        //XLOG(DBG9) << "methods count: " << structInfo->methods.size();

        cxtpl_params.emplace("fullBaseType",
                       std::make_any<
                        std::string>(fullBaseType));

        cxtpl_params.emplace("generator_path",
                       std::make_any<
                        std::string>("typeclass_gen_cpp.cxtpl"));
        cxtpl_params.emplace("generator_includes",
                             std::make_any<
                               std::vector<std::string>>(
                                 std::vector<std::string>{
                                     wrapLocalInclude(
                                      gen_hpp_name),
                                     wrapLocalInclude(
                                      R"raw(type_erasure_common.hpp)raw")
                                 })
                             );

        std::string cxtpl_output;

/// \note generated file
#include "generated/typeclass_gen_cpp.cxtpl.cpp"

        cxxctp::utils::writeToFile(cxtpl_output, gen_cpp_name);
      }
    }
  }

  return cxxctp_callback_result{""};
}
