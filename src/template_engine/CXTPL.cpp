#include "CXTPL.h"

using namespace clang;
using namespace llvm;
using llvm::StringRef;

void CXTPL<AnyDict>::createFromFile(const string &path) {
    code_before_build_ = readWholeFile(path);
    rebuild();
}

void CXTPL<AnyDict>::createFromString(const string &code) {
    code_before_build_ = code;
    rebuild();
}

void CXTPL<AnyDict>::loadBuiltFromFile(const string &path) {
    code_after_build_ = readWholeFile(path);
    if(code_after_build_.empty()) {
        // TODO: better warning
        printf("WARNING: empty code passed to CXTPL\n");
    }
    code_for_cling_after_build_ = prepareForCling(code_after_build_);
}

void CXTPL<AnyDict>::loadBuiltFromString(const string &code) {
    code_after_build_ = code;
    if(code_after_build_.empty()) {
        // TODO: better warning
        printf("WARNING: empty code passed to CXTPL\n");
    }
    code_for_cling_after_build_ = prepareForCling(code_after_build_);
    if(code_for_cling_after_build_.empty()) {
        // TODO: better warning
        printf("WARNING: empty code passed to cling\n");
    }
}

/*std::unique_ptr<string> CXTPL<AnyDict>::interpretToString(bool& bVar, bool& cVar,
    std::vector<std::string>& carNames) {
  if(code_for_cling_after_build_.empty()) {
    return nullptr;
  }
  return runInInterpreter(code_for_cling_after_build_, bVar, cVar, carNames);
}*/

void CXTPL<AnyDict>::interpretToFile(const string &path,
                                     const std::map<std::string, std::any>& dictionary,
                                     const std::string &includes_code) {
    printf("interpretToFile: with dictionary = %lu\n", dictionary.size());

    if(code_for_cling_after_build_.empty()) {
        // TODO: better warning
        printf("WARNING: empty code passed to cling\n");
        return;
    }
    interp_callback cb = [path/* copyed! */](std::unique_ptr<std::string> res) {
        writeToFile(res->c_str(), path);
    };
    runInInterpreter(cb, code_for_cling_after_build_, dictionary, includes_code);
}

void CXTPL<AnyDict>::compileToFile(const string &path,
                                   const std::map<std::string, std::any>& dictionary) {
    /*std::string output;

    /// \note uses `output` and `dictionary`
#include "../../build/test1.cxtpl.cpp"

    writeToFile(output, path);*/
}

/*void CXTPL<AnyDict>::interpretToFile(const string &path) {
  const auto interRes = interpretToString(bVar, cVar, carNames);
  if(interRes) {
    writeToFile(interRes->c_str(), path);
  }
}*/

void CXTPL<AnyDict>::buildToFile(const string &path) {
    if(code_after_build_.empty()) {
       // TODO: better warning
       printf("WARNING: empty code passed to CXTPL\n");
    }
    writeToFile(code_after_build_, path);
}

std::string CXTPL<AnyDict>::buildToString() {
    return code_after_build_;
}

void CXTPL<AnyDict>::rebuild() {
    if(!code_before_build_.empty()) {
        code_after_build_ = buildFromString(code_before_build_);
    }
    if(!code_after_build_.empty()) {
        code_for_cling_after_build_ = prepareForCling(code_after_build_);
    }
}

