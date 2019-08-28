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
            std::cout << "Destructor: Joining thread " << i << " until completion";
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
int aGlobal = 42;
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
    std::cout << "aGlobal is " << res.getAs<long long>() << '\n';
    interp.process("getAnotherGlobal();", &res);
    std::cout << "getAnotherGlobal() returned " << res.getAs<float>() << '\n';

    setAnotherGlobal(1.); // We modify the compiled value,
    interp.process("getAnotherGlobal();", &res); // does the interpreter see it?
    std::cout << "getAnotherGlobal() returned " << res.getAs<float>() << '\n';

    // We modify using the interpreter, now the binary sees the new value.
    interp.process("setAnotherGlobal(7.777); getAnotherGlobal();");
    std::cout << "getAnotherGlobal() returned " << getAnotherGlobal() << '\n';
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
    std::cout << "7 * 8 = " << pFunc(7, 8) << '\n';
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
    std::cout << "The square of 17 is " << res << '\n';
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
        std::cout << "unload " << filename << " ... " << '\n';
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
        std::cout << "load " << filename << " ... " << '\n';
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
        //cling_args_storage.push_back("std=c++17");
        //cling_args_storage.push_back("-std=c++17");
        cling_args_storage.push_back("--std=c++17");
        cling_args_storage.push_back("-I../cling-build/build/lib/clang/5.0.0/include");
        cling_args_storage.push_back("-I../cling-build/src/include/");
        cling_args_storage.push_back("-I../cling-build/build/include/");
        cling_args_storage.push_back("-I../cling-build/src/tools/clang/include/");
        cling_args_storage.push_back("-I../cling-build/build/tools/clang/include/");

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
            "/home/avakimov_am/job/clingrewriter/src/app_loop.cpp"
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
    cling::Interpreter::CompilationResult compilationResult1;
    /*if(interpMap.find("main_module") != interpMap.end() &&
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

    std::cout << "LLVMDIR is " << LLVMDIR << '\n';

    for(const auto& it : moduleToSources) {
        reloadClingModule(it.first, it.second);
        /*interpMap[it.first] =
            std::make_unique<InterpreterModule>(it.first, it.second);
        interpMap[it.first]->prepare();
        interpMap[it.first]->run();*/
        std::cout << "reloaded module " << it.first << '\n';
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
    //m_metaProcessor1->process("using std::cout;", compilationResult1, nullptr);
    //m_metaProcessor1->process("using std::endl;", compilationResult1, nullptr);
    //m_metaProcessor1->process("std::cout << \"cout1 called\" << std::endl;", compilationResult1, nullptr);

    //m_metaProcessor1->process(".x /home/denis/workspace/cling-cmake/src/MyTest1.cpp", compilationResult1, nullptr, true);

    // Create the Interpreter. LLVMDIR is provided as -D during compilation.
    //cling::Interpreter interp2(main_module, interp_args.size(), &(interp_args[0]), LLVMDIR/*, {}, true*/);
    cling::Value res; // Will hold the result of the expression evaluation.
    //interp2.process("#include <iostream>", &res);
    //interp2.process("std::cout << \"cout 12 called\" << std::endl;", &res);

    /*cling::MetaProcessor* m_metaProcessor2 = new cling::MetaProcessor(interp2, llvm::outs());*/
    /*cling::MetaProcessor* m_metaProcessor2 = new cling::MetaProcessor(interp2, llvm::outs());*/

    cling::Interpreter::CompilationResult compilationResult2;

    //m_metaProcessor2->process("#include <iostream>", compilationResult2, nullptr);
    /*m_metaProcessor2->process("using std::cout;", compilationResult2, nullptr);
    m_metaProcessor2->process("using std::endl;", compilationResult2, nullptr);*/
    ///m_metaProcessor2->process("std::cout << \"cout2 called\" << std::endl;", compilationResult2, nullptr);
    //m_metaProcessor1->process("std::cout << \"cout2 called\" << std::endl;", compilationResult1, nullptr);

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

