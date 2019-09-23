#include <string>
#include <iostream>

extern void CXTPL_createFromFile(const std::string& path);

extern void CXTPL_buildToFile(const std::string& path);

void CXTPL_config(int argc, const char* const* argv) {
    printf("loaded CXTPL_config with CLING\n");

    for(int i = 0; i < argc; i++){
        std::cout << "arg at " << i << " = " << argv[i] << std::endl;
    }

    const std::string cxtpl_dir = "../resources/cxtpl";
    const std::string out_dir = "../resources/cxtpl/generated";

    // enum_gen

    CXTPL_createFromFile(cxtpl_dir + "/enum_gen_hpp.cxtpl");
    CXTPL_buildToFile(out_dir + "/enum_gen_hpp.cxtpl.cpp");

    CXTPL_createFromFile(cxtpl_dir + "/enum_gen_cpp.cxtpl");
    CXTPL_buildToFile(out_dir + "/enum_gen_cpp.cxtpl.cpp");

    // typeclass_gen

    CXTPL_createFromFile(cxtpl_dir + "/typeclass_gen_cpp.cxtpl");
    CXTPL_buildToFile(out_dir + "/typeclass_gen_cpp.cxtpl.cpp");

    CXTPL_createFromFile(cxtpl_dir + "/typeclass_gen_hpp.cxtpl");
    CXTPL_buildToFile(out_dir + "/typeclass_gen_hpp.cxtpl.cpp");

    // typeclass_instance_gen

    CXTPL_createFromFile(cxtpl_dir + "/typeclass_instance_gen_cpp.cxtpl");
    CXTPL_buildToFile(out_dir + "/typeclass_instance_gen_cpp.cxtpl.cpp");

    CXTPL_createFromFile(cxtpl_dir + "/typeclass_instance_gen_hpp.cxtpl");
    CXTPL_buildToFile(out_dir + "/typeclass_instance_gen_hpp.cxtpl.cpp");

    printf("processed CXTPL_config with CLING\n");
}
