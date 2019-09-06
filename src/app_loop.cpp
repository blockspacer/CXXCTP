/*#include <boost/log/core/record.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/size.hpp>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/bind_executor.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/config.hpp>*/

/*#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <streambuf>*/

/*#include <cling/Interpreter/Interpreter.h>
#include <cling/Interpreter/Value.h>
#include "cling/Interpreter/CIFactory.h"
#include "cling/Interpreter/Interpreter.h"
#include "cling/Interpreter/InterpreterCallbacks.h"
//#include "cling/Interpreter/IncrementalExecutor.h"
//#include "cling/Interpreter/IncrementalParser.h"
#include "cling/Interpreter/Transaction.h"
#include "cling/Interpreter/Value.h"
#include "cling/Interpreter/CValuePrinter.h"
#include "cling/MetaProcessor/MetaProcessor.h"
#include <cling/Utils/Casting.h>
#include "cling/Interpreter/LookupHelper.h"
#include "cling/Utils/AST.h"*/

//#include "mime_type.h"
//#include "http_callbacks.h"

#include <cling/Interpreter/Interpreter.h>
#include <cling/Interpreter/Value.h>
#include "cling/Interpreter/CIFactory.h"
#include "cling/Interpreter/Interpreter.h"
#include "cling/Interpreter/InterpreterCallbacks.h"
//#include "cling/Interpreter/IncrementalExecutor.h"
//#include "cling/Interpreter/IncrementalParser.h"
#include "cling/Interpreter/Transaction.h"
#include "cling/Interpreter/Value.h"
#include "cling/Interpreter/CValuePrinter.h"
#include "cling/MetaProcessor/MetaProcessor.h"
#include <cling/Utils/Casting.h>
#include "cling/Interpreter/LookupHelper.h"
#include "cling/Utils/AST.h"
#include <cling/Interpreter/Interpreter.h>
#include <cling/Interpreter/Value.h>
#include "cling/Interpreter/CIFactory.h"
#include "cling/Interpreter/Interpreter.h"
#include "cling/Interpreter/InterpreterCallbacks.h"
//#include "cling/Interpreter/IncrementalExecutor.h"
//#include "cling/Interpreter/IncrementalParser.h"
#include "cling/Interpreter/Transaction.h"
#include "cling/Interpreter/Value.h"
#include "cling/Interpreter/CValuePrinter.h"
#include "cling/MetaProcessor/MetaProcessor.h"
#include <cling/Utils/Casting.h>
#include "cling/Interpreter/LookupHelper.h"
#include "cling/Utils/AST.h"

/*#include "clang/Basic/FileManager.h"
#include "clang/Basic/LangOptions.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/HeaderSearchOptions.h"
#include "clang/Frontend/ASTUnit.h"
#include "clang/Basic/DiagnosticCommonKinds.inc"*/
#include "clang/Parse/Parser.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/Decl.h"
#include "clang/AST/DeclBase.h"
#include "clang/AST/DeclCXX.h"
#include "clang/AST/PrettyPrinter.h"
#include "clang/AST/Type.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Sema/Sema.h"
/*#include "clang/Basic/FileManager.h"
#include "clang/Basic/LangOptions.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/HeaderSearchOptions.h"
#include "clang/Frontend/ASTUnit.h"
#include "clang/Basic/DiagnosticCommonKinds.inc"*/
#include "clang/Parse/Parser.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/Decl.h"
#include "clang/AST/DeclBase.h"
#include "clang/AST/DeclCXX.h"
#include "clang/AST/PrettyPrinter.h"
#include "clang/AST/Type.h"

/*
#include "clang/AST/ASTContext.h"
#include "clang/AST/DeclVisitor.h"
#include "clang/AST/Decl.h"
#include "clang/AST/DeclCXX.h"
#include "clang/AST/DeclObjC.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ExprCXX.h"
#include "clang/AST/PrettyPrinter.h"
#include "clang/Basic/Module.h"
#include "llvm/Support/raw_ostream.h"*/

#include "clang/Frontend/CompilerInstance.h"
#include "clang/Sema/Sema.h"
#include <clang/Lex/Lexer.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Frontend/ASTConsumers.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Tooling/Tooling.h>
#include <clang/Rewrite/Core/Rewriter.h>
#include "clang/Driver/Options.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Rewrite/Core/Rewriter.h"

#include "clang/ASTMatchers/ASTMatchers.h"

#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchersMacros.h"
#include "clang/Basic/CharInfo.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Lex/Lexer.h"
#include "clang/Lex/MacroArgs.h"
#include "clang/Lex/PPCallbacks.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Refactoring.h"
#include "clang/Tooling/Tooling.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/AttrIterator.h"
#include "clang/AST/Decl.h"
#include "clang/AST/DeclCXX.h"
#include "clang/AST/DeclarationName.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Basic/SourceLocation.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Basic/TokenKinds.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Lex/Lexer.h"
#include "clang/Rewrite/Core/RewriteBuffer.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ErrorOr.h"
#include "llvm/Support/LineIterator.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/TargetSelect.h"

#include "llvm/Config/llvm-config.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include <llvm/Support/raw_os_ostream.h>

#include "llvm/Config/llvm-config.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"

// LLVM includes
#include "llvm//Support/Path.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/Twine.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/raw_ostream.h"

//#include "boost/unordered_map.hpp"
//#include <boost/multi_index_container.hpp>
//#include <boost/multi_index/member.hpp>
//#include <boost/multi_index/ordered_index.hpp>
//#include <boost/multi_index/hashed_index.hpp>
//#include <boost/multi_index/sequenced_index.hpp>
//#include <boost/multi_index/random_access_index.hpp>
//#include <boost/multi_index/identity.hpp>


