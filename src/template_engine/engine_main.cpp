#include "CXTPL.h"

int main(int /*argc*/, const char* const* /*argv*/) {
    CXTPL<AnyDict> cxtpl;

    cxtpl.createFromFile("../resources/cxtpl/enum_gen_hpp.cxtpl");
    cxtpl.buildToFile("../resources/cxtpl/enum_gen_hpp.cxtpl.cpp");

    cxtpl.createFromFile("../resources/cxtpl/enum_gen_cpp.cxtpl");
    cxtpl.buildToFile("../resources/cxtpl/enum_gen_cpp.cxtpl.cpp");

    llvm::outs() << "app_loop_finish!... " << '\n';
    return EXIT_SUCCESS;
}
