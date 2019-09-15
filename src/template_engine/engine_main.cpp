#include "CXTPL.h"

bool runCXTPLInInterpreter(int argc, const char* const* argv) {
    const std::vector<std::string> sources{
        "../src/template_engine/CXTPL_config.cpp"
    };
    const std::string module_id = "CXTPL_template_module";

    auto interp = std::make_unique<InterpreterModule>("CXTPL_template_module", std::vector<std::string>{});
    for(const auto& it: sources) {
        cling::Interpreter::CompilationResult compilationResult;

        // load file
        interp->metaProcessor_->process(".L " + it, compilationResult, nullptr, true);

        // run func from file with args as hex pointer values
        {
            CXTPL<AnyDict> helper;
            std::string code;
            code += helper.argRefToCling("int", "argc", argc);
            code += helper.argRefToCling("const char* const*", "argv", argv);
            code += "CXTPL_config(argc, argv);";
            interp->metaProcessor_->process(code, compilationResult, nullptr, true);
        }
    }
    return true;
}

static CXTPL<AnyDict> cxtpl;

void CXTPL_createFromFile(const std::string& path) {
    cxtpl.createFromFile(path);
    std::cout << "loaded file " << path << '\n';
}

void CXTPL_buildToFile(const std::string& path) {
    cxtpl.buildToFile(path);
    std::cout << "created file " << path << '\n';
}

int main(int argc, const char* const* argv) {
    // TODO: multiple --threads

    // enum_gen

    if(!runCXTPLInInterpreter(argc, argv)){
        std::cout << "ERROR: can`t run CXTPL in Cling" << '\n';
        return EXIT_FAILURE;
    }

    std::cout << "all CXTPL jobs done\n";
    return EXIT_SUCCESS;
}