#include <cling/Interpreter/Interpreter.h>
#include <cling/Interpreter/Value.h>
#include "cling/Interpreter/CIFactory.h"
#include "cling/Interpreter/Interpreter.h"
#include "cling/Interpreter/InterpreterCallbacks.h"
//#include "cling/Interpreter/IncrementalExecutor.h"
//#include "cling/Interpreter/IncrementalParser.h"
#include "cling/Interpreter/Transaction.h"
#include "cling/Interpreter/Value.h"
#include "cling/Interpreter/CValuePrinter.h"
#include "cling/MetaProcessor/MetaProcessor.h"
#include <cling/Utils/Casting.h>
#include "cling/Interpreter/LookupHelper.h"
#include "cling/Utils/AST.h"
#include <cling/Interpreter/Interpreter.h>
#include <cling/Interpreter/Value.h>
#include "cling/Interpreter/CIFactory.h"
#include "cling/Interpreter/Interpreter.h"
#include "cling/Interpreter/InterpreterCallbacks.h"
//#include "cling/Interpreter/IncrementalExecutor.h"
//#include "cling/Interpreter/IncrementalParser.h"
#include "cling/Interpreter/Transaction.h"
#include "cling/Interpreter/Value.h"
#include "cling/Interpreter/CValuePrinter.h"
#include "cling/MetaProcessor/MetaProcessor.h"
#include <cling/Utils/Casting.h>
#include "cling/Interpreter/LookupHelper.h"
#include "cling/Utils/AST.h"

/*#include "clang/Basic/FileManager.h"
#include "clang/Basic/LangOptions.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/HeaderSearchOptions.h"
#include "clang/Frontend/ASTUnit.h"
#include "clang/Basic/DiagnosticCommonKinds.inc"*/
#include "clang/Parse/Parser.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/Decl.h"
#include "clang/AST/DeclBase.h"
#include "clang/AST/DeclCXX.h"
#include "clang/AST/PrettyPrinter.h"
#include "clang/AST/Type.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Sema/Sema.h"
/*#include "clang/Basic/FileManager.h"
#include "clang/Basic/LangOptions.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/HeaderSearchOptions.h"
#include "clang/Frontend/ASTUnit.h"
#include "clang/Basic/DiagnosticCommonKinds.inc"*/
#include "clang/Parse/Parser.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/Decl.h"
#include "clang/AST/DeclBase.h"
#include "clang/AST/DeclCXX.h"
#include "clang/AST/PrettyPrinter.h"
#include "clang/AST/Type.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Sema/Sema.h"
#include <clang/Lex/Lexer.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Frontend/ASTConsumers.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Tooling/Tooling.h>
#include <clang/Rewrite/Core/Rewriter.h>
#include "clang/Driver/Options.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Rewrite/Core/Rewriter.h"

#include "clang/ASTMatchers/ASTMatchers.h"

#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchersMacros.h"
#include "clang/Basic/CharInfo.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Lex/Lexer.h"
#include "clang/Lex/MacroArgs.h"
#include "clang/Lex/PPCallbacks.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Refactoring.h"
#include "clang/Tooling/Tooling.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/AttrIterator.h"
#include "clang/AST/Decl.h"
#include "clang/AST/DeclCXX.h"
#include "clang/AST/DeclarationName.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Basic/SourceLocation.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Basic/TokenKinds.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Lex/Lexer.h"
#include "clang/Rewrite/Core/RewriteBuffer.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ErrorOr.h"
#include "llvm/Support/LineIterator.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/TargetSelect.h"

#include "llvm/Config/llvm-config.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include <llvm/Support/raw_os_ostream.h>

#include "llvm/Config/llvm-config.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"

// LLVM includes
#include "llvm//Support/Path.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/Twine.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/raw_ostream.h"

//#include "boost/unordered_map.hpp"
//#include <boost/multi_index_container.hpp>
//#include <boost/multi_index/member.hpp>
//#include <boost/multi_index/ordered_index.hpp>
//#include <boost/multi_index/hashed_index.hpp>
//#include <boost/multi_index/sequenced_index.hpp>
//#include <boost/multi_index/random_access_index.hpp>
//#include <boost/multi_index/identity.hpp>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <streambuf>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <functional>
#include <unordered_map>
#include <map>
#include <condition_variable>
#include <cstdio>
#include <functional>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>
//#include <filesystem>
#include <memory>
#include <numeric>
#include <string_view>
#include <condition_variable>
// Standard includes
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <iterator>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <streambuf>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <functional>
#include <unordered_map>
#include <map>
#include <condition_variable>
#include <cstdio>
#include <functional>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>
#include <regex>
#include <iterator>

#include "jinja2cpp/value.h"
#include "jinja2cpp/template.h"
#include "jinja2cpp/filesystem_handler.h"
#include "jinja2cpp/template_env.h"
#include "jinja2cpp/reflected_value.h"

#include "funcParser.h"
#include "clangUtils.h"

extern std::vector<parsed_func> split_to_funcs(std::string const& inStr);

//using namespace jinja2;
using namespace std;
using namespace clang;
using namespace clang::driver;
using namespace clang::tooling;
using namespace llvm;
using namespace clang::ast_matchers;
using clang::tooling::CommonOptionsParser;
using clang::tooling::Replacement;
using llvm::StringRef;

class AppLoop
{
public:
    AppLoop()
    {
    }

    void run();

    void stop();

    // The acceptor receives incoming connections
    //tcp::acceptor acceptor;

    bool m_Running = true;

    //std::vector<std::function<void(bool,int)>> callbacks_;
    //std::function<void(void)> callback_;
};

AppLoop* appLoop = nullptr;

void AppLoop::run() {
        std::cout << "AppLoop::run(): " << std::endl;
}

void AppLoop::stop() {
    m_Running = false;
}

#if defined(CLING_IS_ON)

