#include "CXTPL.h"

int main(int /*argc*/, const char* const* /*argv*/) {
    CXTPL<AnyDict> cxtpl;

    // TODO: multiple --threads

    // enum_gen

    cxtpl.createFromFile("../resources/cxtpl/enum_gen_hpp.cxtpl");
    cxtpl.buildToFile("../resources/cxtpl/enum_gen_hpp.cxtpl.cpp");

    cxtpl.createFromFile("../resources/cxtpl/enum_gen_cpp.cxtpl");
    cxtpl.buildToFile("../resources/cxtpl/enum_gen_cpp.cxtpl.cpp");

    // typeclass_gen

    cxtpl.createFromFile("../resources/cxtpl/typeclass_gen_cpp.cxtpl");
    cxtpl.buildToFile("../resources/cxtpl/typeclass_gen_cpp.cxtpl.cpp");

    cxtpl.createFromFile("../resources/cxtpl/typeclass_gen_hpp.cxtpl");
    cxtpl.buildToFile("../resources/cxtpl/typeclass_gen_hpp.cxtpl.cpp");

    // typeclass_instance_gen

    cxtpl.createFromFile("../resources/cxtpl/typeclass_instance_gen_cpp.cxtpl");
    cxtpl.buildToFile("../resources/cxtpl/typeclass_instance_gen_cpp.cxtpl.cpp");

    cxtpl.createFromFile("../resources/cxtpl/typeclass_instance_gen_hpp.cxtpl");
    cxtpl.buildToFile("../resources/cxtpl/typeclass_instance_gen_hpp.cxtpl.cpp");

    llvm::outs() << "all CXTPL jobs done" << '\n';
    return EXIT_SUCCESS;
}
