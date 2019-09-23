// see https://github.com/bisegni/chaosframework/blob/master/chaos/common/script/cling/CPPScriptVM.cpp
// see https://github.com/galsasson/ofxCling
// see https://github.com/0xfd000000/qling/blob/22e56c4be0bbccb1d0437f610bfa37374b44b87f/qling/qling.cpp

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

#include <iostream>
#include <map>
#include <string>
#include <any>

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

#include "utils.hpp"
#include "DispatchQueue.hpp"

#include "funcParser.hpp"
#include "inputThread.hpp"
#include "clangUtils.hpp"
#include "clangPipeline.hpp"

#if !defined(CLING_IS_ON)
#include "ClingInterpreterModule.hpp"
#include "src/ctp_registry.hpp"
#endif // CLING_IS_ON

using namespace std;
using namespace clang;
using namespace clang::driver;
using namespace clang::tooling;
using namespace llvm;
using namespace clang::ast_matchers;
using clang::tooling::CommonOptionsParser;
using clang::tooling::Replacement;
using llvm::StringRef;

int main(int argc, const char* const* argv) {

/// \note that function may be usefull only if Cling is turned off
/// because functions may be called by name in Cling
#if !defined(CLING_IS_ON)
    add_modulecallbacks();
#endif // CLING_IS_ON

    using namespace clang::tooling;

    // input thread allows sending commands via cmd
    // usefull if you want to debug/quit/.. long running tasks
    std::thread inp_thread(cxxctp::input_func);
    inp_thread.detach();

#if defined(CLING_IS_ON)
    // cling thread used as C++ interpreter
    std::thread cling_thread(cling_utils::cling_func);
    cling_thread.detach();

    // Wait until main() sends data
    {
      std::unique_lock<std::mutex> lk(cling_utils::InterpreterModule::clingReadyMutex);
      cling_utils::InterpreterModule::clingReadyCV.wait(lk, []{return cling_utils::InterpreterModule::isClingReady;});
    }
#endif // CLING_IS_ON

    /*bool quit2 = false;
    while(!quit2)
    {
      // TODO
    }*/

    llvm::outs() << "clang... " << '\n';

    std::vector<std::string> args_storage;
    clang_utils::add_default_clang_args(args_storage);

    ///\note skip first arg (app name)
    for(int i = 1; i < argc; i++) {
        args_storage.push_back(argv[i]);
    }

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

    auto MakeAbsolute = [](const std::string &Input) -> SmallString<256> {
        if (Input.empty())
            return {};
        SmallString<256> AbsolutePath(Input);
        if (std::error_code EC = llvm::sys::fs::make_absolute(AbsolutePath)) {
            llvm::errs() << "Can't make absolute path from " << Input << ": "
                         << EC.message() << "\n";
        }
        return AbsolutePath;
    };
    for(const auto& it: op.getSourcePathList()) {
        llvm::outs() << "added source path = " << MakeAbsolute(it) << '\n';
    }

    ClangTool Tool(op.getCompilations(), op.getSourcePathList());

    Tool.run(new clang_utils::ToolFactory(/*new UseOverride::Action()*/));

#if defined(CLING_IS_ON)
    bool quit = false;
    while(!quit)
    {
        /// \note must wait for Cling & ClangTool threads
        quit = cling_utils::InterpreterModule::receivedMessagesQueue_->isEmpty();
    }
#endif // CLING_IS_ON
    // TODO: free mem
    //delete m_metaProcessor1;
    //delete m_metaProcessor2;

    llvm::outs() << "app_loop_finish!... " << '\n';
    return EXIT_SUCCESS;
}
