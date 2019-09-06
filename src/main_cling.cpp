// see https://github.com/bisegni/chaosframework/blob/master/chaos/common/script/cling/CPPScriptVM.cpp
// see https://github.com/galsasson/ofxCling
// see https://github.com/0xfd000000/qling/blob/22e56c4be0bbccb1d0437f610bfa37374b44b87f/qling/qling.cpp


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
#include <optional>
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

#include <experimental/filesystem>

#include "types_for_erasure.hpp"
#include "type_erasure_my_interface.hpp"
#include "type_erasure_my_interface_externs.hpp"
#include "type_erasure_my_interface2.hpp"
#include "type_erasure_my_interface2_externs.hpp"
#include "type_erasure_my_interface_my_interface2.hpp"
#include "type_erasure_my_interface_my_interface2_externs.hpp"

namespace fs = std::experimental::filesystem;

#include "someEnum.hpp"

#include "jinja2cpp/value.h"
#include "jinja2cpp/template.h"

#include "funcParser.h"

#include "clangUtils.h"

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

static std::mutex clingReadyMutex;
static std::condition_variable clingReadyCV;
static bool isClingReady = false;

/*
 * DispatchQueue: Based on
 * https://embeddedartistry.com/blog/2017/2/1/c11-implementing-a-dispatch-queue-using-stdfunction
 **/
class DispatchQueue {
public:
    typedef std::function<void(void)> dispatch_callback;

    DispatchQueue(const std::string& name, const size_t thread_cnt = 1);
    ~DispatchQueue();

    // dispatch and copy
    void dispatch(const dispatch_callback& op);
    // dispatch and move
    void dispatch(dispatch_callback&& op);

    // Deleted operations
    // TODO
    DispatchQueue(const DispatchQueue& rhs) = delete;
    DispatchQueue& operator=(const DispatchQueue& rhs) = delete;
    DispatchQueue(DispatchQueue&& rhs) = delete;
    DispatchQueue& operator=(DispatchQueue&& rhs) = delete;

    // private:
    std::string name_;
    std::mutex lock_;
    std::vector<std::thread> threads_;
    std::queue<dispatch_callback> callbacksQueue_;
    std::condition_variable cv_;
    bool quit_ = false;

    void dispatch_loop(void);

    void DispatchQueued(void);

    void clear();

    bool isEmpty() {
        std::scoped_lock<std::mutex> lock(lock_);
        return threads_.empty();
    }
};


DispatchQueue::DispatchQueue(const std::string& name, const size_t thread_cnt)
    : name_(name), threads_(thread_cnt) {

    // NOTE: threads_.size() may be 0 -> use parent thread
    for (size_t i = 0; i < threads_.size(); i++) {
        threads_[i] = std::thread(&DispatchQueue::dispatch_loop, this); // TODO: this in constructor
    }
}

DispatchQueue::~DispatchQueue() {

    // Signal to dispatch threads that it's time to wrap up
    std::unique_lock<std::mutex> lock(lock_);
    quit_ = true;

    /*while (!callbacksQueue_.empty())
    callbacksQueue_.pop();*/

    lock.unlock();
    cv_.notify_all();

    // NOTE: threads_.size() may be 0 -> use parent thread
    // Wait for threads to finish before we exit
    for (size_t i = 0; i < threads_.size(); i++) {
        if (threads_[i].joinable()) {
            llvm::outs() << "Destructor: Joining thread " << i << " until completion";
            threads_[i].join();
        }
    }
}

void DispatchQueue::dispatch(const dispatch_callback& op) {
    std::unique_lock<std::mutex> lock(lock_);
    callbacksQueue_.push(op);

    // Manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again (see notify_one for details)
    lock.unlock();
    cv_.notify_all();
}

void DispatchQueue::dispatch(dispatch_callback&& op) {
    std::unique_lock<std::mutex> lock(lock_);
    callbacksQueue_.push(std::move(op));

    // Manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again (see notify_one for details)
    lock.unlock();
    cv_.notify_all();
}

// NOTE: Runs in loop and blocks execution (if runs in same thread)
void DispatchQueue::dispatch_loop(void) {
    std::unique_lock<std::mutex> lock(lock_);

    do {
        // Wait until we have data or a quit signal
        cv_.wait(lock, [this] { return (callbacksQueue_.size() || quit_); });

        // after wait, we own the lock
        if (!quit_ && callbacksQueue_.size()) {
            auto dispatchCallback = std::move(callbacksQueue_.front());
            callbacksQueue_.pop();

            // unlock now that we're done messing with the queue
            lock.unlock();

            dispatchCallback();

            lock.lock();
        }
    } while (!quit_);

    lock.unlock();
}

void DispatchQueue::clear() {
    std::unique_lock<std::mutex> lock(lock_);

    while (!callbacksQueue_.empty())
        callbacksQueue_.pop();
}

void DispatchQueue::DispatchQueued(void) {
    std::unique_lock<std::mutex> lock(lock_);

    do {
        if (!quit_ && callbacksQueue_.size()) {
            auto dispatchCallback = std::move(callbacksQueue_.front());
            callbacksQueue_.pop();

            // unlock now that we're done messing with the queue
            lock.unlock();

            dispatchCallback();

            lock.lock();
        }
    } while (callbacksQueue_.size() && !quit_);

    lock.unlock();
}

/// Definitions of declarations injected also into cling.
/// NOTE: this could also stay in a header #included here and into cling, but
/// for the sake of simplicity we just redeclare them here.
static int aGlobal = 42;
static float anotherGlobal = 3.141;
float getAnotherGlobal() { return anotherGlobal; }
void setAnotherGlobal(float val) { anotherGlobal = val; }

///\brief Call compiled functions from the interpreter.
void useHeader(cling::Interpreter& interp) {
    // We could use a header, too...
    interp.declare("int aGlobal;\n"
                   "float getAnotherGlobal();\n"
                   "void setAnotherGlobal(float val);\n");

    cling::Value res; // Will hold the result of the expression evaluation.
    interp.process("aGlobal;", &res);
    llvm::outs() << "aGlobal is " << res.getAs<long long>() << '\n';
    interp.process("getAnotherGlobal();", &res);
    llvm::outs() << "getAnotherGlobal() returned " << res.getAs<float>() << '\n';

    setAnotherGlobal(1.); // We modify the compiled value,
    interp.process("getAnotherGlobal();", &res); // does the interpreter see it?
    llvm::outs() << "getAnotherGlobal() returned " << res.getAs<float>() << '\n';

    // We modify using the interpreter, now the binary sees the new value.
    interp.process("setAnotherGlobal(7.777); getAnotherGlobal();");
    llvm::outs() << "getAnotherGlobal() returned " << getAnotherGlobal() << '\n';
}

///\brief Call an interpreted function using its symbol address.
void useSymbolAddress(cling::Interpreter& interp) {
    // Declare a function to the interpreter. Make it extern "C" to remove
    // mangling from the game.
    interp.declare("extern \"C\" int plutification(int siss, int sat) "
                   "{ return siss * sat; }");
    void* addr = interp.getAddressOfGlobal(llvm::StringRef("plutification"));
    using func_t = int(int, int);
    func_t* pFunc = cling::utils::VoidToFunctionPtr<func_t*>(addr);
    llvm::outs() << "7 * 8 = " << pFunc(7, 8) << '\n';
}

///\brief Pass a pointer into cling as a string.
void usePointerLiteral(cling::Interpreter& interp) {
    int res = 17; // The value that will be modified

    // Update the value of res by passing it to the interpreter.
    std::ostringstream sstr;
    // on Windows, to prefix the hexadecimal value of a pointer with '0x',
    // one need to write: std::hex << std::showbase << (size_t)pointer
    sstr << "int& ref = *(int*)" << std::hex << std::showbase << (size_t)&res << ';';
    sstr << "ref = ref * ref;";
    interp.process(sstr.str());
    llvm::outs() << "The square of 17 is " << res << '\n';
}

#if !defined(LLVMDIR)
#error "LLVMDIR not defined"
#endif

/*float MyTest() {
    return 98;
}*/


std::string readWholeFile(const std::string& file_path) {
    std::ifstream file_stream(file_path, std::ios::binary);
    return std::string((std::istreambuf_iterator<char>(file_stream)),
                       std::istreambuf_iterator<char>());
}

void processCode(cling::Interpreter& interp, const std::string& code) {
    cling::Value res; // Will hold the result of the expression evaluation.
    interp.process(code.c_str(), &res);
}

void executeCode(cling::Interpreter& interp, const std::string& code) {
    interp.execute(code.c_str());
}

#if 0
std::map<std::string, cling::Transaction*> lastFileLoadTransactions;
void reloadFile(cling::Interpreter& interp, const std::string& filename) {
    /*auto it = lastFileLoadTransactions.find(filename);
    if (it != lastFileLoadTransactions.end()) {
        llvm::outs() << "unload " << filename << " ... " << '\n';
        interp.unload(*it->second);
    }*/

/*#include <iosfwd>
#include <exception> 		// For ios_base::failure
#include <bits/char_traits.h> 	// For char_traits, streamoff, streamsize, fpos
#include <bits/localefwd.h>	// For class locale
#include <bits/ios_base.h>	// For ios_base declarations.
#include <streambuf>
#include <bits/basic_ios.h>

#include <ios>
#include <bits/ostream_insert.h>*/
    {
        llvm::outs() << "load " << filename << " ... " << '\n';
        cling::Interpreter::PushTransactionRAII ScopedT1(&interp);
        /*interp.loadFile("string");
        interp.loadFile("sstream");
        interp.loadFile("fstream");
        interp.loadFile("streambuf");*/
        //interp.loadFile(filename.c_str(), false);
        interp.enableDynamicLookup(true);
        interp.enableRawInput(true);
        //interp.declare(readWholeFile(filename.c_str()));
        interp.process(readWholeFile(filename.c_str()));
        interp.enableDynamicLookup(false);
        interp.enableRawInput(false);
        interp.process("#define IS_FILE_LOADED_BY_CLING");
    }
    lastFileLoadTransactions[filename]
        = const_cast<cling::Transaction*>(interp.getLastTransaction());
    //interp.enablePrintDebug(false);
}

