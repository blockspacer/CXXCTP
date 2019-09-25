#include "ctp_registry.hpp"

#include "ctp_scripts/2_scripts/make_reflect/make_reflect.hpp"

//#include "ctp_scripts/2_scripts/make_interface/make_interface.hpp"
//#include "ctp_scripts/2_scripts/typeclass_instance/typeclass_instance.hpp"
//#include "ctp_scripts/2_scripts/typeclass/typeclass.hpp"
//#include "ctp_scripts/2_scripts/reflect_enum/reflect_enum.hpp"
//#include "ctp_scripts/2_scripts/make_removefuncbody/make_removefuncbody.hpp"

#include "clangPipeline.hpp"

namespace ctp_utils {

/// \brief scripts placed here will be bundled with CXXCTP_tool
/// (will become built-in C++ plugins)
/// \note that function may be usefull only if Cling is turned off
/// because functions may be called by name in Cling
void add_modulecallbacks() {
    clang_utils::add_cxxctp_callback("make_reflect", &make_reflect);

    //clang_utils::add_cxxctp_callback("make_interface", &make_interface);
    //clang_utils::add_cxxctp_callback("reflect_enum", &reflect_enum);
    //clang_utils::add_cxxctp_callback("typeclass", &typeclass);
    //clang_utils::add_cxxctp_callback("typeclass_instance", &typeclass_instance);
    //clang_utils::add_cxxctp_callback("make_removefuncbody", &make_removefuncbody);
}

} // namespace ctp_utils
