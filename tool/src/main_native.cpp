#include <iostream>
#include <iterator>
#include <exception>
#include <string>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <memory>
#include <vector>
#include <iomanip>
#include <sstream>

// __has_include is currently supported by GCC and Clang. However GCC 4.9 may have issues and
// returns 1 for 'defined( __has_include )', while '__has_include' is actually not supported:
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=63662
#if __has_include(<filesystem>)
#include <filesystem>
#else
#include <experimental/filesystem>
#endif // __has_include

#include <boost/program_options.hpp>
#include <boost/optional.hpp>
#include <boost/optional/optional_io.hpp>
#include <boost/program_options.hpp>
#include <boost/utility/in_place_factory.hpp>

#include <folly/logging/xlog.h>
#include <folly/logging/Init.h>
#include <folly/FileUtil.h>
#include <folly/File.h>
#include <folly/logging/FileHandlerFactory.h>
#include <folly/logging/LogHandlerFactory.h>
#include <folly/logging/LogWriter.h>
#include <folly/logging/LoggerDB.h>
#include <folly/Singleton.h>
#include <folly/Random.h>

#if FOLLY_USE_SYMBOLIZER
#include <folly/experimental/symbolizer/SignalHandler.h> // @manual
#endif
#include <folly/portability/GFlags.h>

#include <glog/logging.h>

// boost log or
// #include <glog/logging.h>
#include <glog/logging.h>

#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>

#include "core/errors/errors.hpp"

#include "utils.hpp"
#include "DispatchQueue.hpp"

#include "funcParser.hpp"
#include "inputThread.hpp"

#include "clangUtils.hpp"

#include "clangPipeline.hpp"

#include "options/ctp/options.hpp"

#if defined(CLING_IS_ON)
#include "ClingInterpreterModule.hpp"
#endif // CLING_IS_ON

#include "ctp_registry.hpp"

#include "version.hpp"

namespace po = boost::program_options;

#if __has_include(<filesystem>)
namespace fs = std::filesystem;
#else
namespace fs = std::experimental::filesystem;
#endif // __has_include

static boost::optional<std::string> log_config;

static boost::optional<std::string> srcdir_arg;

static boost::optional<std::string> resdir_arg;

static std::vector<std::string> ctp_scripts_search_paths;

#if 0 // TODO: custom logger format
namespace {
class TestLogFormatter : public folly::LogFormatter {
 public:
  std::string formatMessage(
      const folly::LogMessage& logMessage,
      const folly::LogCategory* /* handlerCategory */) override {
    return "Test Formatter! " + logMessage.getMessage();
  }
};

class TestLogWriter : public folly::LogWriter {
 public:
  void writeMessage(folly::StringPiece buffer, uint32_t /* flags */ = 0)
      override {
    messages.push_back(buffer.str());
  }

  void flush() override {}

  std::vector<std::string> messages;

  bool ttyOutput() const override {
    return false;
  }
};

class TestHandlerFactory : public folly::LogHandlerFactory {
 public:
  explicit TestHandlerFactory(
      const std::shared_ptr<TestLogWriter> writer,
      const std::shared_ptr<TestLogFormatter> formatter = nullptr)
      : writer_(writer), formatter_(formatter) {}

  folly::StringPiece getType() const override {
    return "test";
  }

  std::shared_ptr<folly::LogHandler> createHandler(const Options& options) override {
    TestWriterFactory writerFactory{writer_};
    if (formatter_ == nullptr) {
      return folly::StandardLogHandlerFactory::createHandler(
          getType(), &writerFactory, options);
    }
    TestFormatterFactory formatterFactory{formatter_};
    return folly::StandardLogHandlerFactory::createHandler(
        getType(), &writerFactory, &formatterFactory, options);
  }

 private:
  std::shared_ptr<TestLogWriter> writer_;
  std::shared_ptr<TestLogFormatter> formatter_;
  class TestWriterFactory : public folly::StandardLogHandlerFactory::WriterFactory {
   public:
    explicit TestWriterFactory(std::shared_ptr<TestLogWriter> writer)
        : writer_(writer) {}

    bool processOption(folly::StringPiece /* name */, folly::StringPiece /* value */)
        override {
      return false;
    }

    std::shared_ptr<folly::LogWriter> createWriter() override {
      return writer_;
    }

   private:
    std::shared_ptr<TestLogWriter> writer_;
  };

