#include "CXTPL_AnyDict.hpp"

#include "I_Dict.hpp"

namespace cxtpl_util {

void Dict<AnyDict>::interpretToFile(const string &path,
                                     const std::map<std::string, std::any>& cxtpl_params,
                                     const std::string &includes_code) {
    printf("interpretToFile: with cxtpl_params = %lu\n", cxtpl_params.size());

    if(code_for_cling_after_build_.empty()) {
        // TODO: better warning
        printf("WARNING: empty code passed to cling\n");
        return;
    }
    interp_callback cb = [path/* copyed! */](std::unique_ptr<std::string> res) {
        cxxctp::utils::writeToFile(res->c_str(), path);
    };
    runInInterpreter(cb, code_for_cling_after_build_, cxtpl_params, includes_code);
}

/*void Dict<AnyDict>::compileToFile(const string &path,
                                   const std::map<std::string, std::any>& cxtpl_params) {
    std::string cxtpl_output;

    /// \note uses `cxtpl_output` and `cxtpl_params`
#include "../../build/test1.cxtpl.cpp"

    cxxctp::utils::writeToFile(cxtpl_output, path);
}*/

/*void Dict<AnyDict>::interpretToFile(const string &path) {
  const auto interRes = interpretToString(bVar, cVar, carNames);
  if(interRes) {
    cxxctp::utils::writeToFile(interRes->c_str(), path);
  }
}*/

std::string Dict<AnyDict>::loadClingArgs(const std::string& appende, const std::map<std::string, std::any>& cxtpl_params) {
    //std::string result = /*clinja_args +*/ inputToCode;
    std::string result;

    auto wrapArgsToCling = [&](const std::string code) {
        std::ostringstream sstr;
        // scope begin
        sstr << "[](){";
        // vars begin
        /*sstr << "const bool& bVar = ";
          sstr << "*(const bool*)("
                  // Pass a pointer into cling as a string.
               << std::hex << std::showbase
               << reinterpret_cast<size_t>(&bVar) << ");";*/
        sstr << ARG_REF_TO_CLING("std::map<std::string, std::any>", cxtpl_params);
        //sstr << ARG_REF_TO_CLING("bool", bVar);
        //sstr << ARG_REF_TO_CLING("bool", cVar);
        //sstr << ARG_REF_TO_CLING("std::vector<std::string>", carNames);
        //sstr << "\n bool bVar = true; \n";
        //sstr << "\n bool cVar = true; \n";
        //sstr << "\n std::vector<std::string> carNames; \n";
        // vars end
        sstr << "return ";
        sstr << "static_cast<void*>(";
        sstr << code;
        sstr << ");";
        // scope end
        sstr << "}()";
        return sstr.str();
    };
    return wrapArgsToCling(appende);
}

void Dict<AnyDict>::runInInterpreter(
    const interp_callback& callback, const string &inStr,
    const std::map<std::string, std::any>& cxtpl_params,
    const std::string &includes_code) {
    if(inStr.empty()) {
        // TODO: better warning
    }
    const std::string inStrWithArgs = loadClingArgs(inStr, cxtpl_params);
    //#if 0
    cling_utils::InterpreterModule::receivedMessagesQueue_->
        dispatch([includes_code /* copy! */, inStrWithArgs /* copy! */, callback /* copy! */]() {
            //#endif
            cling::Value clingResult;
            auto interp = std::make_unique<cling_utils::InterpreterModule>("template_module", std::vector<std::string>{});
            interp->prepare();
            interp->run();
            {
                cling::Interpreter::CompilationResult compilationResult;
                interp->metaProcessor_->process(includes_code, compilationResult,
                                                nullptr, true);
            }
            {
                cling::Interpreter::CompilationResult compilationResult;
                interp->metaProcessor_->process(inStrWithArgs, compilationResult,
                                                &clingResult, true);

                void* resOptionVoid = clingResult.getAs<void*>();
                /// \note free memory by unique_ptr
                auto resOption = std::unique_ptr<std::string>(
                    static_cast<std::string*>(resOptionVoid));
                if(!resOption) {
                    return /*nullptr*/;
                }
                std::cout << "processed = " << *resOption << std::endl;
                //////////////return std::move(resOption);
                callback(std::move(resOption));
            }
            //#if 0
        });
    //#endif
    //return nullptr; // TODO
}

Dict<AnyDict>::~Dict<AnyDict>() {}

} // namespace cxtpl_util