void input_func()
{
    std::cout << "main cling input thread... " << '\n';
    std::string command;
    std::string command_param1;
    std::string command_param2;
    while(true) {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin >> command;
        std::cout << "in main cling input thread: "<< command << '\n';
        if (command == "q") {
            //std::scoped_lock lock(m_runFlagMutex);
            //runFlag = false;
            break;
        } else if (command == "reload_all") {
            //std::scoped_lock lock(interpMap["main_module"]->canRunMutex);
            //reloadAllCling(); // NOTE: run under mutex
            receivedMessagesQueue_->dispatch([] {
                std::cout << "dispatch reloadAllCling 2!... " << '\n';
                reloadAllCling();
            });
        }  else if (command == "reload_file") {
            std::cin >> command_param1 >> command_param2;
            {
                //std::scoped_lock lock(interpMap["main_module"]->canRunMutex);
                receivedMessagesQueue_->dispatch([command_param1, command_param2] {
                    std::cout << "dispatch reload_file 1!... " << '\n';
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
                        std::cout << "dispatch reloadClingModule 1!... " << '\n';
                        reloadClingModule(command_param1,
                                          moduleToSources[command_param1]);
                    });
                } else {
                    std::cout << "UNKNOWN MODULE! " << '\n';
                }
            }
        } else if (command == "unload") {
            unsigned int times = 1;
            std::cin >> command_param1 >> times;
            {
                //std::scoped_lock lock(interpMap["main_module"]->canRunMutex);
                receivedMessagesQueue_->dispatch([command_param1, times] {
                    std::cout << "dispatch unload 1!... " << '\n';
                    interpMap[command_param1]->interpreter_->unload(times);
                });
            }
        } else if (command == "process_code") {
            std::cin >> command_param1;
            std::getline(std::cin, command_param1);
            std::cout << "command_param: " << command_param1 << '\n';
            {
                //std::scoped_lock lock(interpMap["main_module"]->canRunMutex);
                receivedMessagesQueue_->dispatch([command_param1, command_param2] {
                    std::cout << "dispatch process_code 1!... " << '\n';
                    processCode(*interpMap[command_param1.c_str()]->interpreter_, command_param2);
                });
            }
        } else if (command == "execute_code") {
            std::cin >> command_param1;
            std::getline(std::cin, command_param1);
            std::cout << "command_param: " << command_param1 << '\n';
            {
                //std::scoped_lock lock(interpMap["main_module"]->canRunMutex);
                receivedMessagesQueue_->dispatch([command_param1, command_param2] {
                    std::cout << "dispatch execute_code 1!... " << '\n';
                    executeCode(*interpMap[command_param1.c_str()]->interpreter_, command_param2);
                });
            }
        } else if (command == "declare") {
            std::cin >> command_param1;
            std::getline(std::cin, command_param1);
            std::cout << "command_param: " << command_param1 << '\n';
            {
                //std::scoped_lock lock(interpMap["main_module"]->canRunMutex);
                receivedMessagesQueue_->dispatch([command_param1, command_param2] {
                    std::cout << "dispatch declare 1!... " << '\n';
                    interpMap[command_param1.c_str()]->interpreter_->declare(command_param2);
                });
            }
        } else if (command == "execute_code_from_file") {
            /// note file must be without UTF BOM
            std::cin >> command_param1 >> command_param2;
            {
                //std::scoped_lock lock(interpMap["main_module"]->canRunMutex);
                receivedMessagesQueue_->dispatch([command_param1, command_param2] {
                    std::cout << "dispatch execute_code_from_file 1!... " << '\n';
                    processCode(*interpMap[command_param1.c_str()]->interpreter_, readWholeFile(command_param2));
                });
            }
            /*interp.emitAllDecls(const_cast<cling::Transaction*>(interp.getCurrentTransaction()));*/
        } else {
            std::cout << "UNKNOWN COMMAND! " << '\n';
        }
        /*m_metaProcessor1->process(".x /home/denis/workspace/cling-cmake/src/MyTest1.cpp", compilationResult2, nullptr, true);*/
    }

    std::cout << "end input_func! " << '\n';
    std::terminate();
}