void reloadAllFiles(cling::Interpreter& interp) {
    for(const auto& it : lastFileLoadTransactions) {
        reloadFile(interp, it.first);
    }
}
#endif

class InterpreterModule {
public:
    InterpreterModule(const std::string& id, const std::vector<std::string>& moduleFiles)
        : id_(id)
          , moduleFiles_(moduleFiles)
          //, moduleThread(&InterpreterModule::threadMain, this)
    {
        for(const auto& it: moduleFiles_) {
            printf("moduleFiles_ module %s\n", it.c_str());
        }
        //moduleThread.detach();
        createInterpreter();
    }

    ~InterpreterModule() {
        cling::Interpreter::CompilationResult compilationResult;
        metaProcessor_->process(id_ + "_cling_shutdown();", compilationResult, nullptr, true);
    }

    void createInterpreter() {
        std::vector<std::string> cling_args_storage;
        cling_args_storage.push_back("EmbedCling");
        cling_args_storage.push_back("-I.");
        cling_args_storage.push_back("-I../");

        //cling_args_storage.push_back("-nobuiltininc");
        //cling_args_storage.push_back("-nostdinc");

        //cling_args_storage.push_back("std=c++17");
        //cling_args_storage.push_back("-std=c++17");
        cling_args_storage.push_back("--std=c++17");
        //cling_args_storage.push_back("--std=c++2a");
        //cling_args_storage.push_back("-fmodules-ts");

        cling_args_storage.push_back("-I../cling-build/build/lib/clang/5.0.0/include");
        cling_args_storage.push_back("-I../cling-build/src/include/");
        cling_args_storage.push_back("-I../cling-build/build/include/");
        cling_args_storage.push_back("-I../cling-build/src/tools/clang/include/");
        cling_args_storage.push_back("-I../cling-build/build/tools/clang/include/");
        cling_args_storage.push_back("-I../cling-build/src/tools/cling/include/");

        cling_args_storage.push_back("-I../submodules/Jinja2Cpp/thirdparty/nonstd/expected-light/include/");

        cling_args_storage.push_back("-I../resources");

        // https://stackoverflow.com/a/30877725
        cling_args_storage.push_back("-DBOOST_SYSTEM_NO_DEPRECATED");
        cling_args_storage.push_back("-DBOOST_ERROR_CODE_HEADER_ONLY");
        // https://jinja2cpp.dev/docs/build_and_install.html#dependency-management-modes
        cling_args_storage.push_back("-Dvariant_CONFIG_SELECT_VARIANT=variant_VARIANT_NONSTD");

        //cling_args_storage.push_back("-I/usr/local/tander/i586-pc-linux-gnu/usr/lib/gcc/i586-pc-linux-gnu/7.3.0/include/g++-v7/");
        //cling_args_storage.push_back("-I/usr/local/tander/i586-pc-linux-gnu/usr/lib/gcc/i586-pc-linux-gnu/7.3.0/include/g++-v7/i586-pc-linux-gnu/");
        //cling_args_storage.push_back("-I/usr/local/tander/i586-pc-linux-gnu/usr/include/");

        //cling_args_storage.push_back("-I/usr/include/c++/8/");
        //cling_args_storage.push_back("-I/usr/include/c++/7/");

        //cling_args_storage.push_back("-I/usr/include/x86_64-linux-gnu/");

        std::vector< const char* > interp_args;
        {
            std::vector< std::string >::const_iterator iarg;
            for( iarg = cling_args_storage.begin() ; iarg != cling_args_storage.end() ; ++iarg ) {
                interp_args.push_back(iarg->c_str());
            }
        }
        interpreter_ = std::make_unique<cling::Interpreter>(
            interp_args.size(), &(interp_args[0]), LLVMDIR/*, {}, false*/);
        interpreter_->AddIncludePath(".");
        interpreter_->AddIncludePath("../");
        //interpreter_->process("#include <iostream>\n");
        //interpreter_->process("#include <string>\n");
        //interpreter_->process("#include <optional>\n");
        interpreter_->enableDynamicLookup(true);
        metaProcessor_ = std::make_unique<cling::MetaProcessor>(*interpreter_, llvm::outs());

        interpreter_->process("#define CLING_IS_ON 1");

        interpreter_->declare("int aGlobal;\n"
                       "float getAnotherGlobal();\n"
                       "void setAnotherGlobal(float val);\n");

        /*interpreter_->process("#include <string>");
        interpreter_->process("#include <map>");
        interpreter_->process("#include <memory>");

        interpreter_->declare("std::map<std::string, std::unique_ptr<InterpreterModule>> interpMap;\n");*/

        printf("created module %s\n", id_.c_str());
    }

    void prepare() {
        cling::Interpreter::CompilationResult compilationResult;

        for(const auto& it: moduleFiles_) {
            printf("processes module %s\n", it.c_str());
            metaProcessor_->process(".x " + it, compilationResult, nullptr, true);
        }

        metaProcessor_->process(id_ + "_cling_prepare();", compilationResult, nullptr);
    }

    /*void run_update() {
        cling::Interpreter::CompilationResult compilationResult;

        metaProcessor_->process(id_ + "_cling_run_update();", compilationResult, nullptr, true);
    }*/

    void run() {
        std::thread module_main([this](){
            cling::Interpreter::CompilationResult compilationResult;
            metaProcessor_->process(id_ + "_cling_run();", compilationResult, nullptr, true);
        });
        module_main.detach();
    }

public:
    std::string id_;
    std::vector<std::string> moduleFiles_;
    std::unique_ptr<cling::Interpreter> interpreter_;
    std::unique_ptr<cling::MetaProcessor> metaProcessor_;
    //std::thread moduleThread;
    //std::mutex canRunMutex;
    //bool canRun = true;
};

//static cling::MetaProcessor* m_metaProcessor1 = nullptr;
static std::map<std::string, std::unique_ptr<InterpreterModule>> interpMap;

/*struct animal
{
    std::string name;
    int legs;
};*/

/*typedef boost::multi_index_container<
    std::unique_ptr<InterpreterModule>,
  boost::indexed_by<
    boost::random_access<>,  // keep insertion order
        boost::ordered_non_unique< member<some, long, &some::key> >
        >
> InterpreterModuleContainer;*/

/// \note module loading order is important
static std::map<std::string, std::vector<std::string>> moduleToSources {
    /// \note module with app loop must be loaded last
    {
        "main_module",
        std::vector<std::string>{
            "../src/app_loop.cpp"
        }
    }
    /*{
        "http_callbacks_module",
        std::vector<std::string>{
            "/home/denis/workspace/cling-cmake/src/http_callbacks.cpp"
        }
    },
    /// \note module with app loop must be loaded last
    {
        "main_module",
        std::vector<std::string>{
            "/home/denis/workspace/cling-cmake/src/mime_type.cpp",
            /// \note file with app loop must be loaded last
            "/home/denis/workspace/cling-cmake/src/app_loop.cpp"
        }
    }*/
};

void removeClingModule(const std::string& module_id) {
    if(interpMap.find(module_id) != interpMap.end()) {
        printf("erased module %s\n", module_id.c_str());
        interpMap.erase(module_id);
    } else {
        printf("module not found! %s\n", module_id.c_str());
        for(const auto& it : interpMap) {
            printf("maybe you wanted to type %s?\n", it.first.c_str());
        }
    }
}

static std::shared_ptr<DispatchQueue> receivedMessagesQueue_;

void reloadClingModule(const std::string& module_id, const std::vector<std::string>& sources) {
    interpMap[module_id] = std::make_unique<InterpreterModule>(
        module_id.c_str(),
        sources);
    interpMap[module_id]->prepare();
    interpMap[module_id]->run();
}

