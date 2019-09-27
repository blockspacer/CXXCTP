#include "clangPipeline.hpp"

#include "DispatchQueue.hpp"

#include "funcParser.hpp"

#include "clangUtils.hpp"

#include "options/ctp/options.hpp"

#include <experimental/filesystem>

#include <clang/Rewrite/Core/RewriteBuffer.h>
#include <clang/Rewrite/Core/Rewriter.h>
#include <clang/ASTMatchers/ASTMatchers.h>
#include <clang/AST/ASTContext.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/ASTMatchers/ASTMatchersMacros.h>
#include <clang/AST/Type.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Sema/Sema.h>
#include <clang/Basic/FileManager.h>
#include <clang/Basic/LangOptions.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Sema/Sema.h>
#include <clang/Lex/Lexer.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Frontend/ASTConsumers.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Tooling/Tooling.h>
#include <clang/Rewrite/Core/Rewriter.h>
#include <clang/Driver/Options.h>
#include <clang/AST/AST.h>
#include <clang/AST/ASTContext.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/ASTConsumers.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <clang/Rewrite/Core/Rewriter.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Sema/Sema.h>
#include <clang/Lex/Lexer.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Frontend/ASTConsumers.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Tooling/Tooling.h>
#include <clang/Rewrite/Core/Rewriter.h>
#include <clang/Driver/Options.h>
#include <clang/AST/AST.h>
#include <clang/AST/ASTContext.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/ASTConsumers.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <clang/Rewrite/Core/Rewriter.h>

#include <folly/logging/xlog.h>

/*
using namespace clang;
using namespace clang::driver;
using namespace clang::tooling;
using namespace llvm;
using namespace clang::ast_matchers;
using clang::tooling::CommonOptionsParser;
//using clang::tooling::Replacement;
using llvm::StringRef;*/

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

std::map<std::string, cxxctp_callback> get_cxxctp_callbacks() {
  return cxxctp_callbacks;
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
void add_default_clang_args(std::vector<std::string> &args)
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

bool nativeCallModuleFunc(const UseOverride::Checker::MatchResult& Result,
                    clang::Rewriter &rewriter_,
                    const clang::Decl* decl,
                    const cxxctp::parsed_func& func_to_call,
                    const std::vector<cxxctp::parsed_func>& parsedFuncs) {
    clang_utils::cxxctp_callback callback_cxxctp =
      clang_utils::get_cxxctp_callback(func_to_call.parsed_func_.func_name_);
    if(!callback_cxxctp) {
        return false;
    }

    XLOG(DBG9) << "found native callback for: "
                 << func_to_call.parsed_func_.func_name_;

    callback_cxxctp(func_to_call, Result, rewriter_, decl, parsedFuncs);
    return true;
}

#if defined(CLING_IS_ON)

void clingCallModuleFunc(const UseOverride::Checker::MatchResult& Result,
                    clang::Rewriter &rewriter_,
                    const clang::Decl* decl,
                    const cxxctp::parsed_func& func_to_call,
                    const std::vector<cxxctp::parsed_func>& parsedFuncs) {
    bool calledNativeCallback = nativeCallModuleFunc(Result, rewriter_,
      decl, func_to_call, parsedFuncs);
    if(calledNativeCallback) {
      XLOG(DBG9) << "found native callback for: "
                   << func_to_call.func_with_args_as_string_;
      return;
    }

    XLOG(DBG9) << "can`t find native callback for: "
                 << func_to_call.func_with_args_as_string_ << "; fallback to cling";

    std::ostringstream sstr;
    // scope begin
    sstr << "[](){";
    sstr << "return ";
    // func begin
    sstr << func_to_call.parsed_func_.func_name_ << "( ";
    // func arguments
    sstr << "*(const cxxctp::parsed_func*)("
         // Pass a pointer into cling as a string.
         << std::hex << std::showbase
         << reinterpret_cast<size_t>(&func_to_call) << ')';
    sstr << " , "; // next argument
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
        if(compilationResult
            != cling::Interpreter::Interpreter::kSuccess) {
          XLOG(ERR) << "ERROR while running cling code:\n" << sstr.str();
        }
    }
}

#endif // CLING_IS_ON