string CXTPL<AnyDict>::buildFromString(const string &input) {
    std::string processStr = input;
    std::string result;
    std::stringstream ss;
    const std::string openTagStart = "<CX=";
    const std::string nextTagMultiLine = ">";
    const std::string nextTagLine = "l>";
    const std::string nextTagString = "s>";
    const std::string nextTagRawString = "r>";
    const std::string closeTag = "<=CX>";
    auto startsWith = [](const std::string& in, const std::string& prefix) {
        return !in.compare(0, prefix.size(), prefix);
    };
    auto removePrefix = [](const std::string& from, const std::string& prefix) {
        return from.substr( prefix.size(), from.size() );
    };
    struct EncloseTagResult {
        std::string srcAfterTagCode;
        std::string tagCode;
        std::string::size_type close_pos;
    };
    auto encloseTag = [](const std::string& processStr, const std::string& closeTag) {
        std::string::size_type close_pos = processStr.find(closeTag);
        std::string srcAfterTagCode;
        std::string tagCode;
        if(close_pos != std::string::npos) {
            tagCode = processStr.substr( 0, close_pos );
            srcAfterTagCode = processStr.substr( close_pos + closeTag.length(), processStr.length() );
        }
        return EncloseTagResult{srcAfterTagCode, tagCode, close_pos};
    };
    const std::string outVarName = "output";
    auto wrapToRawStringText = [&outVarName](const std::string& text) {
        std::string result;
        result += R"outraw(
              )outraw";
        result += outVarName;
        result += R"outraw(
              += )outraw";
        result += text;
        result += R"outraw(;
              )outraw";
        return result;
    };
    auto wrapRawText = [&wrapToRawStringText](const std::string& text) {
        std::string src;
        src += R"outraw(
           R"raw()outraw";
        src += text;
        src += R"outraw()raw"
           )outraw";
        return wrapToRawStringText(src);
    };
    auto wrapToStringText = [&wrapToRawStringText](const std::string& text) {
        std::string src;
        src += R"outraw(
           std::to_string( )outraw";
        src += text;
        src += R"outraw( )
           )outraw";
        return wrapToRawStringText(src);
    };

    auto wrapCodeLine = [](const std::string& text) {
        return text;
    };

    auto wrapCodeMultiline = [](const std::string& text) {
        return text;
    };

    // TODO: use string view https://www.bfilipek.com/2018/07/string-view-perf.html

    std::string closeTagToFind = "";
    //while (!processStr.empty())
    const auto max_iterations = std::numeric_limits<size_t>::max();
    for(size_t i = 0; i < max_iterations; i++)
    {
        std::string::size_type pos = processStr.find(openTagStart);
        if(pos != std::string::npos) {
            result += wrapRawText(processStr.substr( 0, pos ));
            pos += openTagStart.size();
            processStr = processStr.substr( pos, processStr.size() );
            //std::cout << "seq1 = " << processStr << std::endl;
            if(startsWith(processStr, nextTagMultiLine)) {
                //std::cout << "nextTagMultiLine = " << processStr << std::endl;
                processStr = removePrefix( processStr, nextTagMultiLine );
                EncloseTagResult closedTag = encloseTag( processStr, closeTag );
                if(closedTag.close_pos == std::string::npos) {
                    // TODO: better error reporting
                    std::cout << "ERROR: missing closing tag after "
                              << openTagStart + nextTagMultiLine << std::endl;
                    break;
                }
                processStr = closedTag.srcAfterTagCode;
                result += wrapCodeMultiline(closedTag.tagCode);
                //std::cout << "nextTagMultiLine tagCode = " << closedTag.tagCode << std::endl;
                //std::cout << "srcAfterTagCode "
                //        << closedTag.srcAfterTagCode << std::endl;
            } else if(startsWith(processStr, nextTagLine)) {
                //std::cout << "nextTagLine = " << processStr << std::endl;
                processStr = removePrefix( processStr, nextTagLine );
                EncloseTagResult closedTag = encloseTag( processStr, "\n" );
                if(closedTag.close_pos == std::string::npos) {
                    // TODO: better error reporting
                    std::cout << "ERROR: missing closing tag after "
                              << openTagStart + nextTagMultiLine << std::endl;
                    break;
                }
                processStr = closedTag.srcAfterTagCode;
                result += wrapCodeLine(closedTag.tagCode);
                //std::cout << "nextTagLine tagCode = " << closedTag.tagCode << std::endl;
            } else if(startsWith(processStr, nextTagString)) {
                //std::cout << "nextTagString = " << processStr << std::endl;
                processStr = removePrefix( processStr, nextTagString );
                EncloseTagResult closedTag = encloseTag( processStr, closeTag );
                if(closedTag.close_pos == std::string::npos) {
                    // TODO: better error reporting
                    std::cout << "ERROR: missing closing tag after "
                              << openTagStart + nextTagMultiLine << std::endl;
                    break;
                }
                processStr = closedTag.srcAfterTagCode;
                result += wrapToStringText(closedTag.tagCode);
                //std::cout << "nextTagString tagCode = " << closedTag.tagCode << std::endl;
            } else if(startsWith(processStr, nextTagRawString)) {
                //std::cout << "nextTagRawString = " << processStr << std::endl;
                processStr = removePrefix( processStr, nextTagRawString );
                EncloseTagResult closedTag = encloseTag( processStr, closeTag );
                if(closedTag.close_pos == std::string::npos) {
                    // TODO: better error reporting
                    std::cout << "ERROR: missing closing tag after "
                              << openTagStart + nextTagMultiLine << std::endl;
                    break;
                }
                processStr = closedTag.srcAfterTagCode;
                result += wrapToRawStringText(closedTag.tagCode);
                //std::cout << "nextTagRawString tagCode = " << closedTag.tagCode << std::endl;
            }
        } else {
            // remainder
            result += wrapRawText(processStr.substr( 0, processStr.size() ));
            break;
        }
        ///std::cout << "processStr = " << processStr << std::endl;
    }
    return result;
}