void cling_func() {
    receivedMessagesQueue_ =
        std::make_shared<DispatchQueue>(std::string{"Cling Dispatch Queue"}, 0);

    receivedMessagesQueue_->dispatch([] {
        std::cout << "dispatch reloadAllCling 1!... " << '\n';
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
        std::cout << "dispatch 2!... " << '\n';
    });
    receivedMessagesQueue_->DispatchQueued();

    receivedMessagesQueue_->dispatch([] {
        std::cout << "dispatch reloadAllCling 1!... " << '\n';
        reloadAllCling();
    });
    receivedMessagesQueue_->DispatchQueued();

    receivedMessagesQueue_->dispatch([] {
        std::cout << "dispatch 3!... " << '\n';
    });
    receivedMessagesQueue_->DispatchQueued();*/
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
    //std::cout << "match1 = " << std::endl;

    /*auto any_decl = Result.Nodes.getNodeAs<clang::NamedDecl>( "any_decl" );
    if(any_decl && !any_decl->isInvalidDecl()
       && any_decl->getIdentifier()) {
      std::cout << "any_decl = " << any_decl->getName().str() << std::endl;
    }
    auto any_decl = Result.Nodes.getNodeAs<clang::Decl>( "any_decl" );
    if(any_decl && !any_decl->isInvalidDecl()
       && any_decl->getKind()) {
      std::cout << "any_decl = " << any_decl->getDeclKindName()<< std::endl;
    }*/

    /*auto any_decl2 = Result.Nodes.getNodeAs<clang::PragmaCommentDecl>( "any_decl" );
    if(any_decl2) {
      std::cout << "any_decl2 = "
        << any_decl2->getArg().str() << " " << any_decl2->getDeclKindName() << std::endl;
    }*/

    /*auto any_decl2 = Result.Nodes.getNodeAs<clang::OMPParallelForDirective>( "any_decl" );
    if(any_decl2) {
      std::cout << "any_decl2 = "
        << any_decl2->getStmtClassName() << std::endl;
    }*/



    if ( const clang::Decl* decl = Result.Nodes.getNodeAs<clang::Decl>( "bind_gen" ) )
    {
      if ( decl && !decl->isInvalidDecl())
      if (auto annotate = decl->getAttr<clang::AnnotateAttr>()) {
        std::cout << "annotate->getAnnotation()"
          << annotate->getAnnotation().str() << std::endl;
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
          isFuncCall = true;
          std::string delimiter = ";";
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
          }
        }

        if(isEmbed) {
          std::cout << "embed for code: "
            << code << std::endl;
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
          std::cout << "eval for code: "
            << code << std::endl;
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
          std::cout << "export for code: "
            << code << std::endl;
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
          std::cout << "generator for code: "
            << code << std::endl;

          cling::Value result;

          //receivedMessagesQueue_->dispatch([] {
          for (const auto& func_to_call : funcs_to_call) {
              std::cout << "main_module task " << func_to_call << "!... " << '\n';
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
    //std::cout << "MethodDecl of " << MethodDecl->getName().str() << std::endl;

#if 0
    const auto *Call = Result.Nodes.getNodeAs<CallExpr>("call");
    assert(Call != nullptr);

    // https://github.com/hfinkel/llvm-project-cxxjit/blob/e534054d0112ea899a7d43dbf34ba8520d247fef/clang-tools-extra/clang-tidy/performance/TypePromotionInMathFnCheck.cpp#L159
    StringRef OldFnName = Call->getDirectCallee()->getName();
    std::cout << "OldFnName of " << OldFnName.str() << std::endl;

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
    //std::cout << "MethodDecl of " << MethodDecl.getName().str() << std::endl;
    return std::none_of(Attrs.begin(), Attrs.end(), [](const Attr *Attr) {
      /*std::cout << "Attr->getSpelling() "
        << Attr->getSpelling() << " is "
        << (strcmp(Attr->getSpelling(), "override") == 0) << std::endl;
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
                                       llvm::StringRef Filename) override {
    Rewriter.setSourceMgr(Compiler.getSourceManager(), Compiler.getLangOpts());
    return std::make_unique<Consumer>(Rewriter);
  }

  bool BeginSourceFileAction(clang::CompilerInstance &Compiler) override {
    llvm::errs() << "Processing " << getCurrentFile() << "\n\n";
    return true;
  }

  void EndSourceFileAction() override {
    ASTFrontendAction::EndSourceFileAction();

    SourceManager &SM = Rewriter.getSourceMgr();
    llvm::errs() << "** EndSourceFileAction for: "
                 << SM.getFileEntryForID(SM.getMainFileID())->getName() << "\n";

    const auto File = SM.getMainFileID();
    Rewriter.getEditBuffer(File).write(llvm::outs());

    std::string file_name = SM.getFileEntryForID(
        SM.getMainFileID())->getName();
    const std::string file_ext = file_name.substr(
      file_name.find_last_of(".") + 1);
    if(!file_name.empty() && !file_ext.empty()) {
      const std::string full_file_ext = "." + file_ext;
      std::cout << "full_file_ext = " << full_file_ext << std::endl;
      file_name.erase(file_name.length() - full_file_ext.length(), full_file_ext.length());
      std::error_code error_code;
      llvm::raw_fd_ostream outFile(file_name + ".generated" + full_file_ext, error_code, llvm::sys::fs::F_None);
      Rewriter.getEditBuffer(SM.getMainFileID()).write(outFile);
      outFile.close();
    }
  }

private:
  clang::Rewriter Rewriter;
};
} // namespace UseOverride

struct ToolFactory : public clang::tooling::FrontendActionFactory {
  clang::FrontendAction *create() override {
    return new UseOverride::Action();
  }
};

int main(int argc, const char* const* argv) {
    using namespace clang::tooling;

    std::cout << "input_func!... " << '\n';
    std::thread inp_thread(input_func);
    inp_thread.detach();
    std::thread cling_thread(cling_func);
    cling_thread.detach();

    // Wait until main() sends data
    {
      std::unique_lock<std::mutex> lk(clingReadyMutex);
      clingReadyCV.wait(lk, []{return isClingReady;});
    }

    std::cout << "clang... " << '\n';

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
    args_storage.push_back("-extra-arg=-I../cling-build/build/lib/clang/5.0.0/include");
    args_storage.push_back("-extra-arg=-I../cling-build/src/include/");
    args_storage.push_back("-extra-arg=-I../cling-build/build/include/");
    args_storage.push_back("-extra-arg=-I../cling-build/src/tools/clang/include/");
    args_storage.push_back("-extra-arg=-I../cling-build/build/tools/clang/include/");
    args_storage.push_back("-extra-arg=-std=c++17");
    args_storage.push_back("test.cpp");
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

    Tool.run(new ToolFactory);

    //return 0;

    //cling::Interpreter::CompilationResult compilationResult;
    while(true)
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

    std::cout << "app_loop_finish!... " << '\n';
    return EXIT_SUCCESS;
}

#if 0
int main(int argc, const char* const* argv) {
    std::cout << "LLVMDIR is " << LLVMDIR << '\n';

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
                             "std::cout << \" myFuncCode \" << std::endl; \n"
                             "}";
    typedef int (*myFunc_t)(int);
    myFunc_t myFuncP = (myFunc_t) interp.compileFunction("myFunc", myFuncCode);
    printf("myFunc returned %d\n", (*myFuncP)(12));

    //interp.unload(1);

    const char* myFuncCode2 = "extern \"C\" int myFunc(int arg) { \n"
                             "printf(\"arg2 is %d\\n\", arg); return 2 * arg * arg; \n"
                              "std::cout << \" myFuncCode2 \" << std::endl; \n"
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
        std::cout << "You entered " << command << '\n';
        if (command == "q") {
            break;
        } else if (command == "reload_all") {
            reloadAllFiles(interp);
            /*interp.process("MyTest1();", &res);
            std::cout << "MyTest1() returned " << res.getAs<float>() << '\n';
            interp.process("MyTest2();", &res);
            std::cout << "MyTest2() returned " << res.getAs<float>() << '\n';*/
        } else if (command == "reload_file") {
            std::cin >> command_param;
            reloadFile(interp, command_param);
        }  else if (command == "unload") {
            unsigned int times = 1;
            std::cin >> times;
            interp.unload(times);
        } else if (command == "process_code") {
            std::getline(std::cin, command_param);
            std::cout << "command_param: " << command_param << '\n';
            processCode(interp, command_param);
        } else if (command == "execute_code") {
            std::getline(std::cin, command_param);
            std::cout << "command_param: " << command_param << '\n';
            executeCode(interp, command_param);
        } else if (command == "declare") {
            std::getline(std::cin, command_param);
            std::cout << "command_param: " << command_param << '\n';
            interp.declare(command_param);
        } else if (command == "execute_code_from_file") {
            /// note file must be without UTF BOM
            std::cin >> command_param;
            processCode(interp, readWholeFile(command_param));
            /*interp.emitAllDecls(const_cast<cling::Transaction*>(interp.getCurrentTransaction()));*/
        } else {
            std::cout << "UNKNOWN COMMAND! " << '\n';
        }
    }

    return 0;
}
#endif // 0