void UseOverride::Checker::run(const UseOverride::Checker::MatchResult& Result) {
    //XLOG(DBG9) << "match1 = ";
    XLOG(DBG9) << "UseOverride::Checker::run...";

    /*auto any_decl = Result.Nodes.getNodeAs<clang::NamedDecl>( "any_decl" );
    if(any_decl && !any_decl->isInvalidDecl()
       && any_decl->getIdentifier()) {
      XLOG(DBG9) << "any_decl = " << any_decl->getName().str();
    }
    auto any_decl = Result.Nodes.getNodeAs<clang::Decl>( "any_decl" );
    if(any_decl && !any_decl->isInvalidDecl()
       && any_decl->getKind()) {
      XLOG(DBG9) << "any_decl = " << any_decl->getDeclKindName();
    }*/

    /*auto any_decl2 = Result.Nodes.getNodeAs<clang::PragmaCommentDecl>( "any_decl" );
    if(any_decl2) {
      XLOG(DBG9) << "any_decl2 = "
        << any_decl2->getArg().str() << " " << any_decl2->getDeclKindName();
    }*/

    /*auto any_decl2 = Result.Nodes.getNodeAs<clang::OMPParallelForDirective>( "any_decl" );
    if(any_decl2) {
      XLOG(DBG9) << "any_decl2 = "
        << any_decl2->getStmtClassName();
    }*/

    if ( const clang::Decl* decl = Result.Nodes.getNodeAs<clang::Decl>( "bind_gen" ) )
    {
        XLOG(DBG9) << "Matched bind_gen";
        if ( decl && !decl->isInvalidDecl())
            if (auto annotate = decl->getAttr<clang::AnnotateAttr>()) {
                XLOG(DBG9) << "annotate->getAnnotation()"
                             << annotate->getAnnotation().str();
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
                std::vector<cxxctp::parsed_func> funcs_to_call;
                if (startsWithGen && startsWithCodegen) {
                    code.erase(0, codegen_token.size());
                    isFuncCall = true;
                    funcs_to_call.push_back(
                      cxxctp::parsed_func{
                        "call_codegen",
                        cxxctp::parsed_func_detail{
                          "call_codegen",
                          cxxctp::args{}
                        }
                      });
                }

                const std::string funccall_token = "{funccall};";
                const bool startsWithFunccall =
                        code.rfind(funccall_token, 0) == 0;

                std::vector<cxxctp::parsed_func> parsedFuncs;
                if (startsWithGen && startsWithFunccall) {
                    code.erase(0, funccall_token.size());
                    parsedFuncs = cxxctp::split_to_funcs(code);
                    for (const cxxctp::parsed_func & seg : parsedFuncs) {
                        XLOG(DBG9) << "segment: " << seg.func_with_args_as_string_;
                        XLOG(DBG9) << "funcs_to_call1  func_name_: " << seg.parsed_func_.func_name_;

                        if(!seg.parsed_func_.func_name_.empty()) {
                            funcs_to_call.push_back(seg);
                            //funcs_to_call.push_back(seg.parsed_func_.func_name_);
                        }

                        for (auto const& arg : seg.parsed_func_.args_.as_vec_) {
                            XLOG(DBG9) << "    arg name: " << arg.name_;
                            XLOG(DBG9) << "    arg value: " << arg.value_;
                        }
                        for (auto const& [key, values] : seg.parsed_func_.args_.as_name_to_value_) {
                            XLOG(DBG9) << "    arg key: " << key;
                            XLOG(DBG9) << "    arg values (" << values.size() <<"): ";
                            for (auto const& val : values) {
                                XLOG(DBG9) << "        " << val;
                            }
                        }
                        XLOG(DBG9) << "\n";
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
                    XLOG(DBG9) << "embed for code: "
                                 << code;
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
                        if(compilationResult
                            != cling::Interpreter::Interpreter::kSuccess) {
                          XLOG(ERR) << "ERROR while running cling code:\n" << sstr.str();
                        }
                    }
                    clang::SourceLocation startLoc = decl->getLocStart();
                    clang::SourceLocation endLoc = decl->getLocEnd();

                    /*if( endLoc.isMacroID() ) {
              // Get the start/end expansion locations
              std::pair< clang::SourceLocation, clang::SourceLocation >
                expansionRange =
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
                                      clang::SourceRange(startLoc, endLoc),
                                      resOption->getValue());
                      }
                      delete resOption; /// \note frees resOptionVoid memory
                    }
#endif // CLING_IS_ON
                } else if(isEval) {
                    XLOG(DBG9) << "eval for code: "
                                 << code;
#if defined(CLING_IS_ON)
                    std::ostringstream sstr;
                    sstr << code;
                    if(cling_utils::InterpreterModule::interpMap.find("main_module") != cling_utils::InterpreterModule::interpMap.end()) {
                        cling::Interpreter::CompilationResult compilationResult;
                        cling_utils::InterpreterModule::interpMap["main_module"]->metaProcessor_->process(
                                    sstr.str(), compilationResult, nullptr, true);
                        if(compilationResult
                            != cling::Interpreter::Interpreter::kSuccess) {
                          XLOG(ERR) << "ERROR while running cling code:\n" << sstr.str();
                        }
                    }
                    clang::SourceLocation startLoc = decl->getLocStart();
                    clang::SourceLocation endLoc = decl->getLocEnd();

                    /*if( endLoc.isMacroID() ) {
              // Get the start/end expansion locations
              std::pair< clang::SourceLocation, clang::SourceLocation >
                expansionRange =
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
                                clang::SourceRange(startLoc, endLoc),
                                "");
#endif // CLING_IS_ON
                } else if(isExport) {
                    XLOG(DBG9) << "export for code: "
                                 << code;
#if defined(CLING_IS_ON)
                    std::ostringstream sstr;
                    sstr << code;
                    if(cling_utils::InterpreterModule::interpMap.find("main_module") != cling_utils::InterpreterModule::interpMap.end()) {
                        cling::Interpreter::CompilationResult compilationResult;
                        cling_utils::InterpreterModule::interpMap["main_module"]->metaProcessor_->process(
                                    sstr.str(), compilationResult, nullptr, true);
                        if(compilationResult
                            != cling::Interpreter::Interpreter::kSuccess) {
                          XLOG(ERR) << "ERROR while running cling code:\n" << sstr.str();
                        }
                    }
                    clang::SourceLocation startLoc = decl->getLocStart();
                    clang::SourceLocation endLoc = decl->getLocEnd();

                    /*if( endLoc.isMacroID() ) {
              // Get the start/end expansion locations
              std::pair< clang::SourceLocation, clang::SourceLocation >
                expansionRange =
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


                    clang::ASTContext *Context = Result.Context;
                    // find '('
                    auto l_paren_loc = clang::Lexer::findLocationAfterToken(
                                startLoc.getLocWithOffset(export_start_token.length() - 1),
                                clang::tok::l_paren,
                                Context->getSourceManager(),
                                Context->getLangOpts(),
                                /*skipWhiteSpace=*/true);

                    rewriter_.ReplaceText(
                                clang::SourceRange(
                                    startLoc,
                                    l_paren_loc
                                    ),
                                "");
                    const std::string export_end_token = ")";
                    rewriter_.ReplaceText(
                                clang::SourceRange(
                                    endLoc,
                                    endLoc.getLocWithOffset(export_end_token.length())
                                    ),
                                "");
                    /*rewriter_.ReplaceText(
            clang::SourceRange(startLoc, endLoc),
            code);*/
#endif // CLING_IS_ON
                } else if(isFuncCall) {

                    // Generate bindings for a decl with pyspot annotation
                    //generate_bindings( *decl );
                    XLOG(DBG9) << "generator for code: "
                                 << code;

                    //receivedMessagesQueue_->dispatch([] {
                    for (const cxxctp::parsed_func& func_to_call : funcs_to_call) {
                        XLOG(DBG9) << "main_module task " << func_to_call.func_with_args_as_string_ << "... " << '\n';
#if defined(CLING_IS_ON)
                        clingCallModuleFunc(Result, rewriter_, decl, func_to_call, parsedFuncs);
#else
                        nativeCallModuleFunc(Result, rewriter_, decl, func_to_call, parsedFuncs);
#endif // CLING_IS_ON
                    }
                }
            }
    }
}

