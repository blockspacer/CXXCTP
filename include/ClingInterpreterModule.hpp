#pragma once

#if defined(CLING_IS_ON)

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <condition_variable>

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
#include "cling/Interpreter/Transaction.h"
#include "cling/Interpreter/Value.h"
#include "cling/Interpreter/CValuePrinter.h"
#include "cling/MetaProcessor/MetaProcessor.h"
#include <cling/Utils/Casting.h>
#include "cling/Interpreter/LookupHelper.h"
#include "cling/Utils/AST.h"

#include "utils.hpp"
#include "DispatchQueue.hpp"

namespace cling_utils {

class InterpreterModule {
public:
    InterpreterModule(const std::string& id,
      const std::vector<std::string>& moduleFiles);

    ~InterpreterModule();

    void createInterpreter();

    void prepare();

    void run();

public: // TODO

    std::string id_;
    std::vector<std::string> moduleFiles_;
    std::unique_ptr<cling::Interpreter> interpreter_;
    std::unique_ptr<cling::MetaProcessor> metaProcessor_;

    static std::shared_ptr<cxxctp::utils::DispatchQueue>
      receivedMessagesQueue_;

    /// \note module loading order is important
    static std::map<std::string, std::vector<std::string>> moduleToSources;

    //static cling::MetaProcessor* m_metaProcessor1 = nullptr;
    static std::map<std::string, std::unique_ptr<InterpreterModule>>
      interpMap;

    static std::mutex clingReadyMutex;
    static std::condition_variable clingReadyCV;
    static bool isClingReady;

    static std::vector<std::string> extra_args;
};

void reloadClingModule(const std::string& module_id,
  const std::vector<std::string>& sources);

// NOTE: run under mutex
void reloadAllCling();

[[ noreturn ]] void cling_func();

void removeClingModule(const std::string& module_id);

void processCode(cling::Interpreter& interp, const std::string& code);

void executeCode(cling::Interpreter& interp, const std::string& code);

void add_default_cling_args(std::vector<std::string> &args);

} // namespace cling_utils

#endif // CLING_IS_ON