string CXTPL<AnyDict>::prepareForCling(const string &inputToCode) {
    //std::string result = /*clinja_args +*/ inputToCode;
    std::string result;
    auto wrapToLambda = [](const std::string& text, const std::string& outVarName) {
        std::string result;
        result += R"outraw(
              [&](){ )outraw";
        result += R"outraw(std::string )outraw";
        result += outVarName;
        result += R"outraw(;)outraw";
        result += text;
        result += R"outraw( ; return new std::string{
              )outraw";
        result += outVarName;
        result += R"outraw(}; }()
              )outraw";
        return result;
    };

    return wrapToLambda(inputToCode, "output");
}

std::string CXTPL<AnyDict>::loadClingArgs(const std::string& appende, const std::map<std::string, std::any>& dictionary) {
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
        sstr << ARG_REF_TO_CLING("std::map<std::string, std::any>", dictionary);
        //sstr << ARG_REF_TO_CLING("bool", bVar);
        //sstr << ARG_REF_TO_CLING("bool", cVar);
        //sstr << ARG_REF_TO_CLING("std::vector<std::string>", carNames);
        //sstr << "\n bool bVar = true; \n";
        //sstr << "\n bool cVar = true; \n";
        //sstr << "\n std::vector<std::string> carNames; \n";
        // vars end
        sstr << "return ";
        //sstr << "static_cast<void*>(new std::string{ \"output\"});";
        sstr << "static_cast<void*>(";
        sstr << code;
        sstr << ");";
        // scope end
        sstr << "}()";
        return sstr.str();
    };
    return wrapArgsToCling(appende);
}

void CXTPL<AnyDict>::runInInterpreter(
    const interp_callback& callback, const string &inStr,
    const std::map<std::string, std::any>& dictionary,
    const std::string &includes_code) {
    if(inStr.empty()) {
        // TODO: better warning
    }
    const std::string inStrWithArgs = loadClingArgs(inStr, dictionary);
    //#if 0
    InterpreterModule::receivedMessagesQueue_->
        dispatch([includes_code /* copy! */, inStrWithArgs /* copy! */, callback /* copy! */]() {
            //#endif
            cling::Value clingResult;
            auto interp = std::make_unique<InterpreterModule>("template_module", std::vector<std::string>{});
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