  class TestFormatterFactory
      : public folly::StandardLogHandlerFactory::FormatterFactory {
   public:
    explicit TestFormatterFactory(std::shared_ptr<folly::LogFormatter> formatter)
        : formatter_(formatter) {}

    bool processOption(folly::StringPiece /* name */, folly::StringPiece /* value */)
        override {
      return false;
    }

    std::shared_ptr<folly::LogFormatter> createFormatter(
        const std::shared_ptr<folly::LogWriter>& /* logWriter */) override {
      return formatter_;
    }

   private:
    std::shared_ptr<folly::LogFormatter> formatter_;
  };
};
} // namespace
#endif // 0

template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    copy(v.begin(), v.end(), std::ostream_iterator<T>(os, " "));
    return os;
}

/*
 * An RAII object to be constructed at the beginning of main() and destructed
 * implicitly at the end of main().
 *
 * The constructor performs the same setup as folly::init(), including
 * initializing singletons managed by folly::Singleton.
 *
 * The destructor destroys all singletons managed by folly::Singleton, yielding
 * better shutdown behavior when performed at the end of main(). In particular,
 * this guarantees that all singletons managed by folly::Singleton are destroyed
 * before all Meyers singletons are destroyed.
 */
class Init {
 public:
  // Force ctor & dtor out of line for better stack traces even with LTO.
  FOLLY_NOINLINE Init(int argc, char* argv[], boost::optional<std::string> log_config);
  FOLLY_NOINLINE ~Init();

  Init(Init const&) = delete;
  Init(Init&&) = delete;
  Init& operator=(Init const&) = delete;
  Init& operator=(Init&&) = delete;
};

Init::Init(int argc, char* argv[],
    boost::optional<std::string> log_config) {
#if FOLLY_USE_SYMBOLIZER
  // Install the handler now, to trap errors received during startup.
  // The callbacks, if any, can be installed later
  folly::symbolizer::installFatalSignalHandler();
#elif !defined(_WIN32)
  google::InstallFailureSignalHandler();
#endif

  // Move from the registration phase to the "you can actually instantiate
  // things now" phase.
  folly::SingletonVault::singleton()->registrationComplete();

  // similar to https://github.com/facebook/folly/blob/master/folly/init/Init.cpp#L49
  // but removed ParseCommandLineFlags
  // add support fo file logging,
  // see https://github.com/facebook/folly/blob/master/folly/logging/docs/LogHandlers.md#file-handler-type
  folly::LoggerDB::get().registerHandlerFactory(
      std::make_unique<folly::FileHandlerFactory>());

  if(log_config.is_initialized()) {
    CHECK(!log_config.value().empty())
      << "invalid (empty) log configuration";
    folly::initLoggingOrDie(log_config.value());
  } else {
    /// \see https://github.com/facebook/folly/tree/master/folly/logging/docs
    folly::initLoggingOrDie(
      ".:=INFO:default:x; default=stream:stream=stderr; x=stream:stream=stderr");
  }
  auto programName = argc && argv && argc > 0 ? (argv)[0] : "unknown";
  XLOG(DBG9) << "program name is " << programName;
  google::InitGoogleLogging(programName);

#if FOLLY_USE_SYMBOLIZER
  // Don't use glog's DumpStackTraceAndExit; rely on our signal handler.
  google::InstallFailureFunction(abort);

  // Actually install the callbacks into the handler.
  folly::symbolizer::installFatalSignalCallbacks();
#endif
}

Init::~Init() {
  folly::SingletonVault::singleton()->destroyInstances();
}

/*struct CPUTask : public folly::CPUThreadPoolExecutor::Task {
  // Must be noexcept move constructible so it can be used in MPMCQueue
  explicit CPUTask(
      folly::Func&& f,
      std::chrono::milliseconds expiration,
      folly::Func&& expireCallback)
    : Task(std::move(f), expiration, std::move(expireCallback)),
      poison(false) {}
  CPUTask()
    : Task(nullptr, std::chrono::milliseconds(0), nullptr),
      poison(true) {}
  CPUTask(CPUTask&& o) noexcept : Task(std::move(o)), poison(o.poison) {}
  CPUTask(const CPUTask&) = default;
  CPUTask& operator=(const CPUTask&) = default;
  bool poison;
};*/

static bool startsWith(const std::string& in, const std::string& prefix) {
  return !in.compare(0, prefix.size(), prefix);
};

static std::string removePrefix(const std::string& from,
    const std::string& prefix) {
  return from.substr( prefix.size(), from.size() );
};