UseOverride::Consumer::Consumer(clang::Rewriter &Rewriter)
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

void UseOverride::Consumer::HandleTranslationUnit(clang::ASTContext &Context) {
    XLOG(DBG9) << "Started AST matcher...";
    Finder_.matchAST(Context);
}

UseOverride::Action::ASTConsumerPointer UseOverride::Action::CreateASTConsumer(
  clang::CompilerInstance &Compiler, StringRef) {
    XLOG(DBG9) << "Created AST consumer...";
    Rewriter.setSourceMgr(Compiler.getSourceManager(), Compiler.getLangOpts());
    return std::make_unique<Consumer>(Rewriter);
}

bool UseOverride::Action::BeginSourceFileAction(clang::CompilerInstance &) {
    XLOG(DBG9) << "Processing " << getCurrentFile().str();
    return true;
}

void UseOverride::Action::EndSourceFileAction() {
    ASTFrontendAction::EndSourceFileAction();

    clang::SourceManager &SM = Rewriter.getSourceMgr();

    const auto fileID = SM.getMainFileID();
    const auto fileEntry = SM.getFileEntryForID(SM.getMainFileID());
    std::string full_file_path = fileEntry->getName();
    XLOG(DBG9) << "full_file_path is " << full_file_path;
    const std::string filename = fs::path(full_file_path).filename();
    XLOG(DBG9) << "filename is " << filename;

    XLOG(DBG9) << "** EndSourceFileAction for: "
                 << fileEntry->getName().str();
    const std::string full_file_ext = fs::path(full_file_path).extension();

    const fs::path out_path = fs::absolute(ctp::Options::res_path
      / (filename + ".generated" + full_file_ext));

    bool shouldFlush = true; // TODO: make optional for some files
    if (shouldFlush) {
        /*const std::string file_ext = full_file_path.substr(
            filename.find_last_of(".") + 1);*/
        if(!full_file_path.empty() && !full_file_ext.empty()) {
            XLOG(DBG9) << "full_file_ext = " << full_file_ext;
            //full_file_path.erase(full_file_path.length() - full_file_ext.length(), full_file_ext.length());
            std::error_code error_code;
            llvm::raw_fd_ostream outFile(out_path.string(), error_code, llvm::sys::fs::F_None);
            Rewriter.getEditBuffer(fileID).write(outFile);
            outFile.close();
        }
    }
}

clang::FrontendAction *ToolFactory::create() {
    return new UseOverride::Action();
}

} // namespace clang_utils
