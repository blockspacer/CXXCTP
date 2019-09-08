#include "clangUtils.h"

std::string printMethodDecl(const clang::Decl* decl, clang::CXXRecordDecl const * node, CXXMethodDecl* fct) {
    std::string methodDecl;
    FunctionDecl *D = fct->getAsFunction();

    bool isCtor = llvm::dyn_cast_or_null<const clang::CXXConstructorDecl>(fct) != nullptr;
    bool isDtor = llvm::dyn_cast_or_null<const clang::CXXDestructorDecl>(fct) != nullptr;
    bool isOperator = fct->isOverloadedOperator();

    if(isCtor || isDtor || isOperator) {
        return "";
    }

    printf("called printMethodDecl\n");

    printf("found function %s in CXXRecordDecl %s\n",
           fct->getNameAsString().c_str(),
           node->getName().str().c_str());

    // TODO: https://stackoverflow.com/questions/56792760/how-to-get-the-actual-type-of-a-template-typed-class-member-with-clang/56796422#56796422https://stackoverflow.com/questions/56792760/how-to-get-the-actual-type-of-a-template-typed-class-member-with-clang/56796422#56796422
    if(fct->isTemplateDecl()) {
        /*  //FunctionTemplateDecl * FTD = fct->getDescribedFunctionTemplate();
    FunctionTemplateDecl *FTD =
     dyn_cast<FunctionTemplateDecl>(D->getFriendDecl())
  if (const FunctionDecl *FD = D->getTemplateSpecializationInfo()platedDecl()) {
   for (unsigned I = 0,
        NumTemplateParams = FD->getNumTemplateParameterLists();
        I < NumTemplateParams; ++I)
  printTemplateParameters(FD->getTemplateParameterList(I));
      methodDecl += " template<";
      fct->getTemplateParameterList()
      methodDecl += " template>";
    }*/
    }

    auto ctor = llvm::dyn_cast_or_null<
        const clang::CXXConstructorDecl>(decl);
    if (ctor != nullptr)
    {
        if(ctor->isExplicit()) {
            methodDecl += " explicit ";
        }
    }

    if(fct->isVirtual()) {
        methodDecl += " virtual ";
    }

    if(fct->isConstexpr()) {
        methodDecl += " constexpr ";
    }

    if(fct->isStatic()) {
        methodDecl += " static ";
    }

    methodDecl += " " + fct->getReturnType().getAsString() + " ";

    //printf("%s", methodDecl.c_str());

    methodDecl += " __" + fct->getNameAsString() + " ";

    //printf("%s", methodDecl.c_str());

    unsigned Indentation = 0;
    //bool PrintInstantiation = false;
    LangOptions LO;
    PrintingPolicy PrintPolicy(LO);
    //PrintPolicy.AnonymousTagLocations = false;
    //PrintPolicy.SuppressTagKeyword = true;

    methodDecl += " ( ";
    // prams | join(', ')
    std::string Proto;
    llvm::raw_string_ostream POut(Proto);

    // see https://github.com/flexferrum/flex_lib/blob/322adb7acdfbc0e541292708a2bd66b305b05c52/tools/codegen/src/ast_reflector.cpp#L174
    int pc = 0;
    for (auto param = D->param_begin(); param != D->param_end(); ++param)
    {
        if(param) {
            auto nextparam = param + 1;
            std::string result;
            llvm::raw_string_ostream os(result);
            (*param)->print(os, PrintPolicy);
            methodDecl += result;

            methodDecl += os.str();

            /*methodDecl += param->getType().getAsString() + " ";
        methodDecl += param->getNameAsString() + " ";*/

            if(nextparam && nextparam != D->param_end()/*pc && pc <= D->getNumParams()*/) {
                methodDecl += ", ";
            }

            //paramInfo.type = TypeInfo::Create(param->getType(), m_astContext);
            //paramInfo.fullDecl = EntityToString(param, m_astContext);
            //methodInfo->params.push_back(std::move(paramInfo));
            pc++;
        }
    }

    methodDecl += " ) ";

    //printf("%s", methodDecl.c_str());

    if(fct->isConst()) {
        methodDecl += " const ";
    }

    // see https://github.com/flexferrum/autoprogrammer/blob/db902121dd492a2df2b7287e0dafd7173062bcc7/src/ast_reflector.cpp#L386
    QualType fnQualType = fct->getType();

    const FunctionProtoType* fnProtoType = nullptr;
    if (const clang::FunctionType *fnType =
            fnQualType->getAs<clang::FunctionType>())
    {
        if (D->hasWrittenPrototype())
            fnProtoType = llvm::dyn_cast<FunctionProtoType>(fnType);
    }

    // see https://github.com/FunkMonkey/libClang/blob/ab4702febef82409773f7c80ec02d53ddbb4d80e/lib/AST/DeclPrinter.cpp#L468
    if(isNoexceptExceptionSpec(fnProtoType->getExceptionSpecType())) {
        methodDecl += " noexcept ";
    }

    if(fct->isPure()) {
        methodDecl += " = 0 ";
    }

    if(fct->isDeleted()) {
        methodDecl += " = delete ";
    }

    if(fct->isDefaulted()) {
        methodDecl += " = default ";
    }

    if(fct->isDefined() && fct->hasBody()) {
        std::string Proto;
        llvm::raw_string_ostream Out(Proto);
        fct->getBody()->
            printPretty(Out, 0, PrintPolicy, Indentation);
        methodDecl += Out.str();
    }

    //methodDecl += "\n";

    printf("%s\n", methodDecl.c_str());

    return methodDecl;
}

void expandLocations(SourceLocation& startLoc,
                     SourceLocation& endLoc,
                     Rewriter& rewriter_) {
    if( startLoc.isMacroID() ) {
        // Get the start/end expansion locations
        std::pair< SourceLocation, SourceLocation > expansionRange =
            rewriter_.getSourceMgr().getImmediateExpansionRange( startLoc );

        // We're just interested in the start location
        startLoc = expansionRange.first;
        endLoc = expansionRange.second;
    }
}