// NOTE: run under mutex
void reloadAllCling() {
    /*cling::Interpreter::CompilationResult compilationResult1;
    if(interpMap.find("main_module") != interpMap.end() &&
        interpMap["main_module"]->metaProcessor_) {
        printf("app_loop_shutdown for main_module\n");
        interpMap["main_module"]->metaProcessor_->process("app_loop_shutdown();", compilationResult1, nullptr, true);
        //delete interpMap["main_module"]->metaProcessor_;
    }*/

    /// \note remove all old modules and create new modules
    for(const auto& it : interpMap) {
        printf("erased module %s\n", it.first.c_str());
        interpMap.erase(it.first);
    }

    llvm::outs() << "LLVMDIR is " << LLVMDIR << '\n';

    for(const auto& it : moduleToSources) {
        reloadClingModule(it.first, it.second);
        /*interpMap[it.first] =
            std::make_unique<InterpreterModule>(it.first, it.second);
        interpMap[it.first]->prepare();
        interpMap[it.first]->run();*/
        llvm::outs() << "reloaded module " << it.first << '\n';
    }

    //main_module.AddIncludePath("/usr/include/c++/8/");
    //main_module.AddIncludePath("/usr/include/x86_64-linux-gnu/");

    //main_module->getCI()->getPreprocessorOpts().DisablePCHValidation = true;

    // Use a stream that doesn't close its file descriptor.
    //static llvm::raw_fd_ostream fMPOuts (STDOUT_FILENO, /* ShouldClose */ false);

    /*
 *
    Interpreter(const Interpreter& parentInterpreter, int argc,
                const char* const* argv, const char* llvmdir = 0,
                const ModuleFileExtensions& moduleExtensions = {},
                bool noRuntime = true);
 * */

    //m_metaProcessor1->process("#include <iostream>", compilationResult1, nullptr, true);
    //m_metaProcessor1->process(".printAST", compilationResult1, nullptr, true);
    //m_metaProcessor1->process("#include <iostream>", compilationResult1, nullptr, true);
    //m_metaProcessor1->process(".x /home/denis/workspace/cling-cmake/src/MyTest1H.h", compilationResult1, nullptr, true);
    //m_metaProcessor1->process("using llvm::outs();", compilationResult1, nullptr);
    //m_metaProcessor1->process("using std::endl;", compilationResult1, nullptr);
    //m_metaProcessor1->process("llvm::outs() << \"cout1 called\" << "\n";", compilationResult1, nullptr);

    //m_metaProcessor1->process(".x /home/denis/workspace/cling-cmake/src/MyTest1.cpp", compilationResult1, nullptr, true);

    // Create the Interpreter. LLVMDIR is provided as -D during compilation.
    //cling::Interpreter interp2(main_module, interp_args.size(), &(interp_args[0]), LLVMDIR/*, {}, true*/);
    cling::Value res; // Will hold the result of the expression evaluation.
    //interp2.process("#include <iostream>", &res);
    //interp2.process("llvm::outs() << \"cout 12 called\" << "\n";", &res);

    /*cling::MetaProcessor* m_metaProcessor2 = new cling::MetaProcessor(interp2, llvm::outs());*/
    /*cling::MetaProcessor* m_metaProcessor2 = new cling::MetaProcessor(interp2, llvm::outs());*/

    /*cling::Interpreter::CompilationResult compilationResult2;

    //m_metaProcessor2->process("#include <iostream>", compilationResult2, nullptr);
    m_metaProcessor2->process("using llvm::outs();", compilationResult2, nullptr);
    m_metaProcessor2->process("using std::endl;", compilationResult2, nullptr);*/
    ///m_metaProcessor2->process("llvm::outs() << \"cout2 called\" << "\n";", compilationResult2, nullptr);
    //m_metaProcessor1->process("llvm::outs() << \"cout2 called\" << "\n";", compilationResult1, nullptr);

    /*interpMap["main_module"]->metaProcessor_->process(".x /home/denis/workspace/cling-cmake/src/app_loop.cpp", compilationResult2, nullptr, true);*/

    /*m_metaProcessor1->process("#include <string>", compilationResult, nullptr);
    m_metaProcessor1->process("std::string s;", compilationResult, nullptr);
    main_module.unload(1);
    m_metaProcessor2->process("std::string s;", compilationResult, nullptr);*/

    /*cling::Interpreter::CompilationResult compilationResult;
    interpMap["main_module"]->metaProcessor_->process("app_loop_prepare();", compilationResult, nullptr);*/

    // TODO: free mem
    //delete m_metaProcessor1;
    //delete m_metaProcessor2;
}

//static bool runFlag = true;
//static std::mutex m_runFlagMutex;

[[ noreturn ]] void input_func()
{
    llvm::outs() << "main cling input thread... " << '\n';
    std::string command;
    std::string command_param1;
    std::string command_param2;
    while(true) {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin >> command;
        llvm::outs() << "in main cling input thread: "<< command << '\n';
        if (command == "q") {
            //std::scoped_lock lock(m_runFlagMutex);
            //runFlag = false;
            break;
        } else if (command == "reload_all") {
            //std::scoped_lock lock(interpMap["main_module"]->canRunMutex);
            //reloadAllCling(); // NOTE: run under mutex
            receivedMessagesQueue_->dispatch([] {
                llvm::outs() << "dispatch reloadAllCling 2!... " << '\n';
                reloadAllCling();
            });
        }  else if (command == "reload_file") {
            std::cin >> command_param1 >> command_param2;
            {
                //std::scoped_lock lock(interpMap["main_module"]->canRunMutex);
                receivedMessagesQueue_->dispatch([command_param1, command_param2] {
                    llvm::outs() << "dispatch reload_file 1!... " << '\n';
                    cling::Interpreter::CompilationResult compilationResult;
                    interpMap[command_param1.c_str()]->metaProcessor_->process(".x " + command_param2, compilationResult, nullptr, true);
                });
            }
        } else if (command == "reload_module") {
            std::cin >> command_param1;
            {
                //std::scoped_lock lock(interpMap["main_module"]->canRunMutex);
                if(moduleToSources.find(command_param1) != moduleToSources.end()) {
                    //removeClingModule(command_param1);
                    receivedMessagesQueue_->dispatch([command_param1] {
                        llvm::outs() << "dispatch reloadClingModule 1!... " << '\n';
                        reloadClingModule(command_param1,
                                          moduleToSources[command_param1]);
                    });
                } else {
                    llvm::outs() << "UNKNOWN MODULE! " << '\n';
                }
            }
        } else if (command == "unload") {
            unsigned int times = 1;
            std::cin >> command_param1 >> times;
            {
                //std::scoped_lock lock(interpMap["main_module"]->canRunMutex);
                receivedMessagesQueue_->dispatch([command_param1, times] {
                    llvm::outs() << "dispatch unload 1!... " << '\n';
                    interpMap[command_param1]->interpreter_->unload(times);
                });
            }
        } else if (command == "process_code") {
            std::cin >> command_param1;
            std::getline(std::cin, command_param1);
            llvm::outs() << "command_param: " << command_param1 << '\n';
            {
                //std::scoped_lock lock(interpMap["main_module"]->canRunMutex);
                receivedMessagesQueue_->dispatch([command_param1, command_param2] {
                    llvm::outs() << "dispatch process_code 1!... " << '\n';
                    processCode(*interpMap[command_param1.c_str()]->interpreter_, command_param2);
                });
            }
        } else if (command == "execute_code") {
            std::cin >> command_param1;
            std::getline(std::cin, command_param1);
            llvm::outs() << "command_param: " << command_param1 << '\n';
            {
                //std::scoped_lock lock(interpMap["main_module"]->canRunMutex);
                receivedMessagesQueue_->dispatch([command_param1, command_param2] {
                    llvm::outs() << "dispatch execute_code 1!... " << '\n';
                    executeCode(*interpMap[command_param1.c_str()]->interpreter_, command_param2);
                });
            }
        } else if (command == "declare") {
            std::cin >> command_param1;
            std::getline(std::cin, command_param1);
            llvm::outs() << "command_param: " << command_param1 << '\n';
            {
                //std::scoped_lock lock(interpMap["main_module"]->canRunMutex);
                receivedMessagesQueue_->dispatch([command_param1, command_param2] {
                    llvm::outs() << "dispatch declare 1!... " << '\n';
                    interpMap[command_param1.c_str()]->interpreter_->declare(command_param2);
                });
            }
        } else if (command == "execute_code_from_file") {
            /// note file must be without UTF BOM
            std::cin >> command_param1 >> command_param2;
            {
                //std::scoped_lock lock(interpMap["main_module"]->canRunMutex);
                receivedMessagesQueue_->dispatch([command_param1, command_param2] {
                    llvm::outs() << "dispatch execute_code_from_file 1!... " << '\n';
                    processCode(*interpMap[command_param1.c_str()]->interpreter_, readWholeFile(command_param2));
                });
            }
            /*interp.emitAllDecls(const_cast<cling::Transaction*>(interp.getCurrentTransaction()));*/
        } else {
            llvm::outs() << "UNKNOWN COMMAND! " << '\n';
        }
        /*m_metaProcessor1->process(".x /home/denis/workspace/cling-cmake/src/MyTest1.cpp", compilationResult2, nullptr, true);*/
    }

    llvm::outs() << "end input_func! " << '\n';
    std::terminate();
}