int main(int argc, char* argv[]) {
  std::vector<std::string> args_storage;

  try {
    const char* help_arg_name = "help";
    const char* log_arg_name = "log,L";
    const char* srcdir_arg_name = "srcdir,S";
    const char* resdir_arg_name = "resdir,R";
    const char* version_arg_name = "version,V";
    const char* plugins_arg_name = "plugins,P";
    const char* ctp_scripts_paths_arg_name = "ctp_scripts_paths,C";

    po::options_description desc("Allowed options");

    desc.add_options()
      (help_arg_name, "produce help message")
      (version_arg_name, "produce version message")
      (plugins_arg_name, "get list of loaded ctp scripts")
      (ctp_scripts_paths_arg_name, po::value(&ctp_scripts_search_paths)->multitoken(), "list of paths where toll will search for ctp_scripts subfolder")
      (resdir_arg_name, po::value(&resdir_arg)->default_value(boost::none, ""), "change output directory path (where to place generated files)")
      (srcdir_arg_name, po::value(&srcdir_arg)->default_value(boost::none, ""), "change current working directory path (path to template files)")
      (log_arg_name, po::value(&log_config)->
        default_value(boost::none, ""), "log configuration")
      ;

    po::variables_map vm;
    auto parsed_options = po::command_line_parser(argc, argv).
      options(desc).allow_unregistered().run();
    po::store(parsed_options, vm);

    po::notify(vm);

    /// \note no logging before Init!
    Init(argc, argv, log_config);
    XLOG(DBG9) << "Initialized CXXCTP_tool";

    /// \note must be before all custom arguments
    clang_utils::add_default_clang_args(args_storage);

    /// \note forward unregistered options to clang libtooling
    for (const auto& o : parsed_options.options) {
        if (vm.find(o.string_key) == vm.end()) {
            // an unknown option
            for(size_t i = 0; i < o.value.size(); i++) {
                const std::string combined_for_clang
                  = o.string_key + o.value[i];
                XLOG(DBG9) << "forwarded unregistered option "
                              "to clang libtooling: "
                              << combined_for_clang;
                if(combined_for_clang.empty()) {
                  continue;
                }
                args_storage.push_back(combined_for_clang);
                if(startsWith(combined_for_clang, "-extra-arg=")) {
                  const std::string combined_for_cling
                    = removePrefix(combined_for_clang, "-extra-arg=");
                  if(combined_for_cling.empty()) {
                    continue;
                  }
#if defined(CLING_IS_ON)
                  cling_utils::InterpreterModule::
                    extra_args.push_back(combined_for_cling);
#endif // CLING_IS_ON
                }
            }
        }
    }

    if (vm.count(help_arg_name)) {
      XLOG(INFO) << desc;
      args_storage.push_back("-help");
      /// \note continue to forward help to clang libtooling
    }

    if (vm.count("version") || vm.count("V")) {
      XLOG(INFO) << CXXCTP_tool_VERSION;
      return EXIT_SUCCESS;
    }

    /// \note that function may be usefull if Cling is turned off
    /// because functions may be called by name in Cling
    ctp_utils::add_modulecallbacks();

    /// \note must be after add_modulecallbacks()
    if (vm.count("plugins") || vm.count("P")) {
      XLOG(INFO) << "loaded plugins (ctp scripts):";
      for(const auto& it : clang_utils::get_cxxctp_callbacks()) {
        XLOG(INFO) << "  + " << it.first;
      }
      return EXIT_SUCCESS;
    }

#if defined(CLING_IS_ON)
    if (ctp_scripts_search_paths.empty()) {
      if (clang_utils::get_cxxctp_callbacks().empty()) {
        XLOG(ERR) << "ERROR: ctp_scripts_paths not set "
                     "and no built-in scripts/plugins available.";
        return EXIT_FAILURE;
      }
      XLOG(WARNING) << "WARNING: ctp_scripts_paths not set.";
    }

    auto fix_search_paths = [](std::vector<std::string>& inout) {
      std::vector<std::string> v;
      for(const auto& it: inout) {
        XLOG(DBG9) << "before: " << it;
        // split a string by blank spaces unless it is in quotes
        std::istringstream iss(it);
          std::string s;
          while (iss >> std::quoted(s)) {
              if(!s.empty()) {
                /// \note made path absolute
                v.push_back(fs::absolute(s));
                XLOG(DBG9) << "after: " << s;
              }
          }
      }
      inout = v;
    };

    fix_search_paths(ctp_scripts_search_paths);
#else
  if(ctp_scripts_search_paths.size() > 0) {
    XLOG(ERR) << "ERROR: `ctp_scripts_paths` option "
                 "require cling support! "
                 "Build tool with DENABLE_CLING=TRUE";
    return EXIT_FAILURE;
  }
#endif // CLING_IS_ON
  }
  catch(std::exception& e) {
    XLOG(ERR) << "ERROR: " << e.what();
    return EXIT_FAILURE;
  }
  catch(...) {
    XLOG(ERR) << "ERROR: Exception of unknown type!";
    return EXIT_FAILURE;
  }

  ctp::Options::src_path = fs::absolute(fs::current_path());
  if(srcdir_arg.is_initialized() && !srcdir_arg.value().empty()) {
    XLOG(DBG9) << "srcdir_arg " << srcdir_arg.value();
    ctp::Options::src_path = fs::absolute(fs::path(srcdir_arg.value()));
    if(!fs::is_directory(ctp::Options::src_path)) {
      XLOG(ERR) << srcdir_arg.value() << " must be directory";
      return EXIT_FAILURE;
    }
    fs::current_path(srcdir_arg.value());
  }

  ctp::Options::res_path = fs::absolute(fs::current_path());

  if(resdir_arg.is_initialized() && !resdir_arg.value().empty()) {
    XLOG(DBG9) << "resdir_arg " << resdir_arg.value();
    ctp::Options::res_path = fs::absolute(fs::path(resdir_arg.value()));
    if(!fs::is_directory(ctp::Options::res_path)) {
      XLOG(WARNING) << "created directory " << resdir_arg.value();
      fs::create_directories(ctp::Options::res_path);
    }
  }

#if defined(CLING_IS_ON)
  XLOG(DBG9) << "ctp_scripts_search_paths (" << ctp_scripts_search_paths.size() << "): ";
  for(const std::string& it: ctp_scripts_search_paths) {
    ctp::Options::ctp_scripts_search_paths.push_back(it);
    XLOG(DBG9) << " + " << it;
  }
#endif // CLING_IS_ON

  XLOG(DBG9) << "Current path is " << fs::current_path();
  XLOG(DBG9) << "srcdir: Local path is " << srcdir_arg.get_value_or("");
  XLOG(DBG9) << "srcdir: Absolute path is " << ctp::Options::src_path;
  XLOG(DBG9) << "resdir: Local path is " << resdir_arg.get_value_or("");
  XLOG(DBG9) << "resdir: Absolute path is " << ctp::Options::res_path;

  auto chrono_then = std::chrono::steady_clock::now();

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

  clang::tooling::CommonOptionsParser op(args_arc, args_argv,
    UseOverrideCategory);

  // TODO: https://github.com/mlomb/MetaCPP/blob/8eddde5e1bf4809ad70a68a385b9cbcc8e237370/MetaCPP-CLI/ScraperTool.cpp#L19

  auto MakeAbsolute = [](const std::string &Input) -> clang::SmallString<256> {
      if (Input.empty())
          return {};
      clang::SmallString<256> AbsolutePath(Input);
      if (std::error_code EC = llvm::sys::fs::make_absolute(AbsolutePath)) {
          llvm::errs() << "Can't make absolute path from " << Input << ": "
                       << EC.message() << "\n";
      }
      return AbsolutePath;
  };
  for(const auto& it: op.getSourcePathList()) {
      XLOG(DBG9) << "added source path = " << MakeAbsolute(it).str().str();
  }

  clang::tooling::ClangTool Tool(op.getCompilations(),
    op.getSourcePathList());

  Tool.run(new clang_utils::ToolFactory(/*new UseOverride::Action()*/));

#if defined(CLING_IS_ON)
    bool quit = false;
    while(!quit)
    {
        /// \note must wait for Cling & ClangTool threads
        quit = cling_utils::InterpreterModule::receivedMessagesQueue_->isEmpty();
    }
#endif // CLING_IS_ON

  long int diff_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                 std::chrono::steady_clock::now() - chrono_then)
                 .count();
  long int diff_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
                 std::chrono::steady_clock::now() - chrono_then)
                 .count();
  XLOG(DBG9) << "Done in : " << diff_ms << " milliseconds (" << diff_ns << " nanoseconds)";
  return EXIT_SUCCESS;
}
