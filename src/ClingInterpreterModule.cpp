#include "ClingInterpreterModule.hpp"

#if defined(CLING_IS_ON)

#include <folly/logging/xlog.h>

// __has_include is currently supported by GCC and Clang. However GCC 4.9 may have issues and
// returns 1 for 'defined( __has_include )', while '__has_include' is actually not supported:
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=63662
#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif

#include "options/ctp/options.hpp"

namespace cling_utils {

std::vector<std::string>
  InterpreterModule::extra_args;

/// \note module loading order is important
std::map<std::string, std::vector<std::string>>
  InterpreterModule::moduleToSources {
/*    /// \note module with app loop must be loaded last
    {
        "main_module",
        std::vector<std::string>{
#if defined(CLING_IS_ON)
            "../resources/cxtpl/CXTPL_STD.cpp",
            "../resources/ctp_scripts/app_loop.cpp"
#endif // CLING_IS_ON
        }
    }*/
};

bool InterpreterModule::isClingReady = false;

std::shared_ptr<cxxctp::utils::DispatchQueue> InterpreterModule::receivedMessagesQueue_{};

std::map<std::string, std::unique_ptr<InterpreterModule>> InterpreterModule::interpMap{};

std::mutex InterpreterModule::clingReadyMutex{};

std::condition_variable InterpreterModule::clingReadyCV{};

void processCode(cling::Interpreter& interp, const std::string& code) {
    cling::Value res; // Will hold the result of the expression evaluation.
    interp.process(code.c_str(), &res);
}

void executeCode(cling::Interpreter& interp, const std::string& code) {
    interp.execute(code.c_str());
}

void removeClingModule(const std::string& module_id) {
    if(InterpreterModule::interpMap.find(module_id) != InterpreterModule::interpMap.end()) {
        //printf("erased module %s\n", module_id.c_str());
        InterpreterModule::interpMap.erase(module_id);
    } else {
        printf("module not found! %s\n", module_id.c_str());
        for(const auto& it : InterpreterModule::interpMap) {
            printf("maybe you wanted to type %s?\n", it.first.c_str());
        }
    }
}

InterpreterModule::InterpreterModule(const std::string &id, const std::vector<std::string> &moduleFiles)
    : id_(id)
    , moduleFiles_(moduleFiles)
    //, moduleThread(&InterpreterModule::threadMain, this)
{
    /*for(const auto& it: moduleFiles_) {
        printf("moduleFiles_ module %s\n", it.c_str());
    }*/
    //moduleThread.detach();
    createInterpreter();
}

InterpreterModule::~InterpreterModule() {
    /*if(!moduleFiles_.empty()) {
        cling::Interpreter::CompilationResult compilationResult;
        metaProcessor_->process(id_ + "_cling_shutdown();", compilationResult, nullptr, true);
        if(compilationResult
            != cling::Interpreter::Interpreter::kSuccess) {
          XLOG(ERR) << "ERROR while running cling code:\n" << sstr.str();
        }
    }*/
}

void add_default_cling_args(std::vector<std::string> &args) {
    args.push_back("EmbedCling");
    args.push_back("-I.");
    args.push_back("-I../");

    //args.push_back("-nobuiltininc");
    //args.push_back("-nostdinc");

    //args.push_back("std=c++17");
    //args.push_back("-std=c++17");
    args.push_back("--std=c++17");
    //args.push_back("--std=c++2a");
    //args.push_back("-fmodules-ts");

    args.push_back("-I../cling-build/build/lib/clang/5.0.0/include");
    args.push_back("-I../cling-build/src/include/");
    args.push_back("-I../cling-build/build/include/");
    args.push_back("-I../cling-build/src/tools/clang/include/");
    args.push_back("-I../cling-build/build/tools/clang/include/");
    args.push_back("-I../cling-build/src/tools/cling/include/");

    //args.push_back("-I../submodules/Jinja2Cpp/thirdparty/nonstd/expected-light/include/");

    args.push_back("-I../resources");

    /*args.push_back("-lCXXCTP_core");
    args.push_back("-LCXXCTP_core");
    args.push_back("-l CXXCTP_core");
    args.push_back("-L CXXCTP_core");
    args.push_back("-llibCXXCTP_core");
    args.push_back("-LlibCXXCTP_core");
    args.push_back("-l libCXXCTP_core");
    args.push_back("-L libCXXCTP_core");*/

    /*args.push_back("-static ");
    args.push_back("-L./build/");
    args.push_back("-llibCXXCTP_core");
    args.push_back("-lCXXCTP_core");*/

    // https://stackoverflow.com/a/30877725
    args.push_back("-DBOOST_SYSTEM_NO_DEPRECATED");
    args.push_back("-DBOOST_ERROR_CODE_HEADER_ONLY");
    // https://jinja2cpp.dev/docs/build_and_install.html#dependency-management-modes
    //args.push_back("-Dvariant_CONFIG_SELECT_VARIANT=variant_VARIANT_NONSTD");

    //args.push_back("-I/usr/local/tander/i586-pc-linux-gnu/usr/lib/gcc/i586-pc-linux-gnu/7.3.0/include/g++-v7/");
    //args.push_back("-I/usr/local/tander/i586-pc-linux-gnu/usr/lib/gcc/i586-pc-linux-gnu/7.3.0/include/g++-v7/i586-pc-linux-gnu/");
    //args.push_back("-I/usr/local/tander/i586-pc-linux-gnu/usr/include/");

    //args.push_back("-I/usr/include/c++/8/");
    //args.push_back("-I/usr/include/c++/7/");

    //args.push_back("-I/usr/include/x86_64-linux-gnu/");

    for(const auto& it: InterpreterModule::extra_args) {
      args.push_back(it);
      XLOG(DBG9) << "InterpreterModule::extra_args = " << it;
    }
}

void InterpreterModule::createInterpreter() {
    std::vector<std::string> args;
    add_default_cling_args(args);

    std::vector< const char* > interp_args;
    {
        std::vector< std::string >::const_iterator iarg;
        for( iarg = args.begin() ; iarg != args.end() ; ++iarg ) {
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

    /*interpreter_->declare("int aGlobal;\n"
                          "float getAnotherGlobal();\n"
                          "void setAnotherGlobal(float val);\n");*/

    /*interpreter_->process("#include <string>");
        interpreter_->process("#include <map>");
        interpreter_->process("#include <memory>");

        interpreter_->declare("std::map<std::string, std::unique_ptr<InterpreterModule>> interpMap;\n");*/

    //printf("created module %s\n", id_.c_str());
}

void InterpreterModule::prepare() {
    cling::Interpreter::CompilationResult compilationResult;

    if(!moduleFiles_.empty()) {
        for(const auto& it: moduleFiles_) {
            //printf("processes module %s\n", it.c_str());

            //metaProcessor_->process(".L /home/avakimov_am/job/CXXCTP/build/libCXXCTP_core.a", compilationResult, nullptr, true);

            //metaProcessor_->process(".L CXXCTP_core", compilationResult, nullptr, true);

            metaProcessor_->process(".L " + it, compilationResult, nullptr, true);
            if(compilationResult
                != cling::Interpreter::Interpreter::kSuccess) {
              XLOG(ERR) << "ERROR while running cling code:\n" << it;
            }
        }

        //metaProcessor_->process(id_ + "_cling_prepare();", compilationResult, nullptr);
    }
}

void InterpreterModule::run() {
    /*if(!moduleFiles_.empty()) {
        std::thread module_main([this](){
            cling::Interpreter::CompilationResult compilationResult;
            metaProcessor_->process(id_ + "_cling_run();", compilationResult, nullptr, true);
            if(compilationResult
                != cling::Interpreter::Interpreter::kSuccess) {
              XLOG(ERR) << "ERROR while running cling code:\n" << sstr.str();
            }
        });
        module_main.detach();
    }*/
}

void reloadClingModule(const std::string &module_id, const std::vector<std::string> &sources) {
    InterpreterModule::interpMap[module_id] = std::make_unique<InterpreterModule>(
                module_id.c_str(),
                sources);
    InterpreterModule::interpMap[module_id]->prepare();
    InterpreterModule::interpMap[module_id]->run();
}

static void process_ctp_scripts_dir(const std::string& ctp_scripts_path) {
#if defined(CLING_IS_ON)
    // Init InterpreterModule files
    if(const auto Interp_it = InterpreterModule::moduleToSources.find("main_module")
       ; Interp_it == InterpreterModule::moduleToSources.end())
    {
      std::vector<fs::path> ctp_scripts_paths(
        fs::recursive_directory_iterator(ctp_scripts_path), fs::recursive_directory_iterator{}
      );

      /// \note we must be able to change loading order
      /// by file naming (0_file, 1_file)
      std::sort(ctp_scripts_paths.begin(), ctp_scripts_paths.end());

      for (const auto & file_entry : ctp_scripts_paths) {
        fs::path full_path = fs::absolute(file_entry);
        if(full_path.extension() == ".cpp"
           /// \note skip path containing `generated` as substr
           && full_path.string().find("generated") == std::string::npos)
        {
          InterpreterModule::moduleToSources["main_module"].push_back(full_path.string());
          XLOG(DBG9) << "added to InterpreterModule file " << full_path.string();
        }
      }
    }

    for(const auto& it : InterpreterModule::moduleToSources) {
        reloadClingModule(it.first, it.second);
        XLOG(DBG9) << "reloaded module " << it.first;
    }
#endif // CLING_IS_ON
}

static std::vector<fs::path> find_ctp_scripts_dirs(
  std::vector<fs::path> ctp_scripts_search_paths) {
  std::vector<fs::path> res;
  for(const fs::path& it: ctp_scripts_search_paths) {
    const fs::path ctp_scripts_path = it / "ctp_scripts";
    if(fs::exists(ctp_scripts_path) && fs::is_directory(ctp_scripts_path)) {
      res.push_back(ctp_scripts_path);
    }
  }
  return res;
}

void reloadAllCling() {
    /// \note remove all old modules and create new modules
    for(const auto& it : InterpreterModule::interpMap) {
        //printf("erased module %s\n", it.first.c_str());
        InterpreterModule::interpMap.erase(it.first);
    }

    XLOG(DBG9) << "LLVMDIR is " << LLVMDIR;

    fs::path abs_cur_path = fs::absolute(fs::current_path());

    XLOG(DBG9) << "fs::current_path() is " << abs_cur_path.string();

    //const std::string ctp_scripts_path
    //  = abs_cur_path / ".." / "resources" / "ctp_scripts";

    //std::vector<fs::path> ctp_scripts_search_paths; // << TODO

#if defined(CLING_IS_ON)
    std::vector<fs::path> ctp_scripts_paths =
      find_ctp_scripts_dirs(ctp::Options::ctp_scripts_search_paths);
    if(ctp_scripts_paths.empty()) {
      XLOG(WARNING) << "can`t find ctp_scripts folder in ctp_search_paths";
    }
    for(const fs::path& it: ctp_scripts_paths) {
      process_ctp_scripts_dir(it);
    }
#endif // CLING_IS_ON

    cling::Value res; // Will hold the result of the expression evaluation.
}

[[ noreturn ]] void cling_func() {
    InterpreterModule::receivedMessagesQueue_ =
            std::make_shared<cxxctp::utils::DispatchQueue>(std::string{"Cling Dispatch Queue"}, 0);

    InterpreterModule::receivedMessagesQueue_->dispatch([] {
        XLOG(DBG9) << "dispatched reloadAllCling event!... ";
        reloadAllCling();
        {
            std::unique_lock<std::mutex> lk(InterpreterModule::clingReadyMutex);
            InterpreterModule::isClingReady = true;
        }
        InterpreterModule::clingReadyCV.notify_one();
    });

    while(true) {
        InterpreterModule::receivedMessagesQueue_->DispatchQueued();
        if(InterpreterModule::receivedMessagesQueue_->isEmpty()) {
            /*for(const auto& it : interpMap) {
                interpMap[it.first]->run_update();
            }*/
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
}

} // namespace cling_utils

#endif // CLING_IS_ON