static void main_module_cling_prepare() {
    printf("called app_loop_prepare\n");
    //MyTest1();

    try
    {
        appLoop = new AppLoop();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

/*static void main_module_cling_run_update() {
    printf("called app_loop_run_update\n");
}*/

static void main_module_cling_run() {
    printf("called app_loop_run\n");

    appLoop->run();
}

static void main_module_cling_shutdown() {
    printf("called app_loop_shutdown\n");
    appLoop->stop();
    delete appLoop;
}

/*#include <mutex>
std::mutex lock_;*/

void app_loop() {
    printf("loaded app_loop with CLING\n");
    /*std::scoped_lock<std::mutex> lock(lock_);
    auto globVar =
          ::std::optional<std::string>
          {"asdasdcout123123"};*/
}

/*const char* call_codegen(
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl) {
  printf("call_codegen called...\n");
  rewriter.ReplaceText(
    decl->getSourceRange(),
    "call_codegen result here!13#5#wq@dfe");
  return "";
}*/

clang::SourceLocation
findPureInsertionPoint(clang::CXXMethodDecl *MethodDecl,
                   const clang::ASTContext &Context) {
  clang::SourceLocation Location;

  /// Find the end of the parameter list.
  if (MethodDecl->param_empty()) {
    const unsigned Offset = MethodDecl->getName().size();
    Location = MethodDecl->getLocation().getLocWithOffset(Offset);
  } else {
    const clang::ParmVarDecl *Last = *std::prev(MethodDecl->param_end());
    Location = Last->getLocEnd(); // getEndLoc
  }

  Location = clang::Lexer::findLocationAfterToken(
      Location, clang::tok::r_paren, Context.getSourceManager(),
      Context.getLangOpts(),
      /*skipWhiteSpace=*/true);

  return Location.getLocWithOffset(0);
}

clang::SourceRange
findFuncBodyRange(clang::CXXMethodDecl *MethodDecl,
                   const clang::ASTContext &Context) {
#if 0
  clang::SourceLocation LocationStart;
  clang::SourceLocation LocationEnd;

  /// Find the end of the parameter list.
  if (MethodDecl->param_empty()) {
    const unsigned Offset = MethodDecl->getName().size();
    LocationStart = MethodDecl->getLocation().getLocWithOffset(Offset);
  } else {
    const clang::ParmVarDecl *Last = *std::prev(MethodDecl->param_end());
    LocationStart = Last->getLocEnd(); // getEndLoc
  }

  LocationStart = LocationStart.getLocWithOffset(1);

  LocationEnd = clang::Lexer::findLocationAfterToken(
      LocationStart, clang::tok::r_brace, Context.getSourceManager(),
      Context.getLangOpts(),
      /*skipWhiteSpace=*/true);

  return clang::SourceRange(
    LocationStart,
    LocationEnd);
#endif
  return MethodDecl->getBody()->getSourceRange();
}

clang::SourceLocation
findVirtualInsertionPoint(clang::CXXMethodDecl *MethodDecl,
                   const clang::ASTContext &Context) {
  clang::SourceLocation Location;

  Location = MethodDecl->getLocStart();

  return Location.getLocWithOffset(0);
}

clang::SourceLocation
findCXXRecordNameEndPoint(clang::CXXRecordDecl const *decl,
                   const clang::ASTContext &Context) {
  clang::SourceLocation Location;

  /// Find the end of name.
  const unsigned Offset = decl->getName().size();
  Location = decl->getLocation().getLocWithOffset(Offset);

  return Location.getLocWithOffset(0);
}

const bool isReflectable(DeclaratorDecl* decl) {
  bool res = false;
  if ( auto annotate = decl->getAttr<clang::AnnotateAttr>() )
  {
    //
    const std::string gen_token = "{gen};{attr};";
    std:: string code =
      annotate->getAnnotation().str();
    const bool startsWithGen =
      code.rfind(gen_token, 0) == 0;
    code.erase(0, gen_token.size());
    if (startsWithGen) {
      std::cout << "isReflectable code() " << code << std::endl;
      std::string delimiter = ";";
      size_t pos = 0;
      std::string token;
      while ((pos = code.find(delimiter)) != std::string::npos) {
        token = code.substr(0, pos);
        std::cout << "isReflectable token " << token << std::endl;
        if(token == "reflectable") {
          res = true;
          break;
        }
        code.erase(0, pos + delimiter.length());
      }
      if(!code.empty()
         && code == "reflectable") {
        res = true;
      }
    }
  }

  std::cout << "isReflectable attr() "
    << decl->getName().str()
    << "is " << res << std::endl;


#if 0
  for (auto &attr : decl->attrs()) {
      if (attr->getKind() == attr::Annotate) {
        Attr a = *attr;
        auto annotate = static_cast<clang::AnnotateAttr>(*attr);

        std::cout << "isReflectable attr->getSpelling() " << attr->getSpelling() << std::endl;
        //
        const std::string gen_token = "{gen};{attr}";
        std:: string code =
          attr->getSpelling();
        const bool startsWithGen =
          code.rfind(gen_token, 0) == 0;
        code.erase(0, gen_token.size());
        if (startsWithGen) {
          std::string delimiter = ";";
          size_t pos = 0;
          std::string token;
          while ((pos = code.find(delimiter)) != std::string::npos) {
            token = code.substr(0, pos);
            std::cout << "isReflectable token " << token << std::endl;
            if(token == "reflectable") {
              res = true;
            }
            code.erase(0, pos + delimiter.length());
          }
        }
      }
  }
#endif
  return res;
}

template<typename CharT>
std::basic_string<CharT> ReadFile(jinja2::FileStreamPtr<CharT>& stream)
{
    std::basic_string<CharT> result;
    constexpr size_t buffSize = 0x10000;
    CharT buff[buffSize];

    if (!stream)
        return result;

    while (stream->good() && !stream->eof())
    {
        stream->read(buff, buffSize);
        auto readSize = stream->gcount();
        result.append(buff, buff + readSize);
        if (readSize < buffSize)
            break;
    }

    return result;
}

const std::string
getFileContent(const std::string& path)
{
  std::ifstream file(path);
  if(!file.is_open()) {
    printf("ERROR: can`t read file %s\n", path.c_str());
    return "";
  }
  std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

  //printf("loaded %s from file %s\n", content.c_str(), path.c_str());
  return content;
}

void writeToFile(const std::string& str, const std::string& path) {
  //printf("saving %s to file %s\n", str.c_str(), path.c_str());
  std::ofstream file(path);
  if(!file.is_open()) {
    printf("ERROR: can`t write to file %s\n", path.c_str());
    return;
  }
  file << str;
  file.close();
}

struct ReflectedEnumItems {
  std::string name;
  int64_t value;
};

/*namespace jinja2
{
template<>
struct jinja2::TypeReflection<ReflectedEnumItems>
  : TypeReflected<ReflectedEnumItems>
{
    static auto& GetAccessors()
    {
        static std::unordered_map<std::string, FieldAccessor> accessors = {
            {"name", [](const ReflectedEnumItems& obj) {return obj.name;}},
            {"value", [](const ReflectedEnumItems& obj) {return obj.value;}}
        };

        return accessors;
    }
};
} // namespace jinja2*/

const char* typeclass_instance(
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl) {
  return ""; // TODO
}

// see https://github.com/tlatkdgus1/llvm-code_obfuscate/blob/c4d0641f95704fb9909e2ac09500df1b6bc5d017/tools/clang/lib/AST/DeclPrinter.cpp#L447
// see https://github.com/root-project/root/blob/331efa4c00fefc38980eaaf7b41b8e95fcd1a23b/interpreter/llvm/src/tools/clang/lib/AST/DeclPrinter.cpp#L474
const char* typeclass(
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl) {

  printf("typeclass called...\n");

  clang::CXXRecordDecl const *node =
      matchResult.Nodes.getNodeAs<clang::CXXRecordDecl>("bind_gen");

  if (node) {
    printf("reflect is record %s\n", node->getName().str().c_str());
    // TODO: getOriginalNamespace
    {

      jinja2::ValuesList GeneratedTypeclassFuncs;

      // see https://github.com/asutton/clang/blob/master/lib/AST/DeclPrinter.cpp#L502
      for(auto fct = node->method_begin();
        fct != node->method_end(); ++fct)
      {
        CXXMethodDecl* tf = *fct;
        std::string methodDecl = printMethodDecl(decl, node, tf);

        if(!methodDecl.empty()) {
          GeneratedTypeclassFuncs.push_back(jinja2::Value{methodDecl.c_str()});
        }
      }

      jinja2::ValuesMap params;

      SourceLocation startLoc = decl->getLocStart();
      SourceLocation endLoc = decl->getLocEnd();
      expandLocations(startLoc, endLoc, rewriter);
      auto codeRange = SourceRange{startLoc, endLoc};
      std::string OriginalTypeclassBaseCode =
        rewriter.getRewrittenText(codeRange);
      // removes $apply(typeclass, e.t.c.)
      std::string CleanOriginalTypeclassBaseCode
        = std::regex_replace(OriginalTypeclassBaseCode,
            std::regex("\\$apply([^(]*)\\([^)]*\\)(.*)"), "$1$2");

      params.emplace("OriginalTypeclassBaseCode",
                     jinja2::Value{CleanOriginalTypeclassBaseCode.c_str()});

      params.emplace("GeneratedTypeclassName",
                     jinja2::Value{node->getName().str().c_str()});

      params.emplace("GeneratedTypeclassFuncs",
                     jinja2::Value{GeneratedTypeclassFuncs});

      {
        std::string gen_hpp_name
            = node->getNameAsString() + ".typeclass.generated.hpp";
        std::string typeclassHppConvertor =
          getFileContent("../resources/typeclass_gen_hpp.j2tpl");
        params.emplace("generator_path",
                       jinja2::Value{"typeclass_gen_hpp.j2tpl"});
        params.emplace("generator_includes",
                       jinja2::Value{
                           jinja2::ValuesList{
                             /// \TODO
                             "../src/type_erasure_common.hpp"}});
        jinja2::Template tpl;
        auto parseResult = tpl.Load(typeclassHppConvertor);
        if(!parseResult) {
          printf("ERROR: can`t load jinja2 template from %s [%s]\n",
            typeclassHppConvertor.c_str(),
            parseResult.error().GetLocationDescr().c_str());
        }
        writeToFile(tpl.RenderAsString(params).value(), gen_hpp_name);
      }
    }
  }

  return "";
}

const char* reflect_enum(
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl) {
  printf("reflect_enum called...\n");

  clang::EnumDecl const *node =
      matchResult.Nodes.getNodeAs<clang::EnumDecl>("bind_gen");

  if (node) {
    printf("reflect is record %s\n", node->getName().str().c_str());

    /*jinja2::ValuesList GeneratedEnumNames;
    GeneratedEnumNames.push_back("NONE");
    jinja2::ValuesList GeneratedEnumValues;
    GeneratedEnumValues.push_back(0);*/
    jinja2::ValuesList GeneratedEnumItems;

    {
    jinja2::ValuesMap GeneratedEnumItemsVMap;
    GeneratedEnumItemsVMap.emplace("name",
                                   jinja2::Value{"NONE"});
    GeneratedEnumItemsVMap.emplace("value",
                                   jinja2::Value(0));
    GeneratedEnumItems.push_back(
        jinja2::Value{GeneratedEnumItemsVMap});
    /*GeneratedEnumItems.push_back(
        jinja2::Value{
            jinja2::ValuesMap{
                {"value", jinja2::Value(0)},
                {"name", "NONE"}
            }
        });*/
    }

   /* GeneratedEnumItems.push_back(
      jinja2::ValuesMap{
        {"value", jinja2::Value(0)},
        {"name", "NONE"}} );*/
    //GeneratedEnumItems["NONE"] = 0;

    LangOptions LO;
    PrintingPolicy PrintPolicy(LO);
    PrintPolicy.AnonymousTagLocations = false;
    PrintPolicy.SuppressTagKeyword = true;

    PresumedLoc pLoc = node->getASTContext()
                           .getSourceManager()
                           .getPresumedLoc(node->getLocation());

    std::string nameString = node->getNameAsString();
    if(nameString.empty()) {
      printf("ERROR (reflect_enum): "
             "can`t handle enum without name [%s:%d]\n",
              pLoc.getFilename(), pLoc.getLine());
    }
    std::string typeString = "int";
    const QualType QT = node->getIntegerType();
    if(!QT.isNull()) {
      typeString = QT.getAsString(); // getTypeClassName
    }
    printf("%s : %s [%s:%d]\n",
      nameString.c_str(), typeString.c_str(),
      pLoc.getFilename(), pLoc.getLine());

    int64_t maxval = std::numeric_limits<int64_t>::min();
    for (auto iter = node->enumerator_begin();
         iter != node->enumerator_end(); iter++)
    {
        printf("    %s %ld\n", iter->getNameAsString().c_str(),
          iter->getInitVal().getExtValue());
        /*GeneratedEnumNames.push_back(iter->getNameAsString());
        GeneratedEnumValues.push_back(iter->getInitVal().getExtValue());
        GeneratedEnumItems[iter->getNameAsString()] = iter->getInitVal().getExtValue();*/
        jinja2::ValuesMap GeneratedEnumItemsVMap;
        GeneratedEnumItemsVMap.emplace("value",
                                       jinja2::Value{
                                           iter->getInitVal().getExtValue()});
        GeneratedEnumItemsVMap.emplace("name",
                                       jinja2::Value{
                                           iter->getNameAsString()});
        GeneratedEnumItems.push_back(
          jinja2::Value{GeneratedEnumItemsVMap});
        maxval = std::max(maxval, iter->getInitVal().getExtValue());
    }
    printf("\n");

    {
        /*GeneratedEnumNames.push_back("TOTAL");
        GeneratedEnumValues.push_back(maxval + 1);
        GeneratedEnumItems["TOTAL"] = maxval + 1;*/
        jinja2::ValuesMap GeneratedEnumItemsVMap;
        GeneratedEnumItemsVMap.emplace("value",
                                       jinja2::Value(maxval + 1));
        GeneratedEnumItemsVMap.emplace("name",
                                       jinja2::Value{"TOTAL"});
        GeneratedEnumItems.push_back(
          jinja2::Value{GeneratedEnumItemsVMap});
    }

      /*std::string enum2StringConvertor = R"(
      inline const char* {{enumName}}ToString({{enumName}} e)
      {
          switch (e)
          {
      {% for item in items %}
          case {{item}}:
              return "{{item}}";
      {% endfor %}
          }
          return "Unknown Item";
      })";*/
      //jinja2::RealFileSystem fs;
      //auto test1Stream = fs.OpenStream("test_data/simple_template1.j2tpl");

      jinja2::ValuesMap params;
      params.emplace("GeneratedEnumName",
                     jinja2::Value{nameString});
      params.emplace("GeneratedEnumType",
                     jinja2::Value{typeString});
      params.emplace("GeneratedEnumItems",
                     jinja2::Value{GeneratedEnumItems});

      //tpl.Load("{{'Hello World' }}!!!");
      //tpl.LoadFromFile("simple_template1.j2tpl");
      //std::cout << tpl.RenderAsString(params);

    std::string gen_hpp_name
          = node->getNameAsString() + ".enum.generated.hpp";
    {
      std::string enum2StringConvertor =
        getFileContent("../resources/enum_gen_cpp.j2tpl");
      params.emplace("generator_path",
                     jinja2::Value{"enum_gen_cpp.j2tpl"});
      params.emplace("generator_includes",
                     jinja2::Value{
                         jinja2::ValuesList{gen_hpp_name}});
      jinja2::Template tpl;
      auto parseResult = tpl.Load(enum2StringConvertor);
      if(!parseResult) {
        printf("ERROR: can`t load jinja2 template from %s [%s]\n",
          enum2StringConvertor.c_str(), parseResult.error().GetLocationDescr().c_str());
      }
      writeToFile(tpl.RenderAsString(params).value(),
                    node->getNameAsString() + ".enum.generated.cpp");
    }

    {
      std::string enum2StringConvertor =
        getFileContent("../resources/enum_gen_hpp.j2tpl");
      params.emplace("generator_path",
                     jinja2::Value{"enum_gen_hpp.j2tpl"});
      jinja2::Template tpl;
      auto parseResult = tpl.Load(enum2StringConvertor);
      if(!parseResult) {
        printf("ERROR: can`t load jinja2 template from %s [%s]\n",
          enum2StringConvertor.c_str(),
          parseResult.error().GetLocationDescr().c_str());
      }
      writeToFile(tpl.RenderAsString(params).value(), gen_hpp_name);
    }
  }

  return "";
}

const char* make_reflect(
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl) {
  printf("make_removefuncbody called...\n");

  std::string indent = "  ";
  std::string output{};
  output.append("\n");
  output.append(indent
                  + "public:");
  indent.append("  ");
  output.append("\n");

  std::map<std::string, std::string> fields;
  std::map<std::string, std::string> methods;

  clang::CXXRecordDecl const *record =
      matchResult.Nodes.getNodeAs<clang::CXXRecordDecl>("bind_gen");
  if (record) {
    //printf("reflect is record %s\n", record->getName().str().c_str());

    // see https://github.com/Papierkorb/bindgen/blob/b55578e517a308778f5a510de02af499b353f15d/clang/src/record_match_handler.cpp
    for (clang::Decl *decl : record->decls()) {
      if (clang::CXXMethodDecl *method
            = llvm::dyn_cast<clang::CXXMethodDecl>(decl)) {
        //runOnMethod(method, isSignal);
        printf("reflect is CXXMethodDecl %s %s %s %s\n",
          method->getNameInfo().getName().getAsString().c_str(),
          method->getReturnType().getAsString().c_str(),
          method->getType().getUnqualifiedType().getAsString().c_str(),
          method->getName().str().c_str());
        if(isReflectable(method)) {
          methods[method->getNameInfo().getName().getAsString()] =
            method->getReturnType().getAsString().c_str();
        }
      } else if (clang::AccessSpecDecl *spec
                    = llvm::dyn_cast<clang::AccessSpecDecl>(decl)) {
        //isSignal = AccessSpecDecl(spec);
        //printf("is CXXMethodDecl %s\n", spec->getName().str().c_str());
      } else if (clang::FieldDecl *field
                    = llvm::dyn_cast<clang::FieldDecl>(decl)) {
        //runOnField(field);
        printf("reflect is FieldDecl %s %s\n",
          field->getType().getUnqualifiedType().getAsString().c_str(),
          field->getName().str().c_str());
        if(isReflectable(field)) {
          fields[field->getName().str()] =
            field->getType().getUnqualifiedType().getAsString().c_str();
        }
      }
    }

    // TODO: use jinja / template

    output.append(indent
                    + "static std::map<std::string, std::string> fields");
    output.append(" = {");
    output.append("\n");
    for(const auto& [key, value] : fields) {
      output.append(indent
                      + indent + "{ ");
      output.append("\"" + key + "\"");
      output.append(", ");
      output.append("\"" + value + "\"");
      output.append(" }");
      output.append("\n");
    }
    output.append("\n");
    output.append(indent
                  + "};");
    output.append("\n");
    // methods
    output.append("\n");
    output.append(indent
                    + "static std::map<std::string, std::string> methods");
    output.append(" = {");
    output.append("\n");
    for(const auto& [key, value] : methods) {
      output.append(indent + indent
                      + "{ ");
      output.append("\"" + key + "\"");
      output.append(", ");
      output.append("\"" + value + "\"");
      output.append(" }");
      output.append("\n");
    }
    output.append("\n");
    output.append(indent +
                    "};");
    output.append("\n");
    auto locEnd = record->getLocEnd();
    rewriter.InsertText(locEnd, output,
      /*InsertAfter=*/true, /*IndentNewLines*/ false);
#if 0
    rewriter.InsertText(locEnd.getLocWithOffset(-1), "\nsdfsdfsdff",
      /*InsertAfter=*/true, /*IndentNewLines*/ true);
    rewriter.InsertText(locEnd.getLocWithOffset(-1), "\nfgfgfgfgf",
      /*InsertAfter=*/true, /*IndentNewLines*/ true);
#endif

    /*for(auto fct = record->method_begin();
      fct!= record->method_end(); ++fct)
    {
      if(fct->hasBody() && !fct->getName().str().empty()) {
          printf("INFO: removed body from function %s in CXXRecordDecl %s\n",
            fct->getName().str().c_str(),
            record->getName().str().c_str());
          rewriter.RemoveText(findFuncBodyRange(*fct, *matchResult.Context));
        }
    }*/
  }
  return "";
}

const char* make_removefuncbody(
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl) {
  printf("make_removefuncbody called...\n");

  clang::CXXRecordDecl const *record =
      matchResult.Nodes.getNodeAs<clang::CXXRecordDecl>("bind_gen");
  if (record) {
    printf("is record %s\n", record->getName().str().c_str());
    for(auto fct = record->method_begin();
      fct!= record->method_end(); ++fct)
    {
      if(fct->hasBody() && !fct->getName().str().empty()) {
          printf("INFO: removed body from function %s in CXXRecordDecl %s\n",
            fct->getName().str().c_str(),
            record->getName().str().c_str());
          rewriter.RemoveText(findFuncBodyRange(*fct, *matchResult.Context));
        }
    }
  }
  return "";
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

// see https://blog.jetbrains.com/clion/2017/11/towards-a-more-powerful-and-simpler-cpp-with-herb-sutter/
// see https://herbsutter.com/2017/07/26/metaclasses-thoughts-on-generative-c/
// see https://www.fluentcpp.com/2018/03/09/c-metaclasses-proposal-less-5-minutes/
const char* make_interface(
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl) {
  printf("make_interface called...\n");

  clang::CXXRecordDecl const *record =
      matchResult.Nodes.getNodeAs<clang::CXXRecordDecl>("bind_gen");
  if (record) {

    /*SourceLocation startLoc = record->getLocStart();
    SourceLocation endLoc = record->getLocEnd();
    expandLocations(startLoc, endLoc, rewriter);
    rewriter.InsertText(startLoc, " startLoc1 ");
    rewriter.InsertText(endLoc, " endLoc2 ");*/

    printf("is record %s\n", record->getName().str().c_str());
#if 0
    {
        clang::SourceLocation ClassRenamePoint =
            findCXXRecordNameEndPoint(record, *matchResult.Context);
        /*rewriter.ReplaceText(ClassRenamePoint,
          record->getName().size(), "asdsadads ");*/
        rewriter.InsertText(record->getLocation(), "ClassRenamePoint ");
    }
#endif // 0

    // TODO:
    // see https://stackoverflow.com/questions/24706053/how-to-find-move-constructors-in-codebase-using-clang-ast-tools/32082812#32082812
    // compiler.require(!f.is_copy() && !f.is_move(), "interfaces may not copy or move; consider a virtual clone() instead"); // 3.1

    // see https://github.com/crdelozier/ironclad/blob/master/tools/refactoring-tool/Translator.hpp#L327
    // see https://dl.khadas.com/test/github/external/v8/tools/clang/plugins/FindBadConstructsConsumer.cpp
    // see https://github.com/crosswalk-project/chromium-crosswalk/blob/master/tools/clang/plugins/FindBadConstructsConsumer.cpp
    // see https://github.com/csmith-project/creduce/blob/master/clang_delta/RemoveUnusedOuterClass.cpp#L68
    if (!record->hasUserDeclaredDestructor()) {
      printf("ERROR: found interface %s without virtual destructor\n",
        record->getName().str().c_str());
      //rewriter.InsertText(PureInsertionPoint,
      //  "\nvirtual ~CLASSNAME_HERE() noexcept {}\n");
    } else if (!record->getDestructor()->isVirtual()) {
      printf("ERROR: found not-virtual destructor in interface %s\n",
        record->getName().str().c_str());
    }

    for(auto fld = record->fields().begin();
      fld!= record->fields().end(); ++fld)
    {
        printf("ERROR: found data %s in interface %s\n",
          fld->getName().str().c_str(),
          record->getName().str().c_str());
    }


    for(auto fct = record->method_begin();
      fct!= record->method_end(); ++fct)
    {
      if(!fct->isInvalidDecl() && !fct->getName().str().empty()) {
        // check
        if(fct->isModulePrivate()) {
          printf("ERROR: found private function %s in interface %s\n",
            fct->getName().str().c_str(),
            record->getName().str().c_str());
        }

        // check
        if(fct->hasBody()) {
          printf("ERROR: found function %s with body in interface %s\n",
            fct->getName().str().c_str(),
            record->getName().str().c_str());
        }

        // modify
        if(!fct->isPure()) {
          //fct->setPure(true);
          printf("INFO: made pure function %s in interface %s\n",
            fct->getName().str().c_str(),
            record->getName().str().c_str());
          //clang::CXXMethodDecl f =
          //findInsertionPoint()

          clang::SourceLocation PureInsertionPoint =
              findPureInsertionPoint(*fct, *matchResult.Context);
          rewriter.InsertText(PureInsertionPoint, " = 0");
        }

        // modify
        if(!fct->isVirtual()) {
          //fct->setPure(true);
          printf("INFO: made virtual function %s in interface %s\n",
            fct->getName().str().c_str(),
            record->getName().str().c_str());
          //clang::CXXMethodDecl f =
          //findInsertionPoint()

          clang::SourceLocation VirtualInsertionPoint =
              findVirtualInsertionPoint(*fct, *matchResult.Context);
          rewriter.InsertText(VirtualInsertionPoint, "virtual ");
        }
      }
    }
  }

  clang::FieldDecl const *field =
    matchResult.Nodes.getNodeAs<clang::FieldDecl>("bind_gen");
  if (field) {
    printf("is field\n");
  }

  clang::FunctionDecl const *function =
      matchResult.Nodes.getNodeAs<clang::FunctionDecl>("bind_gen");
  if (function) {
    printf("is function\n");
  }

  /*rewriter.ReplaceText(
    decl->getSourceRange(),
    "make_interface result here!13#5#wq@dfe");*/
  return "";
}

#else // CLING_IS_ON

int main(int argc, const char* const* argv) {
    printf("main started...\n");
    try
    {
        appLoop = new AppLoop();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    appLoop->run();
    appLoop->stop();
    delete appLoop;
    printf("main finished...\n");
    return EXIT_SUCCESS;
}

#endif // CLING_IS_ON

#if 0
namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>



auto const address = tcp::v4();//net::ip::make_address("0.0.0.0");
auto const port = static_cast<unsigned short>(8091);
auto const doc_root = std::make_shared<std::string>(".");
auto const threads = 1;

class AppLoop
{
public:
    AppLoop() : // The io_context is required for all I/O
                ioc{threads}//,
    // The acceptor receives incoming connections
    //acceptor{ioc, {address, port}}
    {
        //acceptor.set_option(tcp::acceptor::reuse_address(true));
    }

    void run();

    void stop();

    // The io_context is required for all I/O
    net::io_context ioc;

    // The acceptor receives incoming connections
    //tcp::acceptor acceptor;

    bool m_Running = true;

    //std::vector<std::function<void(bool,int)>> callbacks_;
    //std::function<void(void)> callback_;
};

AppLoop* appLoop = nullptr;

//------------------------------------------------------------------------------

// Append an HTTP rel-path to a local filesystem path.
// The returned path is normalized for the platform.
std::string
path_cat(
    beast::string_view base,
    beast::string_view path)
{
    if(base.empty())
        return path.to_string();
    std::string result = base.to_string();
#if BOOST_MSVC
    char constexpr path_separator = '\\';
    if(result.back() == path_separator)
        result.resize(result.size() - 1);
    result.append(path.data(), path.size());
    for(auto& c : result)
        if(c == '/')
            c = path_separator;
#else
    char constexpr path_separator = '/';
    if(result.back() == path_separator)
        result.resize(result.size() - 1);
    result.append(path.data(), path.size());
#endif
    return result;
}

// This function produces an HTTP response for the given
// request. The type of the response object depends on the
// contents of the request, so the interface requires the
// caller to pass a generic lambda for receiving the response.
template<
    class Body, class Allocator,
    class Send>
void
handle_request(
    beast::string_view doc_root,
    http::request<Body, http::basic_fields<Allocator>>&& req,
    Send&& send)
{
    /*cling::Interpreter::CompilationResult compilationResult1;
    interpMap["http_callbacks_module"]->metaProcessor_->process("printf(\"http_callbacks123\n\");", compilationResult1, nullptr, true);*/
    //printf("http_callbacks2 is %i\n", http_callbacks2());
    //printf("http_callbacks1 is %i\n", http_callbacks1);

#ifdef CLING_IS_ON // TODO
    printf("getAnotherGlobal is %f\n", getAnotherGlobal());
#endif // CLING_IS_ON

    /*if(appLoop->callback_) {
        appLoop->callback_();
    }*/

    // Returns a bad request response
    auto const bad_request =
        [&req](beast::string_view why)
    {
        http::response<http::string_body> res{http::status::bad_request, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/html");
        res.keep_alive(req.keep_alive());
        res.body() = why.to_string();
        res.prepare_payload();
        return res;
    };

    // Returns a not found response
    auto const not_found =
        [&req](beast::string_view target)
    {
        http::response<http::string_body> res{http::status::not_found, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/html");
        res.keep_alive(req.keep_alive());
        res.body() = "The resource '" + target.to_string() + "' was not found.";
        res.prepare_payload();
        return res;
    };

    // Returns a server error response
    auto const server_error =
        [&req](beast::string_view what)
    {
        http::response<http::string_body> res{http::status::internal_server_error, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/html");
        res.keep_alive(req.keep_alive());
        res.body() = "An error occurred: '" + what.to_string() + "'";
        res.prepare_payload();
        return res;
    };

    // Make sure we can handle the method
    if( req.method() != http::verb::get &&
        req.method() != http::verb::head)
        return send(bad_request("Unknown HTTP-method"));

    // Request path must be absolute and not contain "..".
    if( req.target().empty() ||
        req.target()[0] != '/' ||
        req.target().find("..") != beast::string_view::npos)
        return send(bad_request("Illegal request-target"));

    // Build the path to the requested file
    std::string path = path_cat(doc_root, req.target());
    if(req.target().back() == '/')
        path.append("index.html");

    // Attempt to open the file
    beast::error_code ec;
    http::file_body::value_type body;
    body.open(path.c_str(), beast::file_mode::scan, ec);

    // Handle the case where the file doesn't exist
    if(ec == beast::errc::no_such_file_or_directory)
        return send(not_found(req.target()));

    // Handle an unknown error
    if(ec)
        return send(server_error(ec.message()));

    // Cache the size since we need it after the move
    auto const size = body.size();

    // Respond to HEAD request
    if(req.method() == http::verb::head)
    {
        http::response<http::empty_body> res{http::status::ok, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, mime_type(path));
        res.content_length(size);
        res.keep_alive(req.keep_alive());
        return send(std::move(res));
    }

    // Respond to GET request
    http::response<http::file_body> res{
        std::piecewise_construct,
        std::make_tuple(std::move(body)),
        std::make_tuple(http::status::ok, req.version())};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, mime_type(path));
    res.content_length(size);
    res.keep_alive(req.keep_alive());
    return send(std::move(res));
}

//------------------------------------------------------------------------------

// Report a failure
void
fail(beast::error_code ec, char const* what)
{
    std::cerr << "fail: " << what << ": " << ec.message() << "\n";
}

// Handles an HTTP server connection
class session : public std::enable_shared_from_this<session>
{
    // This is the C++11 equivalent of a generic lambda.
    // The function object is used to send an HTTP message.
    struct send_lambda
    {
        session& self_;

        explicit
            send_lambda(session& self)
            : self_(self)
        {
        }

        template<bool isRequest, class Body, class Fields>
        void
        operator()(http::message<isRequest, Body, Fields>&& msg) const
        {
            // The lifetime of the message has to extend
            // for the duration of the async operation so
            // we use a shared_ptr to manage it.
            auto sp = std::make_shared<
                http::message<isRequest, Body, Fields>>(std::move(msg));

            // Store a type-erased version of the shared
            // pointer in the class to keep it alive.
            self_.res_ = sp;

            // Write the response
            http::async_write(
                self_.socket_,
                *sp,
                net::bind_executor(
                    self_.strand_,
                    std::bind(
                        &session::on_write,
                        self_.shared_from_this(),
                        std::placeholders::_1,
                        std::placeholders::_2,
                        sp->need_eof())));
        }
    };

    tcp::socket socket_;
    net::strand<
        net::io_context::executor_type> strand_;
    beast::flat_buffer buffer_;
    std::shared_ptr<std::string const> doc_root_;
    http::request<http::string_body> req_;
    std::shared_ptr<void> res_;
    send_lambda lambda_;

public:
    // Take ownership of the socket
    explicit
        session(
            tcp::socket socket,
            std::shared_ptr<std::string const> const& doc_root)
        : socket_(std::move(socket))
          , strand_(socket_.get_executor())
          , doc_root_(doc_root)
          , lambda_(*this)
    {
    }

    // Start the asynchronous operation
    void
    run()
    {
        do_read();
    }

    void
    do_read()
    {
        // Make the request empty before reading,
        // otherwise the operation behavior is undefined.
        req_ = {};

        // Read a request
        http::async_read(socket_, buffer_, req_,
                         net::bind_executor(
                             strand_,
                             std::bind(
                                 &session::on_read,
                                 shared_from_this(),
                                 std::placeholders::_1,
                                 std::placeholders::_2)));
    }

    void
    on_read(
        beast::error_code ec,
        std::size_t bytes_transferred)
    {
        boost::ignore_unused(bytes_transferred);

        // This means they closed the connection
        if(ec == http::error::end_of_stream)
            return do_close();

        if(ec)
            return fail(ec, "read");

        // Send the response
        handle_request(*doc_root_, std::move(req_), lambda_);
    }

    void
    on_write(
        beast::error_code ec,
        std::size_t bytes_transferred,
        bool close)
    {
        boost::ignore_unused(bytes_transferred);

        if(ec)
            return fail(ec, "write");

        if(close)
        {
            // This means we should close the connection, usually because
            // the response indicated the "Connection: close" semantic.
            return do_close();
        }

        // We're done with the response so delete it
        res_ = nullptr;

        // Read another request
        do_read();
    }

    void
    do_close()
    {
        // Send a TCP shutdown
        beast::error_code ec;
        socket_.shutdown(tcp::socket::shutdown_send, ec);

        // At this point the connection is closed gracefully
    }
};

//------------------------------------------------------------------------------

// Accepts incoming connections and launches the sessions
class listener : public std::enable_shared_from_this<listener>
{
    tcp::acceptor acceptor_;
    tcp::socket socket_;
    std::shared_ptr<std::string const> doc_root_;

public:
    listener(
        net::io_context& ioc,
        tcp::endpoint endpoint,
        std::shared_ptr<std::string const> const& doc_root)
        : acceptor_(ioc)
          , socket_(ioc)
          , doc_root_(doc_root)
    {
        beast::error_code ec;

        // Open the acceptor
        acceptor_.open(endpoint.protocol(), ec);
        if(ec)
        {
            fail(ec, "open");
            return;
        }

        // Allow address reuse
        acceptor_.set_option(net::socket_base::reuse_address(true), ec);
        if(ec)
        {
            fail(ec, "set_option");
            return;
        }

        // Bind to the server address
        acceptor_.bind(endpoint, ec);
        if(ec)
        {
            fail(ec, "bind");
            return;
        }

        // Start listening for connections
        acceptor_.listen(
            net::socket_base::max_listen_connections, ec);
        if(ec)
        {
            fail(ec, "listen");
            return;
        }
    }

    // Start accepting incoming connections
    void
    run()
    {
        if(!acceptor_.is_open())
            return;
        do_accept();
    }

    void
    do_accept()
    {
        acceptor_.async_accept(
            socket_,
            std::bind(
                &listener::on_accept,
                shared_from_this(),
                std::placeholders::_1));
    }

    void
    on_accept(beast::error_code ec)
    {
        if(ec)
        {
            fail(ec, "accept");
        }
        else
        {
            // Create the session and run it
            std::make_shared<session>(
                std::move(socket_),
                doc_root_)->run();
        }

        // Accept another connection
        do_accept();
    }
};


void AppLoop::run() {
    try
    {
        // Create and launch a listening port
        std::make_shared<listener>(
            ioc,
            tcp::endpoint{address, port},
            doc_root)->run();

        // Run the I/O service on the requested number of threads
        std::vector<std::thread> v;
        v.reserve(threads - 1);
        for(auto i = threads - 1; i > 0; --i)
            v.emplace_back(
                [/*&ioc*/this]
                {
                    ioc.run();
                });
        ioc.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void AppLoop::stop() {
    m_Running = false;
    //acceptor.cancel();
    //acceptor.close();
    //acceptor.release();
    //ioc.restart();
    ioc.stop();
    ioc.reset();
}

#if defined(CLING_IS_ON)

static void main_module_cling_prepare() {
    printf("called app_loop_prepare\n");
    //MyTest1();

    try
    {
        appLoop = new AppLoop();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

/*static void main_module_cling_run_update() {
    printf("called app_loop_run_update\n");
}*/

static void main_module_cling_run() {
    printf("called app_loop_run\n");

    appLoop->run();
}

static void main_module_cling_shutdown() {
    printf("called app_loop_shutdown\n");
    appLoop->stop();
    delete appLoop;
}

void app_loop() {
    printf("loaded app_loop with CLING\n");
}

#else // CLING_IS_ON

int main(int argc, const char* const* argv) {
    printf("main started...\n");
    try
    {
        appLoop = new AppLoop();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    appLoop->run();
    appLoop->stop();
    delete appLoop;
    printf("main finished...\n");
    return EXIT_SUCCESS;
}

#endif // CLING_IS_ON
#endif // 0

