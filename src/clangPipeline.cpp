#include "clangPipeline.hpp"

#include "DispatchQueue.hpp"

#include "funcParser.hpp"

#include "clangUtils.hpp"

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

namespace clang_utils {

static std::map<std::string, cxxctp_callback> cxxctp_callbacks;

void add_cxxctp_callback(const std::string& id, const cxxctp_callback& func) {
    cxxctp_callbacks[id] = func;
}

cxxctp_callback get_cxxctp_callback(const std::string& id) {
    auto it = cxxctp_callbacks.find( id );
    if ( it == cxxctp_callbacks.end() ) {
        return nullptr;
    }
    return cxxctp_callbacks[id];
}
/*OPTIONS:

Generic Options:

  -help                      - Display available options (-help-hidden for more)
  -help-list                 - Display list of available options (-help-list-hidden for more)
  -version                   - Display the version of this program

Use override options:

  -extra-arg=<string>        - Additional argument to append to the compiler command line
  -extra-arg-before=<string> - Additional argument to prepend to the compiler command line
  -p=<string>                - Build path*/
void add_default_clang_args(std::vector<string> &args)
{
    args.push_back("clang_app");
    //args.push_back("-extra-arg=-nostdinc");

    //args.push_back("-DCLANG_ENABLED=1");
    args.push_back("-extra-arg=-DCLANG_ENABLED=1");

    // https://stackoverflow.com/a/30877725
    args.push_back("-extra-arg=-DBOOST_SYSTEM_NO_DEPRECATED");
    args.push_back("-extra-arg=-DBOOST_ERROR_CODE_HEADER_ONLY");

    // TODO: custom paths
    args.push_back("-extra-arg=-I../cling-build/build/lib/clang/5.0.0/include");
    args.push_back("-extra-arg=-I../cling-build/src/include/");
    args.push_back("-extra-arg=-I../cling-build/build/include/");
    args.push_back("-extra-arg=-I../cling-build/src/tools/clang/include/");
    args.push_back("-extra-arg=-I../cling-build/build/tools/clang/include/");
    args.push_back("-extra-arg=-I../cling-build/src/tools/cling/include/");

    args.push_back("-extra-arg=-std=c++17");
    //args.push_back("-extra-arg=--std=c++2a");
    //args.push_back("-extra-arg=-fmodules-ts");

    //args.push_back("-extra-arg=-I/usr/local/tander/i586-pc-linux-gnu/usr/include/");

    /*
    args.push_back("-extra-arg=-I../resources");
    args.push_back("-p=\".\""); // Build path

    // TODO: crash when changed order, may be thread race
    args.push_back("../resources/ReflShapeKind.hpp");
    args.push_back("../resources/test_typeclass_base1.hpp");
    args.push_back("../resources/test_typeclass_instance1.hpp");
    args.push_back("../resources/test.cpp");
*/

    //args.push_back("-help");
}

#if defined(CLING_IS_ON)

void callModuleFunc(const UseOverride::Checker::MatchResult& Result,
                    clang::Rewriter &rewriter_,
                    const clang::Decl* decl,
                    const std::string& func_to_call,
                    const std::vector<cxxctp::parsed_func>& parsedFuncs) {
    std::ostringstream sstr;
    // scope begin
    sstr << "[](){";
    sstr << "return ";
    // func begin
    sstr << func_to_call << "( ";
    // func arguments
    sstr << "*(const clang::ast_matchers::MatchFinder::MatchResult*)("
         // Pass a pointer into cling as a string.
         << std::hex << std::showbase
         << reinterpret_cast<size_t>(&Result) << ')';
    sstr << " , "; // next argument
    sstr << "*(clang::Rewriter*)("
         // Pass a pointer into cling as a string.
         << std::hex << std::showbase
         << reinterpret_cast<size_t>(&rewriter_) << ')';
    sstr << " , "; // next argument
    sstr << "(const clang::Decl*)("
         // Pass a pointer into cling as a string.
         << std::hex << std::showbase
         << reinterpret_cast<size_t>(decl) << ')';
    sstr << " , "; // next argument
    sstr << "*(std::vector<cxxctp::parsed_func>*)("
         // Pass a pointer into cling as a string.
         << std::hex << std::showbase
         << reinterpret_cast<size_t>(&parsedFuncs) << ')';
    // func end
    sstr << " );" << ";";
    // scope end
    sstr << "}();";
    if(cling_utils::InterpreterModule::interpMap.find("main_module")
        != cling_utils::InterpreterModule::interpMap.end()) {
        cling::Interpreter::CompilationResult compilationResult;
        cling_utils::InterpreterModule::interpMap["main_module"]->metaProcessor_->process(
            sstr.str(), compilationResult, nullptr, true);
    }
}

#else

void callModuleFunc(const UseOverride::Checker::MatchResult& Result,
                    clang::Rewriter &rewriter_,
                    const clang::Decl* decl,
                    const std::string& func_to_call,
                    const std::vector<cxxctp::parsed_func>& parsedFuncs) {
    printf("callModuleFunc %s\n", func_to_call.c_str());
    /*llvm::outs() << "!callModuleFunc: "
                 << func_to_call << "\n";*/
    auto func_cxxctp = get_cxxctp_callback(func_to_call);
    if(func_cxxctp) {
        func_cxxctp(Result, rewriter_, decl, parsedFuncs);
    }
}

#endif // CLING_IS_ON

void UseOverride::Checker::run(const UseOverride::Checker::MatchResult& Result) {
    //llvm::outs() << "match1 = " << "\n";

    /*auto any_decl = Result.Nodes.getNodeAs<clang::NamedDecl>( "any_decl" );
    if(any_decl && !any_decl->isInvalidDecl()
       && any_decl->getIdentifier()) {
      llvm::outs() << "any_decl = " << any_decl->getName().str() << "\n";
    }
    auto any_decl = Result.Nodes.getNodeAs<clang::Decl>( "any_decl" );
    if(any_decl && !any_decl->isInvalidDecl()
       && any_decl->getKind()) {
      llvm::outs() << "any_decl = " << any_decl->getDeclKindName()<< "\n";
    }*/

    /*auto any_decl2 = Result.Nodes.getNodeAs<clang::PragmaCommentDecl>( "any_decl" );
    if(any_decl2) {
      llvm::outs() << "any_decl2 = "
        << any_decl2->getArg().str() << " " << any_decl2->getDeclKindName() << "\n";
    }*/

    /*auto any_decl2 = Result.Nodes.getNodeAs<clang::OMPParallelForDirective>( "any_decl" );
    if(any_decl2) {
      llvm::outs() << "any_decl2 = "
        << any_decl2->getStmtClassName() << "\n";
    }*/

    if ( const clang::Decl* decl = Result.Nodes.getNodeAs<clang::Decl>( "bind_gen" ) )
    {
        if ( decl && !decl->isInvalidDecl())
            if (auto annotate = decl->getAttr<clang::AnnotateAttr>()) {
                llvm::outs() << "annotate->getAnnotation()"
                             << annotate->getAnnotation().str() << "\n";
                // {gen};{codegen};
                const std::string gen_token = "{gen};";
                const bool startsWithGen =
                        annotate->getAnnotation().str().rfind(gen_token, 0) == 0;
                std:: string code =
                        annotate->getAnnotation().str();
                code.erase(0, gen_token.size());

                // eval
                const std::string eval_token = "{eval};";
                bool isEval = false;
                const bool startsWithEval =
                        code.rfind(eval_token, 0) == 0;
                if (startsWithEval) {
                    code.erase(0, eval_token.size());
                    isEval = true;
                }

                // export
                const std::string export_token = "{export};";
                bool isExport = false;
                const bool startsWithExport =
                        code.rfind(export_token, 0) == 0;
                if (startsWithExport) {
                    code.erase(0, export_token.size());
                    isExport = true;
                }

                // embed
                const std::string embed_token = "{embed};";
                bool isEmbed = false;
                const bool startsWithEmbed =
                        code.rfind(embed_token, 0) == 0;
                if (startsWithEmbed) {
                    code.erase(0, embed_token.size());
                    isEmbed = true;
                }

                // codegen
                const std::string codegen_token = "{codegen};";
                const bool startsWithCodegen =
                        code.rfind(codegen_token, 0) == 0;
                bool isFuncCall = false;
                std::vector<std::string> funcs_to_call;
                if (startsWithGen && startsWithCodegen) {
                    code.erase(0, codegen_token.size());
                    isFuncCall = true;
                    funcs_to_call.push_back("call_codegen");
                }

                const std::string funccall_token = "{funccall};";
                const bool startsWithFunccall =
                        code.rfind(funccall_token, 0) == 0;

                std::vector<cxxctp::parsed_func> parsedFuncs;
                if (startsWithGen && startsWithFunccall) {
                    code.erase(0, funccall_token.size());
                    parsedFuncs = cxxctp::split_to_funcs(code);
                    for (auto const& seg : parsedFuncs) {
                        llvm::outs() << "segment: " << seg.func_with_args_as_string_ << "\n";
                        llvm::outs() << "funcs_to_call1  func_name_: " << seg.parsed_func_.func_name_ << "\n";

                        if(!seg.parsed_func_.func_name_.empty()) {
                            funcs_to_call.push_back(seg.parsed_func_.func_name_);
                        }

                        for (auto const& arg : seg.parsed_func_.args_.as_vec_) {
                            llvm::outs() << "    arg name: " << arg.name_ << "\n";
                            llvm::outs() << "    arg value: " << arg.value_ << "\n";
                        }
                        for (auto const& [key, values] : seg.parsed_func_.args_.as_name_to_value_) {
                            llvm::outs() << "    arg key: " << key << "\n";
                            llvm::outs() << "    arg values (" << values.size() <<"): " << "\n";
                            for (auto const& val : values) {
                                llvm::outs() << "        " << val << "\n";
                            }
                        }
                        llvm::outs() << "\n";
                    }
                    isFuncCall = true;
                    /*std::string delimiter = ";";
          size_t pos = 0;
          std::string token;
          while ((pos = code.find(delimiter)) != std::string::npos) {
            token = code.substr(0, pos);
            if(!token.empty()) {
              funcs_to_call.push_back(token);
            }
            code.erase(0, pos + delimiter.length());
          }
          if(!code.empty()) {
            funcs_to_call.push_back(code);
          }*/
                }

                if(isEmbed) {
                    llvm::outs() << "embed for code: "
                                 << code << "\n";
#if defined(CLING_IS_ON)
                    std::ostringstream sstr;
                    // scope begin
                    sstr << "[](){";
                    // vars begin
                    sstr << "const clang::ast_matchers::MatchFinder::MatchResult& clangMatchResult = ";
                    sstr << "*(const clang::ast_matchers::MatchFinder::MatchResult*)("
                            // Pass a pointer into cling as a string.
                         << std::hex << std::showbase
                         << reinterpret_cast<size_t>(&Result) << ");";
                    sstr << "clang::Rewriter& clangRewriter = ";
                    sstr << "*(clang::Rewriter*)("
                            // Pass a pointer into cling as a string.
                         << std::hex << std::showbase
                         << reinterpret_cast<size_t>(&rewriter_) << ");";
                    sstr << "const clang::Decl* clangDecl = ";
                    sstr << "(const clang::Decl*)("
                            // Pass a pointer into cling as a string.
                         << std::hex << std::showbase
                         << reinterpret_cast<size_t>(decl) << ");";
                    // vars end
                    sstr << "return ";
                    sstr << code << ";";
                    // scope end
                    sstr << "}();";
                    cling::Value result;
                    if(cling_utils::InterpreterModule::interpMap.find("main_module") != cling_utils::InterpreterModule::interpMap.end()) {
                        cling::Interpreter::CompilationResult compilationResult;
                        cling_utils::InterpreterModule::interpMap["main_module"]->metaProcessor_->process(
                                    sstr.str(), compilationResult, &result, true);
                    }
                    SourceLocation startLoc = decl->getLocStart();
                    SourceLocation endLoc = decl->getLocEnd();

                    /*if( endLoc.isMacroID() ) {
              // Get the start/end expansion locations
              std::pair< SourceLocation, SourceLocation > expansionRange =
                       rewriter_.getSourceMgr().getImmediateExpansionRange( endLoc );

                        // We're just interested in the start location
                        endLoc = expansionRange.first;
                    }*/

                    /*;
          rewriter_.InsertText(startLoc, " startLoc ");
          rewriter_.InsertText(endLoc, " endLoc ");*/

                    clang_utils::expandLocations(startLoc, endLoc, rewriter_);

                    void* resOptionVoid = result.getAs<void*>();
                    auto resOption =
                      static_cast<llvm::Optional<std::string>*>(resOptionVoid);
                    if(resOption) {
                      if(resOption->hasValue()) {
                          rewriter_.ReplaceText(
                                      SourceRange(startLoc, endLoc),
                                      resOption->getValue());
                      }
                      delete resOption; /// \note frees resOptionVoid memory
                    }
#endif // CLING_IS_ON
                } else if(isEval) {
                    llvm::outs() << "eval for code: "
                                 << code << "\n";
#if defined(CLING_IS_ON)
                    std::ostringstream sstr;
                    sstr << code;
                    if(cling_utils::InterpreterModule::interpMap.find("main_module") != cling_utils::InterpreterModule::interpMap.end()) {
                        cling::Interpreter::CompilationResult compilationResult;
                        cling_utils::InterpreterModule::interpMap["main_module"]->metaProcessor_->process(
                                    sstr.str(), compilationResult, nullptr, true);
                    }
                    SourceLocation startLoc = decl->getLocStart();
                    SourceLocation endLoc = decl->getLocEnd();

                    /*if( endLoc.isMacroID() ) {
              // Get the start/end expansion locations
              std::pair< SourceLocation, SourceLocation > expansionRange =
                       rewriter_.getSourceMgr().getImmediateExpansionRange( endLoc );

                    // We're just interested in the start location
                    endLoc = expansionRange.first;
                }*/


                    /*rewriter_.InsertText(startLoc, " 1startLoc ");
          rewriter_.InsertText(endLoc, " 1endLoc ");*/

                    clang_utils::expandLocations(startLoc, endLoc, rewriter_);

                    /*rewriter_.InsertText(startLoc, " 2startLoc ");
          rewriter_.InsertText(endLoc, " 2endLoc ");*/

                    rewriter_.ReplaceText(
                                SourceRange(startLoc, endLoc),
                                "");
#endif // CLING_IS_ON
                } else if(isExport) {
                    llvm::outs() << "export for code: "
                                 << code << "\n";
#if defined(CLING_IS_ON)
                    std::ostringstream sstr;
                    sstr << code;
                    if(cling_utils::InterpreterModule::interpMap.find("main_module") != cling_utils::InterpreterModule::interpMap.end()) {
                        cling::Interpreter::CompilationResult compilationResult;
                        cling_utils::InterpreterModule::interpMap["main_module"]->metaProcessor_->process(
                                    sstr.str(), compilationResult, nullptr, true);
                    }
                    SourceLocation startLoc = decl->getLocStart();
                    SourceLocation endLoc = decl->getLocEnd();

                    /*if( endLoc.isMacroID() ) {
              // Get the start/end expansion locations
              std::pair< SourceLocation, SourceLocation > expansionRange =
                       rewriter_.getSourceMgr().getImmediateExpansionRange( endLoc );

            // We're just interested in the start location
            endLoc = expansionRange.first;
        }*/

                    /*rewriter_.InsertText(startLoc, " 1startLoc ");
          rewriter_.InsertText(endLoc, " 1endLoc ");*/

                    clang_utils::expandLocations(startLoc, endLoc, rewriter_);

                    /*rewriter_.InsertText(startLoc, " 2startLoc ");
          rewriter_.InsertText(endLoc, " 2endLoc ");*/

                    const std::string export_start_token = "$export";


                    ASTContext *Context = Result.Context;
                    // find '('
                    auto l_paren_loc = clang::Lexer::findLocationAfterToken(
                                startLoc.getLocWithOffset(export_start_token.length() - 1),
                                clang::tok::l_paren,
                                Context->getSourceManager(),
                                Context->getLangOpts(),
                                /*skipWhiteSpace=*/true);

                    rewriter_.ReplaceText(
                                SourceRange(
                                    startLoc,
                                    l_paren_loc
                                    ),
                                "");
                    const std::string export_end_token = ")";
                    rewriter_.ReplaceText(
                                SourceRange(
                                    endLoc,
                                    endLoc.getLocWithOffset(export_end_token.length())
                                    ),
                                "");
                    /*rewriter_.ReplaceText(
            SourceRange(startLoc, endLoc),
            code);*/
#endif // CLING_IS_ON
                } else if(isFuncCall) {

                    // Generate bindings for a decl with pyspot annotation
                    //generate_bindings( *decl );
                    llvm::outs() << "generator for code: "
                                 << code << "\n";

                    //receivedMessagesQueue_->dispatch([] {
                    for (const std::string& func_to_call : funcs_to_call) {
                        llvm::outs() << "main_module task " << func_to_call << "!... " << '\n';
                        callModuleFunc(Result, rewriter_, decl, func_to_call, parsedFuncs);
                    }
                }
            }
    }
}

UseOverride::Consumer::Consumer(Rewriter &Rewriter)
    : Checker_(Rewriter) {
    using namespace clang::ast_matchers;
    //const auto CXXMethodMatcher =
    //    cxxMethodDecl(unless(isExpansionInSystemHeader())).bind("target");
    //Finder_.addMatcher(CXXMethodMatcher, &Checker_);
    //const auto CXXAnythingMatcher = anything();
    /*Finder_.addMatcher(
      callExpr(callee(functionDecl(hasName("doSomething")))),
      &Checker_);*/
    /*Finder_.addMatcher(
      callExpr(callee(cxxMethodDecl(hasName("doSomething")))),
      &Checker_);*/
    /*Finder_.addMatcher(
      callExpr(hasDeclaration(functionDecl(hasName("#gen"))))
        .bind("call"),
      &Checker_);*/
    /*Finder_.addMatcher(
      callExpr(hasDeclaration(functionDecl(hasName("#gen"))))
        .bind("call"),
      &Checker_);*/
    /*Finder_.addMatcher(
      cxxRecordDecl(hasName("#gen"))
        .bind("call"),
      &Checker_);*/
    // https://stackoverflow.com/questions/38067137/is-there-any-way-to-restart-matching-with-libclang-matchers-after-already-havi
    /*Finder_.addMatcher(
      namedDecl(hasAttr(attr::Annotate))
        .bind("call"),
      &Checker_);*/
    //Finder_.addMatcher(clang::ast_matchers::decl(anything()).bind( "any_decl" ), &Checker_);
    /*const clang::ast_matchers::internal::VariadicDynCastAllOfMatcher<
        clang::Stmt, clang::OMPParallelForDirective> // CapturedStmt
        CapturedStmtDirective;
    Finder_.addMatcher(CapturedStmtDirective().bind( "any_decl" ), &Checker_);
    */

    /*typedef internal::Matcher<Decl> DeclarationMatcher;
typedef internal::Matcher<Stmt> StatementMatcher;
typedef internal::Matcher<QualType> TypeMatcher;
typedef internal::Matcher<TypeLoc> TypeLocMatcher;
typedef internal::Matcher<NestedNameSpecifier> NestedNameSpecifierMatcher;
typedef internal::Matcher<NestedNameSpecifierLoc> NestedNameSpecifierLocMatcher;
typedef internal::Matcher<CXXCtorInitializer> CXXCtorInitializerMatcher;*/
    //Finder_.addMatcher(clang::ast_matchers::stmt(anything()), &Checker_);
    //Finder_.addMatcher(clang::ast_matchers::decl(anything()), &Checker_);
    //Finder_.addMatcher(clang::ast_matchers::type(anything()), &Checker_);
    //Finder_.addMatcher(clang::ast_matchers::loc(anything()), &Checker_);
    //Finder_.addMatcher(clang::ast_matchers::nestedNameSpecifier(anything()), &Checker_);
    //Finder_.addMatcher(clang::ast_matchers::nestedNameSpecifierLoc(anything()), &Checker_);

    // TODO enumConstantDecl

    // https://github.com/Fahien/pywrap/blob/d753603bfd26c02382ebd9729f07b5d78f2d96a2/src/Consumer.cpp
    auto hasAnnotate = clang::ast_matchers::hasAttr( clang::attr::Annotate );
    auto finderMatcher = clang::ast_matchers::decl( hasAnnotate ).bind( "bind_gen" );
    Finder_.addMatcher(finderMatcher, &Checker_);
    //Finder_.addMatcher(asmStmt().bind("bind_gen"), &Checker_);
    //Finder_.addMatcher(cxxConstructExpr().bind("bind_gen"), &Checker_);
    //Finder_.addMatcher(predefinedExpr().bind("bind_gen"), &Checker_);
}

void UseOverride::Consumer::HandleTranslationUnit(ASTContext &Context) {
    Finder_.matchAST(Context);
}

UseOverride::Action::ASTConsumerPointer UseOverride::Action::CreateASTConsumer(CompilerInstance &Compiler, StringRef) {
    Rewriter.setSourceMgr(Compiler.getSourceManager(), Compiler.getLangOpts());
    return std::make_unique<Consumer>(Rewriter);
}

bool UseOverride::Action::BeginSourceFileAction(CompilerInstance &) {
    llvm::errs() << "Processing " << getCurrentFile() << "\n\n";
    return true;
}

void UseOverride::Action::EndSourceFileAction() {
    ASTFrontendAction::EndSourceFileAction();

    SourceManager &SM = Rewriter.getSourceMgr();

    const auto fileID = SM.getMainFileID();
    const auto fileEntry = SM.getFileEntryForID(SM.getMainFileID());
    std::string full_file_path = fileEntry->getName();
    llvm::outs() << "full_file_path is " << full_file_path << "\n";
    const std::string filename = fs::path(full_file_path).filename();
    llvm::outs() << "filename is " << filename << "\n";

    llvm::outs() << "** EndSourceFileAction for: "
                 << fileEntry->getName().str() << "\n";
    const std::string full_file_ext = fs::path(full_file_path).extension();
    const std::string out_path = filename + ".generated" + full_file_ext;

    bool shouldFlush = true;
#if 0
    if (shouldFlush) {
        std::error_code OutErrInfo;
        std::error_code ok;

        llvm::raw_fd_ostream outputFile(llvm::StringRef(full_file_path),
                                        OutErrInfo, llvm::sys::fs::F_None);

        if (OutErrInfo == ok) {
            const clang::RewriteBuffer RewriteBuf = Rewriter.getEditBuffer(fileID);
            if(RewriteBuf.size()) {
                std::string content = std::string(RewriteBuf.begin(), RewriteBuf.end());
                outputFile << content;
                outputFile.close();
            }
        }
    }
#endif

    //Rewriter.getEditBuffer(File).write(llvm::outs());

    if (shouldFlush) {
        /*const std::string file_ext = full_file_path.substr(
            filename.find_last_of(".") + 1);*/
        if(!full_file_path.empty() && !full_file_ext.empty()) {
            llvm::outs() << "full_file_ext = " << full_file_ext << "\n";
            //full_file_path.erase(full_file_path.length() - full_file_ext.length(), full_file_ext.length());
            std::error_code error_code;
            llvm::raw_fd_ostream outFile(out_path, error_code, llvm::sys::fs::F_None);
            Rewriter.getEditBuffer(fileID).write(outFile);
            outFile.close();
        }
    }
}

FrontendAction *ToolFactory::create() {
    return new UseOverride::Action();
}

} // namespace clang_utils