[[ noreturn ]] void cling_func() {
    receivedMessagesQueue_ =
        std::make_shared<DispatchQueue>(std::string{"Cling Dispatch Queue"}, 0);

    receivedMessagesQueue_->dispatch([] {
        llvm::outs() << "dispatch reloadAllCling 1!... " << '\n';
        reloadAllCling();
        {
          std::unique_lock<std::mutex> lk(clingReadyMutex);
          isClingReady = true;
        }
        clingReadyCV.notify_one();
    });

    while(true) {
        receivedMessagesQueue_->DispatchQueued();
        if(receivedMessagesQueue_->isEmpty()) {
            /*for(const auto& it : interpMap) {
                interpMap[it.first]->run_update();
            }*/
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    /*receivedMessagesQueue_->dispatch([] {
        llvm::outs() << "dispatch 2!... " << '\n';
    });
    receivedMessagesQueue_->DispatchQueued();

    receivedMessagesQueue_->dispatch([] {
        llvm::outs() << "dispatch reloadAllCling 1!... " << '\n';
        reloadAllCling();
    });
    receivedMessagesQueue_->DispatchQueued();

    receivedMessagesQueue_->dispatch([] {
        llvm::outs() << "dispatch 3!... " << '\n';
    });
    receivedMessagesQueue_->DispatchQueued();*/
}


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

namespace UseOverride {
class Checker : public clang::ast_matchers::MatchFinder::MatchCallback {
public:
  using MatchResult = clang::ast_matchers::MatchFinder::MatchResult;

  Checker(/*bool RewriteOption, */clang::Rewriter &Rewriter)
      : /*RewriteOption(RewriteOption),*/ rewriter_(Rewriter) {}

  void run(const MatchResult &Result) {
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

        if (startsWithGen && startsWithFunccall) {
          code.erase(0, funccall_token.size());
          std::vector<parsed_func> parsedFuncs = split_to_funcs(code);
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
          if(interpMap.find("main_module") != interpMap.end()) {
              cling::Interpreter::CompilationResult compilationResult;
              /*interpMap["main_module"]->metaProcessor_->process(
                "#include <iostream>\n", compilationResult, nullptr, true);
              interpMap["main_module"]->metaProcessor_->process(
                "#include <string>\n", compilationResult, nullptr, true);
              interpMap["main_module"]->metaProcessor_->process(
                "#include <optional>\n", compilationResult, nullptr, true);*/
              interpMap["main_module"]->metaProcessor_->process(
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

          expandLocations(startLoc, endLoc, rewriter_);

          void* resOptionVoid = result.getAs<void*>();
          auto resOption = static_cast<llvm::Optional<std::string>*>(resOptionVoid);
          if(resOption->hasValue()) {
            rewriter_.ReplaceText(
              SourceRange(startLoc, endLoc),
              resOption->getValue());
          }
        } else if(isEval) {
          llvm::outs() << "eval for code: "
            << code << "\n";
          std::ostringstream sstr;
          sstr << code;
          if(interpMap.find("main_module") != interpMap.end()) {
              cling::Value result;
              cling::Interpreter::CompilationResult compilationResult;
              interpMap["main_module"]->metaProcessor_->process(
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

          expandLocations(startLoc, endLoc, rewriter_);

          /*rewriter_.InsertText(startLoc, " 2startLoc ");
          rewriter_.InsertText(endLoc, " 2endLoc ");*/

          rewriter_.ReplaceText(
            SourceRange(startLoc, endLoc),
            "");
        } else if(isExport) {
          llvm::outs() << "export for code: "
            << code << "\n";
          std::ostringstream sstr;
          sstr << code;
          if(interpMap.find("main_module") != interpMap.end()) {
              cling::Value result;
              cling::Interpreter::CompilationResult compilationResult;
              interpMap["main_module"]->metaProcessor_->process(
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

          expandLocations(startLoc, endLoc, rewriter_);

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
        } else if(isFuncCall) {
          // Generate bindings for a decl with pyspot annotation
          //generate_bindings( *decl );
          llvm::outs() << "generator for code: "
            << code << "\n";

          cling::Value result;

          //receivedMessagesQueue_->dispatch([] {
          for (const auto& func_to_call : funcs_to_call) {
              llvm::outs() << "main_module task " << func_to_call << "!... " << '\n';
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
              // func end
              sstr << " );" << ";";
              // scope end
              sstr << "}();";
              if(interpMap.find("main_module") != interpMap.end()) {
                  cling::Interpreter::CompilationResult compilationResult;
                  interpMap["main_module"]->metaProcessor_->process(
                    sstr.str(), compilationResult, &result, true);
              }
          }
          //});
          /*rewriter_.ReplaceText(
            decl->getSourceRange(),
            result.getAs<const char*>());*/
        }
      }
    }

    //const auto *MethodDecl = Result.Nodes.getNodeAs<clang::CXXMethodDecl>("target");
    //llvm::outs() << "MethodDecl of " << MethodDecl->getName().str() << "\n";

#if 0
    const auto *Call = Result.Nodes.getNodeAs<CallExpr>("call");
    assert(Call != nullptr);

    // https://github.com/hfinkel/llvm-project-cxxjit/blob/e534054d0112ea899a7d43dbf34ba8520d247fef/clang-tools-extra/clang-tidy/performance/TypePromotionInMathFnCheck.cpp#L159
    StringRef OldFnName = Call->getDirectCallee()->getName();
    llvm::outs() << "OldFnName of " << OldFnName.str() << "\n";

    ASTContext *Context = Result.Context;
    if (const CallExpr *callExpr =
            Result.Nodes.getNodeAs<clang::CallExpr>("call")) {
      const FunctionDecl *FD = callExpr->getDirectCallee();
      FullSourceLoc FullLocationStart = Context->getFullLoc(callExpr->getLocStart());
      //FullSourceLoc FullLocationEnd = Context->getFullLoc(callExpr->getLocEnd());
      std::string fname = FD->getNameInfo().getAsString();
      if (FullLocationStart.isValid()) {
        llvm::outs() << "Found call at " << FullLocationStart.getSpellingLineNumber()
                     << ":" << FullLocationStart.getSpellingColumnNumber() << "\n";
        //rewriter_.ReplaceText(FullLocationStart, fname.length(), "add5");
        rewriter_.ReplaceText(callExpr->getSourceRange(), "sdf sdf ; 1@");
        for (size_t argIdx = 0; argIdx < callExpr->getNumArgs(); ++argIdx) {
          const clang::Expr *expr = callExpr->getArg(argIdx);
        }
      }
    }

    const auto *Target = Result.Nodes.getNodeAs<clang::CXXMethodDecl>("target");

    if (!needsOverride(*Target))
      return;

    auto &Diagnostics = Result.Context->getDiagnostics();
    const auto ID =
        Diagnostics.getCustomDiagID(clang::DiagnosticsEngine::Warning,
                                    "method '%0' should be declared override");

    clang::SourceLocation InsertionPoint =
        findInsertionPoint(*Target, *Result.Context);

    clang::DiagnosticBuilder Diagnostic =
        Diagnostics.Report(InsertionPoint, ID);
    Diagnostic.AddString(Target->getName());

    //if (RewriteOption) {
      rewriter_.InsertText(InsertionPoint, " override ");
    /*} else {
      const auto FixIt =
          clang::FixItHint::CreateInsertion(InsertionPoint, "override");
      Diagnostic.AddFixItHint(FixIt);
    }*/
#endif // 0
  }

private:
  //bool RewriteOption;

  clang::Rewriter &rewriter_;

#if 0
  bool needsOverride(const clang::CXXMethodDecl &MethodDecl) {
    if (!MethodDecl.size_overridden_methods())
      return false;
    const AttrVec &Attrs = MethodDecl.getAttrs();
    //llvm::outs() << "MethodDecl of " << MethodDecl.getName().str() << "\n";
    return std::none_of(Attrs.begin(), Attrs.end(), [](const Attr *Attr) {
      /*llvm::outs() << "Attr->getSpelling() "
        << Attr->getSpelling() << " is "
        << (strcmp(Attr->getSpelling(), "override") == 0) << "\n";
      */
      return (strcmp(Attr->getSpelling(), "override") == 0);
    });
  }

  clang::SourceLocation
  findInsertionPoint(const clang::CXXMethodDecl &MethodDecl,
                     const clang::ASTContext &Context) {
    clang::SourceLocation Location;

    /// Find the end of the parameter list.
    if (MethodDecl.param_empty()) {
      const unsigned Offset = MethodDecl.getName().size();
      Location = MethodDecl.getLocation().getLocWithOffset(Offset);
    } else {
      const clang::ParmVarDecl *Last = *std::prev(MethodDecl.param_end());
      Location = Last->getLocEnd(); // getEndLoc
    }

    Location = clang::Lexer::findLocationAfterToken(
        Location, clang::tok::r_paren, Context.getSourceManager(),
        Context.getLangOpts(),
        /*skipWhiteSpace=*/true);

    return Location.getLocWithOffset(-1);
  }
#endif // 0
};

class Consumer : public clang::ASTConsumer {
public:
  explicit Consumer(clang::Rewriter &Rewriter)
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

  void HandleTranslationUnit(clang::ASTContext &Context) override {
    Finder_.matchAST(Context);
  }

private:
  clang::ast_matchers::MatchFinder Finder_;
  Checker Checker_;
};

class Action : public clang::ASTFrontendAction {
public:
  using ASTConsumerPointer = std::unique_ptr<clang::ASTConsumer>;

  explicit Action() {}

  ASTConsumerPointer CreateASTConsumer(clang::CompilerInstance &Compiler,
                                       llvm::StringRef /*Filename*/) override {
    Rewriter.setSourceMgr(Compiler.getSourceManager(), Compiler.getLangOpts());
    return std::make_unique<Consumer>(Rewriter);
  }

  bool BeginSourceFileAction(clang::CompilerInstance &/*Compiler*/) override {
    llvm::errs() << "Processing " << getCurrentFile() << "\n\n";
    return true;
  }

  void EndSourceFileAction() override {
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

private:
  clang::Rewriter Rewriter;
};
} // namespace UseOverride

struct ToolFactory : public clang::tooling::FrontendActionFactory {
  //ToolFactory(/*clang::FrontendAction* act, std::unique_ptr<clang::ASTConsumer> consumer*/)
  //  /*: m_act(act), m_consumer(std::move(consumer))*/ {};
  clang::FrontendAction *create() override {
    return new UseOverride::Action();
  }
  //clang::FrontendAction* m_act;
  //std::unique_ptr<clang::ASTConsumer> m_consumer;
};

const std::string
getFileContent(const std::string& path)
{
  std::ifstream file(path);
  if(!file.is_open()) {
    printf("ERROR: can`t read file %s\n", path.c_str());
    return "";
  }
  std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

  return content;
}

void writeToFile(const std::string& str, const std::string& path) {
  std::ofstream file(path);
  if(!file.is_open()) {
    printf("ERROR: can`t write to file %s\n", path.c_str());
    return;
  }
  file << str;
  file.close();
}



#include <unordered_map>

//using namespace cxxctp::generated;
using cxxctp::generated::ShapeKind;

static std::unordered_map<ShapeKind, int> u = {
    {ShapeKind::Box, 1},
    {ShapeKind::Sphere, 3},
  };

void EnumTest2(ShapeKind state) {
  switch (state) {
    case ShapeKind::Box: {
        // ...
        break;
    }
    case ShapeKind::Sphere: {
        // ...
        break;
    }
    default: {
        // ...
        break;
    }
  }
}

void EnumTest1() {
  ShapeKind total = ShapeKind::TOTAL;
  llvm::outs() << "total is " << total.ToNumber() << "\n";

  ShapeKind state1 = ShapeKind::Box;
  const auto state1Str = state1.ToString();
  if(state1Str) {
    llvm::outs() << state1Str << "\n";
  }
  EnumTest2(state1);

  ShapeKind state2 = ShapeKind::FromNumber(static_cast<ShapeKind::_enumerated_t>(3));
  if(state2 != ShapeKind::TOTAL) {
    const auto state2Str = state2.ToString();
    if(state2Str) {
      llvm::outs() << state2Str << "\n";
    }
  } else {
    llvm::outs() << "state2 is TOTAL" << "\n";
  }

  EnumTest2(state2);

  auto stateNum1 = ShapeKind::ToNumber(state1);
  auto totalNum = ShapeKind::ToNumber(ShapeKind::TOTAL);
  if(stateNum1 != totalNum) {
    llvm::outs() << stateNum1 << "\n";
  } else {
    llvm::outs() << "stateNum1 is TOTAL" << "\n";
  }

  ShapeKind state3 = ShapeKind::FromString("Box");
  if(state3 != ShapeKind::TOTAL) {
    const auto state3Str = state3.ToString();
    if(state3Str) {
      llvm::outs() << state3Str << "\n";
    }
  } else {
    llvm::outs() << "state3 is TOTAL" << "\n";
  }

  llvm::outs() << "Box != TOTAL is " <<
    (ShapeKind::FromString("Box") != ShapeKind::TOTAL) << "\n";

  std::cout << "Box is " << ShapeKind::FromString("Box") << "\n";

  ShapeKind inShapeKind;
  //std::cin >> inShapeKind;

  std::cout << "inShapeKind) is " << inShapeKind.ToString() << "\n";
  std::cout << "inShapeKind is " << inShapeKind << "\n";

  EnumTest2(state3);

  ShapeKind inShapeKindToIter = ShapeKind::Box;
  for(ShapeKind::const_value_iterator it = inShapeKindToIter.values_begin();
      it != inShapeKindToIter.values_end(); ++it)
    std::cout << "it1 is " << ShapeKind::FromNumber(*it) << "\n";

  inShapeKindToIter = ShapeKind::Box;
  for(ShapeKind::const_name_iterator it = inShapeKindToIter.names_begin();
      it != inShapeKindToIter.names_end(); ++it)
    std::cout << "it names is " << ShapeKind::FromString(*it) << "\n";

  for(const auto& it : inShapeKindToIter.values_)
    std::cout << "it2 is " << ShapeKind::FromNumber(it) << "\n";

  for(const auto& it : inShapeKindToIter.names_)
    std::cout << "it3 is " << ShapeKind::FromString(it) << "\n";

  llvm::outs() << "ShapeKind::Box > ShapeKind::Sphere"
    << (ShapeKind::Box > ShapeKind::Sphere) << "\n";

  llvm::outs() << "ShapeKind::TOTAL <= ShapeKind::Sphere"
    << (ShapeKind::TOTAL <= ShapeKind::Sphere) << "\n";
}

/*std::vector<std::string> csvish_split(std::string const& s)
{
    namespace x3 = boost::spirit::x3;

    auto const quoted   = '"' >> *~x3::char_('"') >> '"';
    auto const unquoted = *~x3::char_(',');
    auto const segments = (quoted | unquoted) % ',';

    std::vector<std::string> ret;
    if (!x3::parse(cbegin(s), cend(s), segments, ret))
        throw std::runtime_error("failed to parse: " + s);
    return ret;
}*/

/*std::vector<std::string> split_args_to_funcs2(std::string const& inStr) {
  std::vector<std::string> result;
  std::istringstream iss(inStr);
  std::string s;
  while (iss >> std::quoted(s)) {
      result.push_back(s);
  }
  return result;
}*/

void test_split_to_funcs() {
  const std::string code_input = R"raw(
    make_nobody;
    make_reflect
    ("as  \"; ddddghj ;
      ; dddgj  ; dd");    make_interface('c'
    + 'b',     argname1      =     "argass  \"; argdfgdfg
      ; ardfggfgdfg  ; afggfgdfg"    ,   argname2      =  45
        ,
           argname1      =  " #\"1 \"2 \" 23" );
    make_checks; make_3
    (12345, "32  ; 5454 ;
      ; ffhfh  ; ass", "bb  ; sss ;
      ; hfhfh  ; sss",
       54321);
  make_jinja  (    1 + 2 + 3    ,    "saw3"    ,   48    );make_ref)raw";
  //const std::string code_input = R"raw("asddddddddd" ; kllklk ; "dfggg"   "bcbccbb")raw";

  for (auto const& seg : split_to_funcs(code_input)) {
      llvm::outs() << "segment: " << seg.func_with_args_as_string_ << "\n";
      llvm::outs() << "  func_name_: " << seg.parsed_func_.func_name_ << "\n";
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
  /*for (auto const& seg : csvish_split(code_input))
      llvm::outs() << seg << '\n';*/
}

namespace cxxctp {
namespace generated {
#if 0
  template<>
  void draw<template_interface<int, const std::string&>/*obj_t::typeclass_t*/>
      (const allcaps_t& data, const char* surface) noexcept {
    /// \note don`t use get_concrete<type> here, it may be get_concrete<ref_type>
    llvm::outs() << "Drawing allcaps_t on " << surface
      << " with data " << data.allcaps_t_data << "\n";
  }

  template<>
  void draw<template_interface<int, const std::string&>/*obj_t::typeclass_t*/>
      (const forward_t& data, const char* surface) noexcept {
    /// \note don`t use get_concrete<type> here, it may be get_concrete<ref_type>
    llvm::outs() << "Drawing forward_t on " << surface
      << " with data " << data.forward_t_data << "\n";
  }

  template<>
  void draw<template_interface<int, const std::string&>/*obj_t::typeclass_t*/>
      (const reverse_t& data, const char* surface) noexcept {
    /// \note don`t use get_concrete<type> here, it may be get_concrete<ref_type>
    llvm::outs() << "Drawing reverse_t on " << surface
      << " with data " << data.reverse_t_data << "\n";
  }
#endif // 0

  // ==============

  template <>
  std::string my_interface2_model_t::test_zoo<allcaps_t>(const std::string& arg) noexcept {
    /// \note use get_concrete<type> here, it is different from get_concrete<ref_type>
    allcaps_t& data = ref_concrete<allcaps_t>();
    return arg + " test_zoo for allcaps_t " + data.allcaps_t_data;
  }

  template <>
  std::string my_interface2_model_t::test_zoo<std::reference_wrapper<allcaps_t>>(const std::string& arg) noexcept {
    /// \note passes ref, not data!
    /// otherwize we won`t be able to call get_concrete<ref_type>
    /// \note get_concrete<type> differs from get_concrete<ref_type>!
    llvm::outs() << "test_zoo ref_concrete<std::reference_wrapper<allcaps_t>>()" << "\n";
    std::reference_wrapper<allcaps_t>& data = ref_concrete<std::reference_wrapper<allcaps_t>>();
    return arg + " test_zoo for allcaps_t " + data.get().allcaps_t_data;
  }

  template <>
  std::string my_interface2_model_t::test_zoo<reverse_t>(const std::string& arg) noexcept {
    /// \note use get_concrete<type> here, it is different from get_concrete<ref_type>
    reverse_t& data = ref_concrete<reverse_t>();
    return arg + " test_zoo for reverse_t " + data.reverse_t_data;
  }

  template <>
  std::string my_interface2_model_t::test_zoo<forward_t>(const std::string& arg) noexcept {
    /// \note use get_concrete<type> here, it is different from get_concrete<ref_type>
    forward_t& data = ref_concrete<forward_t>();
    return arg + " test_zoo for forward_t " + data.forward_t_data;
  }

  // ==============

#if 0
  template<typename A>
  std::string _tc_impl_t<allcaps_t, my_interface2>::
      show(allcaps_t const &, A const & arg2) noexcept {
    llvm::outs() << "show for allcaps_t !!!" << arg2 << "\n";
    return "show for allcaps_t !!!";
  };

  // /// \note no version for reference_wrapper
  template<typename A>
  std::string _tc_impl_t<std::reference_wrapper<allcaps_t>, my_interface2>::
      show(/*std::reference_wrapper<*/allcaps_t/*>*/ const &, A const & arg2) noexcept {
    llvm::outs() << "show for std::reference_wrapper<allcaps_t> !!!" << arg2 << "\n";
    return "show for allcaps_t !!!";
  };

  // /// \note no version for reference_wrapper
  template<typename A>
  std::string _tc_impl_t<std::reference_wrapper<allcaps_t>, my_interface2>::
      show(std::reference_wrapper<allcaps_t> const &, A const & arg2) noexcept {
    llvm::outs() << "show for std::reference_wrapper<allcaps_t> !!!" << arg2 << "\n";
    return "show for allcaps_t !!!";
  };

  template<typename A>
  std::string _tc_impl_t<reverse_t, my_interface2>::
      show(reverse_t const &, A const & arg2) noexcept {
    llvm::outs() << "show for reverse_t !!!" << arg2 << "\n";
    return "show for reverse_t !!!";
  };

  template<typename A>
  std::string _tc_impl_t<forward_t, my_interface2>::
      show(forward_t const &, A const & arg2) noexcept {
    llvm::outs() << "show for forward_t !!!" << arg2 << "\n";
    return "show for forward_t !!!";
  };
#endif // 0

  /*template<
    typename reverse_t,
    typename C
  >
  std::string _tc_combined_t<template_interface<int, const std::string&>>::
    external(const reverse_t& arg1, C const & arg2) noexcept {
      return "external for reverse_t!!!";
  }*/

} // namespace generated
} // namespace cxxctp

#if 0
namespace cxxctp {
namespace generated {
  template<>
  void draw<my_interface2/*obj_t::typeclass_t*/>
   (const allcaps_t&, const char* surface) {
    llvm::outs() << "Drawing allcaps_t on " << surface << "\n";
  }

  template<>
  void draw<my_interface2/*obj_t::typeclass_t*/>
   (const forward_t&, const char* surface) {
    llvm::outs() << "Drawing forward_t on " << surface << "\n";
  }

  template<>
  void draw<my_interface2/*obj_t::typeclass_t*/>
   (const reverse_t&, const char* surface) {
    llvm::outs() << "Drawing reverse_t on " << surface << "\n";
  }
} // namespace generated
} // namespace cxxctp
#endif // 0

using cxxctp::generated::my_interface_obj_t;
using cxxctp::generated::my_interface_impl_t;
using cxxctp::generated::my_interface2_obj_t;
using cxxctp::generated::my_interface2_impl_t;
using cxxctp::generated::my_interface_my_interface2_obj_t;
using cxxctp::generated::_tc_impl_t;
using cxxctp::generated::_tc_model_t;
using cxxctp::generated::_tc_combined_t;

/*template<typename B, typename C>
const auto show = cxxctp::generated::show<my_interface2, B, C>;*/

/*template <typename B, typename C>
constexpr void(*show)(const B& arg1, const C& arg2)
  = &cxxctp::generated::show<my_interface2, B, C>;*/
//using cxxctp::generated::foo1;
//using cxxctp::generated::show<my_interface2>;

void do_small_smth(const my_interface_obj_t& small_obj) {
  if(!small_obj) {
    printf("INVALID SMALL_OBJ!\n");
    return;
  }
  if(!small_obj.has_print()) {
    printf("SMALL_OBJ without print!\n");
    return;
  }
  if(small_obj.has_print()) {
    small_obj.print("Hello from do_small_smth");
  }
  printf("SMALL_OBJ print_interface_data!\n");
  small_obj.print_interface_data();
}

void do_big_smth(const my_interface_my_interface2_obj_t& big_obj) {
  if(!big_obj) {
    printf("INVALID big_OBJ.has_my_interface_model!\n");
    return;
  }
  if(!big_obj.has_print()) {
    printf("big_OBJ without print!\n");
    return;
  }
  if(big_obj.has_print()) {
    big_obj.print("Hello from do_big_smth");
  }
  printf("big_OBJ print_interface_data!\n");
  big_obj.print_interface_data();
}

int main(int /*argc*/, const char* const* /*argv*/) {
    using namespace clang::tooling;

    my_interface2_obj_t tz{forward_t{}};
    llvm::outs() << "test_zoo: " << tz.test_zoo("tz") << "\n";

    llvm::outs() << "my_interface2_obj_t can_convert1 "
      << std::to_string(
        tz.can_convert<template_interface<int, const std::string&>>())
      << "\n";

    llvm::outs() << "my_interface2_obj_t can_convert2 "
      << std::to_string(
        tz.can_convert<my_interface2>())
      << "\n";

    llvm::outs() << "my_interface2_obj_t can_convert3 "
      << std::to_string(
        tz.can_convert<int>())
      << "\n";

    do_small_smth(forward_t{});
    do_small_smth(my_interface_obj_t{});
    //do_small_smth(my_interface2_obj_t{});
    //do_small_smth(my_interface_my_interface2_obj_t{});

    do_big_smth(forward_t{});
    //do_big_smth(my_interface_obj_t{});
    //do_big_smth(my_interface2_obj_t{});
    do_big_smth(my_interface_my_interface2_obj_t{});

    my_interface_my_interface2_obj_t com1;
    com1.create_model<template_interface<int, const std::string&>>(forward_t{});
    com1.create_model<my_interface2>(allcaps_t{});
    if(com1.has_do_job())
      com1.do_job("com1.save", "w");
    com1.print_interface_data();
    com1.set_interface_data("com1 interface data");

    /*forward_t ba;
    ba.forward_t_bar = "data";*/
    std::function<void(allcaps_t&, const std::string&)> fu1 = [](allcaps_t& concrete, const std::string& data){
      concrete.allcaps_t_bar = data;
    };
    com1.set_set_bar(fu1);

    std::function<std::string(allcaps_t&)> fu2 = [](allcaps_t& concrete){
      return concrete.allcaps_t_bar;
    };
    com1.set_get_bar(fu2);

    llvm::outs() << "com1.get_bar(): " << com1.get_bar() << "\n";
    com1.set_bar("dfgfgg");
    llvm::outs() << "com1.get_bar(): " << com1.get_bar() << "\n";

    do_big_smth(com1);

    my_interface_obj_t shared_my_interface_obj_t;
    shared_my_interface_obj_t.replace_model(
      com1.ref_model<template_interface<int, const std::string&>>());
    shared_my_interface_obj_t.set_interface_data("set_interface_data1");
    do_small_smth(shared_my_interface_obj_t);

    /*my_interface_my_interface2_obj_t comMov
      = shared_my_interface_obj_t.ref_my_interface_model();
    shared_my_interface_obj_t.set_interface_data("set_interface_data1");
    do_small_smth(shared_my_interface_obj_t);*/

    my_interface_my_interface2_obj_t com2 = reverse_t{};

    auto tidx1 = com2.getModelTypeIndex
            <template_interface<int, const std::string&>>();
    llvm::outs() << "tidx1 = " << tidx1 << "\n";
    if(my_interface_my_interface2_obj_t::getGlobalTypeIndex
        <template_interface<int, const std::string&>, reverse_t>()
          != tidx1) {
        throw std::runtime_error("getGlobalTypeIndex invalid for reverse_t");
    }

    com2 = shared_my_interface_obj_t;
    com2 = com1;
    com2.set_common_model(reverse_t{});
    com2.replace_model<template_interface<int, const std::string&>>(
      com1.ref_model<template_interface<int, const std::string&>>());

    com1.print_interface_data();

    llvm::outs() << "can_convert1 "
      << std::to_string(
        com1.can_convert<template_interface<int, const std::string&>>())
      << "\n";

    llvm::outs() << "can_convert2 "
      << std::to_string(
        com1.can_convert<my_interface2>())
      << "\n";

    llvm::outs() << "can_convert3 "
      << std::to_string(
        com1.can_convert<int>())
      << "\n";

    com1.set_common_model(forward_t{});

    auto tidx2 = com2.getModelTypeIndex
            <template_interface<int, const std::string&>>();
    llvm::outs() << "tidx2 = " << tidx2 << "\n";
    if(my_interface_my_interface2_obj_t::getGlobalTypeIndex
        <template_interface<int, const std::string&>, forward_t>()
          != tidx2) {
        throw std::runtime_error("getGlobalTypeIndex invalid for forward_t");
    }

    com2.print_interface_data();

    do_big_smth(com2);

    if(com2.has_do_job())
      com2.do_job("com2.save", "w");
    com2.print_interface_data();
    com2.set_interface_data("com2 interface data");
    com2.print_interface_data();

    {
      llvm::outs() << "casted_t1 before " << "\n";
      my_interface2_obj_t casted_t1{com2};
      llvm::outs() << "casted_t1 after " << "\n";
      /*llvm::outs() << "move casted_t1 before " << "\n";
      my_interface2_obj_t casted_t1{std::move(com2)};
      llvm::outs() << "move casted_t1 after " << "\n";*/
    }

    my_interface2_obj_t o2{forward_t{}};
    if(o2.has_do_job())
      o2.do_job("o2.save", "w");

    my_interface_obj_t o{allcaps_t{}};

    o.draw("canvas");
    o.print_interface_data();
    o.set_interface_data("O1 interface data");
    o.print_interface_data();
    o.print_data();
    o.print("Hello o");
    o.set_data("O1 data");
    o.print_data();

    do_small_smth(o);

    my_interface_obj_t a = my_interface_obj_t::construct<allcaps_t>();
    a.draw("water");
    a.print_data();
    a.print("Hello a");
    a.set_data("A1 data");
    a.print_data();

    // Copy-construct a to get b.
    my_interface_obj_t b = a;
    b.draw("sand");
    b.print("Hello b");

    if(b.has_save())
      b.save("my.save", "w");

    // Copy-assign a to get c.
    my_interface_obj_t c;
    c = b;
    c.print("Hello c");

    // Create a forward object.
    my_interface_obj_t d = my_interface_obj_t::construct<forward_t>();
    d.draw("wind");
    d.print_data();
    d.print("Hello d");
    d.save("foo.save", "w");
    d.set_data("D1 data");
    d.print_data();
    d.print_interface_data();
    d.set_interface_data("D1 interface data");
    d.print_interface_data();

    // Create a reverse object.
    my_interface_obj_t e = my_interface_obj_t::construct<reverse_t>();
    e.draw("text");
    e.print("Hello e");

    if(e.has_save())
      e.save("bar.save", "w");

    my_interface_obj_t f = reverse_t{};

    auto tidx3 = f.getModelTypeIndex();
    llvm::outs() << "tidx3 = " << tidx3 << "\n";
    if(tidx3 != my_interface_obj_t::getGlobalTypeIndex<reverse_t>()) {
        throw std::runtime_error("f getGlobalTypeIndex invalid for reverse_t");
    }

    f.draw("console");
    f.print("Hello f");

    o.print("Hello o");
    a.print("Hello a");
    b.print("Hello b");
    c.print("Hello c");
    d.print("Hello d");
    e.print("Hello e");
    f.print("Hello f");

    forward_t fwdt{};

    my_interface2_impl_t<forward_t>::show(fwdt, "fwdt_tz _0");
    my_interface2_impl_t<decltype(fwdt)>::show(fwdt, "fwdt_tz __0");
    //my_interface2_impl_t<allcaps_t>::show(fwdt, "fwdt_tz ___0"); // can`t compile

    allcaps_t fwdtrf{}; // allcaps_t forward_t
    fwdtrf.allcaps_t_data = "fwdtrf_allcaps_t_data_TEST1";

    {
      fwdtrf.allcaps_t_data = "allcaps_t_data1";
      my_interface2_obj_t fwdtrf_tz{std::ref(fwdtrf)};
      llvm::outs() << "test_zoo ref: " << fwdtrf_tz.test_zoo("fwdtrf_tz") << "\n";
      fwdtrf_tz.do_job("fwdtrf_tz.save", "w");
    }

    {
      my_interface_obj_t my_fwdtrf_tz{std::ref(fwdtrf)};
      my_fwdtrf_tz.draw("my_fwdtrf_tz console");
      my_fwdtrf_tz.print("my_fwdtrf_tz Hello f");
    }

    llvm::outs() << "fwdtrf data: " << fwdtrf.allcaps_t_data << "\n";

    {
      fwdtrf.allcaps_t_data = "allcaps_t_data2";
      /// made ref, not copy
      my_interface2_obj_t fwdtrf_tz{std::ref(fwdtrf)};
      llvm::outs() << "test_zoo2 ref: " << fwdtrf_tz.test_zoo("fwdtrf_tz2") << "\n";
      fwdtrf_tz.do_job("fwdtrf_tz.save", "w");

      /// made ref, not copy (of typeclass model)
      my_interface2_obj_t refed_tz{std::ref(fwdtrf_tz)};
      llvm::outs() << "test_zoo3 ref: " << refed_tz.test_zoo("refed_tz") << "\n";
      refed_tz.do_job("refed_tz.save", "w");

      {
        fwdtrf.allcaps_t_data = "allcaps_t_data3";

        llvm::outs() << "test_zoo_1 ref: " << fwdtrf_tz.test_zoo("fwdtrf_tz2") << "\n";
        fwdtrf_tz.do_job("fwdtrf_tz.save 2", "w");

        llvm::outs() << "test_zoo_2 ref: " << refed_tz.test_zoo("refed_tz") << "\n";
        refed_tz.do_job("refed_tz.save 2", "w");
      }

      my_interface2_obj_t cloned(fwdtrf_tz);
      llvm::outs() << "cloned1 ref: " << cloned.test_zoo("cloned1") << "\n";
      cloned.do_job("cloned1.save", "w");

      my_interface2_obj_t movdCopy{std::move(cloned)};
      llvm::outs() << "movdCopy1 ref: " << movdCopy.test_zoo("movdCopy1") << "\n";
      movdCopy.do_job("movdCopy1.save", "w");

      /// \note invalid (moved) data here!
      llvm::outs() << "cloned2 ref: " << cloned.test_zoo("cloned2") << "\n";
      cloned.do_job("cloned2.save", "w");

      /// \note moved data must exist here
      my_interface2_obj_t movdRef{std::move(fwdtrf_tz)};
      llvm::outs() << "movdRef ref: " << movdRef.test_zoo("movdRef") << "\n";
      movdRef.do_job("movdRef.save", "w");

      /// \note copied data must exist here
      llvm::outs() << "movdCopy2 ref: " << movdCopy.test_zoo("movdCopy2") << "\n";
      movdCopy.do_job("movdCopy2.save", "w");
    }

    // can create only from move or ref or temporary
    /*{
      my_interface_obj_t my_fwdtrf_tz2 = fwdtrf;
      my_fwdtrf_tz2.draw("my_fwdtrf_tz2 console");
      my_fwdtrf_tz2.print("my_fwdtrf_tz2 Hello f");
    }*/

    {
      using cxxctp::generated::draw;

      allcaps_t asdasd{}; // allcaps_t forward_t
      asdasd.allcaps_t_data = "_allcaps_t_data_TEST1";
      draw<template_interface<int, const std::string&>>
        (asdasd, "draw draw draw!!!");
    }

    {
      my_interface_obj_t my_fwdtrf_tz3{std::ref(fwdtrf)};
      /// \note invalid (moved) data here!
      my_fwdtrf_tz3.draw("my_fwdtrf_tz3 console");
      my_fwdtrf_tz3.print("my_fwdtrf_tz3 Hello f");
    }

    llvm::outs() << "fwdtrf data: " << fwdtrf.allcaps_t_data << "\n";

    /*{
      allcaps_t fwdtrf2{}; // allcaps_t forward_t
      const auto ref1 = &fwdtrf2;
      my_interface2_obj_t fwdtrf_tz2{ref1};
      llvm::outs() << "test_zoo ref2: " << fwdtrf_tz2.test_zoo("fwdtrf2") << "\n";
    }*/

    my_interface2_obj_t fwdt_tz{std::move(fwdt)};

    //my_interface2_obj_t::show<forward_t>(fwdt, "fwdt_tz 1");

    //my_interface2_obj_t::show<forward_t>(fwdt, "fwdt_tz 1");

    //fwdt_tz.show(forward_t{}, "fwdt_tz 2");
    //fwdt_tz.show(forward_t{}, std::string{"fwdt_tz 2"});

    fwdt_tz = allcaps_t{};

    //my_interface2_impl_t<std::reference_wrapper<allcaps_t>>::show(allcaps_t{}, "fwdt_tz _0");

    fwdt_tz.show(std::string{"fwdt_tz !!!!!!!!!!!!"});

    fwdt_tz.show("fwdt_tz 2");

    {
      using cxxctp::generated::show;

      //foo1(2);
      show<my_interface2>(fwdt, "fwdt_tz ___0");
    }

    /// \note just for test
    /*llvm::outs() << "just for test data 1: "
      << show<template_interface<int, const std::string&>>(fwdt, "fwdt_tz ___0")
      << "\n";*/

    /// \note just for test
    /*llvm::outs() << "just for test data 2: "
      << f.show(fwdt, "fwdt_tz ___0")
      << "\n";*/

    //fwdt_tz.show<allcaps_t>(fwdt_tz.ref_concrete<allcaps_t>(), "fwdt_tz 3");

    /*allcaps_t ac{};
    fwdt_tz.show<allcaps_t>(ac, "fwdt_tz 3");*/

    //fwdt_tz.show<forward_t>(fwdt_tz.ref_concrete<forward_t>(), "fwdt_tz 3");

    //fwdt_tz.__show("fwdt_tz 3");

    //one_obj_t one1 = reverse_t{};
    //obj_t one2 = one_obj_t::construct<reverse_t>();
    //one_obj_t one3 = one2;

    //llvm::outs() << "seg\n";

    test_split_to_funcs();

    EnumTest1();

    // FIXME: cling linkage hack:
    // must use jinja before usage in cling
    {
      std::string enum2StringConvertor = R"(
      inline const char* {{enumName}}ToString({{enumName}} e)
      {
          HELLO
      })";
      //jinja2::RealFileSystem fs;
      //std::string enum2StringConvertor =
      //  getFileContent("simple_template1.j2tpl");
      //auto test1Stream = fs.OpenStream("test_data/simple_template1.j2tpl");
      jinja2::ValuesMap params = {
          {"enumName", "Animals"},
          {"items", jinja2::ValuesList{"Dog", "Cat", "Monkey", "Elephant"} }
      };
      jinja2::Template tpl;
      auto parseResult = tpl.Load(enum2StringConvertor);
      if(!parseResult) {
        printf("ERROR: can`t load jinja2 template from %s [%s]\n",
          enum2StringConvertor.c_str(), parseResult.error().GetLocationDescr().c_str());
      }
      //tpl.Load("{{'Hello World' }}!!!");
      //tpl.LoadFromFile("simple_template1.j2tpl");
      //llvm::outs() << tpl.RenderAsString(params);
      writeToFile(tpl.RenderAsString(params).value(), "tmp.enum.generated.hpp");
    }

    llvm::outs() << "input_func!... " << '\n';
    std::thread inp_thread(input_func);
    inp_thread.detach();
    std::thread cling_thread(cling_func);
    cling_thread.detach();

    // Wait until main() sends data
    {
      std::unique_lock<std::mutex> lk(clingReadyMutex);
      clingReadyCV.wait(lk, []{return isClingReady;});
    }

    llvm::outs() << "clang... " << '\n';

    /*OPTIONS:

    Generic Options:

      -help                      - Display available options (-help-hidden for more)
      -help-list                 - Display list of available options (-help-list-hidden for more)
      -version                   - Display the version of this program

    Use override options:

      -extra-arg=<string>        - Additional argument to append to the compiler command line
      -extra-arg-before=<string> - Additional argument to prepend to the compiler command line
      -p=<string>                - Build path*/
    std::vector<std::string> args_storage;
    args_storage.push_back("clang_app");
    //args_storage.push_back("-extra-arg=-nostdinc");

    //args_storage.push_back("-DCLANG_ENABLED=1");
    args_storage.push_back("-extra-arg=-DCLANG_ENABLED=1");

    // https://stackoverflow.com/a/30877725
    args_storage.push_back("-extra-arg=-DBOOST_SYSTEM_NO_DEPRECATED");
    args_storage.push_back("-extra-arg=-DBOOST_ERROR_CODE_HEADER_ONLY");
    // https://jinja2cpp.dev/docs/build_and_install.html#dependency-management-modes
    args_storage.push_back("-extra-arg=-Dvariant_CONFIG_SELECT_VARIANT=variant_VARIANT_NONSTD");

    args_storage.push_back("-extra-arg=-I../cling-build/build/lib/clang/5.0.0/include");
    args_storage.push_back("-extra-arg=-I../cling-build/src/include/");
    args_storage.push_back("-extra-arg=-I../cling-build/build/include/");
    args_storage.push_back("-extra-arg=-I../cling-build/src/tools/clang/include/");
    args_storage.push_back("-extra-arg=-I../cling-build/build/tools/clang/include/");
    args_storage.push_back("-extra-arg=-I../cling-build/src/tools/cling/include/");

    args_storage.push_back("-extra-arg=-I../submodules/Jinja2Cpp/thirdparty/nonstd/expected-light/include/");

    args_storage.push_back("-extra-arg=-I../resources");

    args_storage.push_back("-extra-arg=-std=c++17");
    //args_storage.push_back("-extra-arg=--std=c++2a");
    //args_storage.push_back("-extra-arg=-fmodules-ts");

    //args_storage.push_back("-extra-arg=-I/usr/local/tander/i586-pc-linux-gnu/usr/include/");

    args_storage.push_back("-p=\".\""); // Build path

    // TODO: crash when changed order, may be thread race
    args_storage.push_back("../resources/ReflShapeKind.hpp");
    args_storage.push_back("../resources/test.cpp");
    //args_storage.push_back("-help");

    // https://stackoverflow.com/questions/53525502/compiling-c-on-the-fly-clang-libtooling-fails-to-set-triple-for-llvm-ir
    // https://stackoverflow.com/questions/27092593/how-to-use-standard-library-with-clang-and-libtooling
    std::vector< const char* > args_vec;
    {
        std::vector< std::string >::const_iterator iarg;
        for( iarg = args_storage.begin() ; iarg != args_storage.end() ; ++iarg ) {
            args_vec.push_back(iarg->c_str());
        }
    }
    int args_arc = args_vec.size();
    const char **args_argv = &(args_vec[0]);
    llvm::cl::OptionCategory UseOverrideCategory("Use override options");
    CommonOptionsParser op(args_arc, args_argv, UseOverrideCategory);
    // TODO: https://github.com/mlomb/MetaCPP/blob/8eddde5e1bf4809ad70a68a385b9cbcc8e237370/MetaCPP-CLI/ScraperTool.cpp#L19
    ClangTool Tool(op.getCompilations(), op.getSourcePathList());

    Tool.run(new ToolFactory(/*new UseOverride::Action()*/));

    //return 0;

    //cling::Interpreter::CompilationResult compilationResult;
    bool quit = false;
    while(!quit)
    {
        /*{
            //std::scoped_lock lock(interpMap["main_module"]->canRunMutex);
            if(interpMap.find("main_module") != interpMap.end()) {
                interpMap["main_module"]->metaProcessor_->process("app_loop_run_once();", compilationResult, nullptr, true);
            }
        }*/
        /*{
            std::scoped_lock lock(m_runFlagMutex);
            if(!runFlag) break;
        }*/
    }
    // TODO: free mem
    //delete m_metaProcessor1;
    //delete m_metaProcessor2;

    llvm::outs() << "app_loop_finish!... " << '\n';
    return EXIT_SUCCESS;
}

#if 0
int main(int argc, const char* const* argv) {
    llvm::outs() << "LLVMDIR is " << LLVMDIR << '\n';

    // Create the Interpreter. LLVMDIR is provided as -D during compilation.
    cling::Interpreter interp(argc, argv, LLVMDIR);

    interp.enableDynamicLookup(true);

    interp.AddIncludePath(".");
    interp.AddIncludePath("../");
    //interp.AddIncludePath("/usr/include/c++/7/");
    //interp.AddIncludePath("/usr/include/c++/8/");

    interp.process("#define IS_CLING 1");
    interp.process("#define CLING_IS_ON 1");

    //interp.enablePrintDebug(true);
    interp.loadHeader("iostream");
    interp.process("#include <iostream>\n");
    interp.loadHeader("ostream");
    interp.process("#include <ostream>\n");
    interp.loadHeader("istream");
    interp.process("#include <istream>\n");
    //interp.loadHeader("bits/c++config.h");
    //interp.process("#include <bits/c++config.h>\n");
    interp.loadHeader("iosfwd");
    interp.process("#include <iosfwd>\n");
    interp.loadHeader("ios");
    interp.process("#include <ios>\n");

    interp.DumpIncludePath();

    useHeader(interp);
    useSymbolAddress(interp);
    usePointerLiteral(interp);

    /*const char* myFuncCode = "extern \"C\" int myFunc(int arg) { \n"
                             "printf(\"arg is %d\\n\", arg); return arg * arg; \n"
                             "llvm::outs() << \" myFuncCode \" << "\n"; \n"
                             "}";
    typedef int (*myFunc_t)(int);
    myFunc_t myFuncP = (myFunc_t) interp.compileFunction("myFunc", myFuncCode);
    printf("myFunc returned %d\n", (*myFuncP)(12));

    //interp.unload(1);

    const char* myFuncCode2 = "extern \"C\" int myFunc(int arg) { \n"
                             "printf(\"arg2 is %d\\n\", arg); return 2 * arg * arg; \n"
                              "llvm::outs() << \" myFuncCode2 \" << "\n"; \n"
                             "}";
    myFunc_t myFuncP2 = (myFunc_t) interp.compileFunction("myFunc", myFuncCode2);
    printf("myFunc2 returned %d\n", (*myFuncP2)(12));
*/

    cling::Value res; // Will hold the result of the expression evaluation

    /*const std::string changed_filename1 = "/home/denis/workspace/cling-cmake/src/MyTest1.cpp";
    reloadFile(interp, changed_filename1.c_str());*/

    /*const std::string changed_filename2 = "/home/denis/workspace/cling-cmake/src/MyTest2.cpp";
    reloadFile(interp, changed_filename2.c_str());*/

    std::string command;
    std::string command_param;
    while(std::cin >> command) {
        llvm::outs() << "You entered " << command << '\n';
        if (command == "q") {
            break;
        } else if (command == "reload_all") {
            reloadAllFiles(interp);
            /*interp.process("MyTest1();", &res);
            llvm::outs() << "MyTest1() returned " << res.getAs<float>() << '\n';
            interp.process("MyTest2();", &res);
            llvm::outs() << "MyTest2() returned " << res.getAs<float>() << '\n';*/
        } else if (command == "reload_file") {
            std::cin >> command_param;
            reloadFile(interp, command_param);
        }  else if (command == "unload") {
            unsigned int times = 1;
            std::cin >> times;
            interp.unload(times);
        } else if (command == "process_code") {
            std::getline(std::cin, command_param);
            llvm::outs() << "command_param: " << command_param << '\n';
            processCode(interp, command_param);
        } else if (command == "execute_code") {
            std::getline(std::cin, command_param);
            llvm::outs() << "command_param: " << command_param << '\n';
            executeCode(interp, command_param);
        } else if (command == "declare") {
            std::getline(std::cin, command_param);
            llvm::outs() << "command_param: " << command_param << '\n';
            interp.declare(command_param);
        } else if (command == "execute_code_from_file") {
            /// note file must be without UTF BOM
            std::cin >> command_param;
            processCode(interp, readWholeFile(command_param));
            /*interp.emitAllDecls(const_cast<cling::Transaction*>(interp.getCurrentTransaction()));*/
        } else {
            llvm::outs() << "UNKNOWN COMMAND! " << '\n';
        }
    }

    return 0;
}
#endif // 0
