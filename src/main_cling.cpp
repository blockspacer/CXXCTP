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

#include "utils.h"
#include "DispatchQueue.h"

#include "funcParser.h"
#include "inputThread.h"
#include "clangUtils.h"
#include "clangPipeline.h"
#include "ClingInterpreterModule.h"
#include "template_engine/CXTPL.h"

#if !defined(CLING_IS_ON)
#include "../resources/ctp_scripts/ctp_registry.h"
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

/*struct clinja_arg {
    std::string declaration;
};*/

/*template <typename M>
M GetWithDefault(const std::map<std::string, std::any>& m, const std::string& key, const M& defval) {
    auto it = m.find( key );
    if ( it == m.end() ) {
        return defval;
    }
    else {
        return std::any_cast<M>(it->second);
    }
}*/

int main(int /*argc*/, const char* const* /*argv*/) {

#if !defined(CLING_IS_ON)
    add_modulecallbacks();
#endif // CLING_IS_ON

    using namespace clang::tooling;

    /*CXTPL<AnyDict> cxtpl;

    cxtpl.createFromFile("../resources/cxtpl/enum_gen_hpp.cxtpl");
    cxtpl.buildToFile("../resources/cxtpl/enum_gen_hpp.cxtpl.cpp");

    cxtpl.createFromFile("../resources/cxtpl/enum_gen_cpp.cxtpl");
    cxtpl.buildToFile("../resources/cxtpl/enum_gen_cpp.cxtpl.cpp");*/

    llvm::outs() << "input_func!... " << '\n';
    std::thread inp_thread(input_func);
    inp_thread.detach();
    std::thread cling_thread(cling_func);
    cling_thread.detach();

    // Wait until main() sends data
    {
      std::unique_lock<std::mutex> lk(InterpreterModule::clingReadyMutex);
      InterpreterModule::clingReadyCV.wait(lk, []{return InterpreterModule::isClingReady;});
    }

    /*bool bVar1 = true;
    bool cVar1 = true;
    std::vector<std::string> carNames1{ "Betta", "Bob", "Lily"};

    std::map<std::string, std::any> anyDictionary;
    anyDictionary["bVar"] =  std::make_any<bool>(std::move(bVar1));
    anyDictionary["cVar"] = std::make_any<bool>(std::move(cVar1));
    anyDictionary["carNames"] = std::make_any<std::vector<std::string>>(std::move(carNames1));

    std::string headerGuard = GetWithDefault<std::string>(anyDictionary, "headerGuard", "");
    std::vector<std::string> generator_includes = GetWithDefault<std::vector<std::string>>(anyDictionary, "headerGuard", carNames1);*/

    /*bool bVar = std::any_cast< bool>(anyDictionary.at("bVar"));
    bool cVar = std::any_cast< bool>(anyDictionary.at("cVar"));
    std::vector<std::string> carNames = std::any_cast< std::vector<std::string>>(anyDictionary.at("carNames"));

    std::cout << "bVar = " << bVar << std::endl;
    std::cout << "cVar = " << cVar << std::endl;
    std::cout << "carNames = " << carNames.size() << std::endl;*/

    /*
    std::cout << "preprocessorRawInput = "
      << cxtpl.compileToString(bVar, cVar, carNames) << std::endl;

    cxtpl.interpretToString(bVar, cVar, carNames);*/

    /*cxtpl.interpretToFile("test1.interpret.out", anyDictionary, R"raw(
#include <iostream>
#include <map>
#include <string>
#include <any>
#include <vector>
)raw");*/

    //cxtpl.compileToFile("test1.compile.out", anyDictionary);

    /*bool quit2 = false;
    while(!quit2)
    {
      // TODO
    }*/

    llvm::outs() << "clang... " << '\n';

    std::vector<std::string> args_storage;
    add_default_clang_args(args_storage);

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

    bool quit = false;
    while(!quit)
    {
      // TODO
    }
    // TODO: free mem
    //delete m_metaProcessor1;
    //delete m_metaProcessor2;

    llvm::outs() << "app_loop_finish!... " << '\n';
    return EXIT_SUCCESS;
}
