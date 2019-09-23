#include "ctp_registry.hpp"

#include "resources/ctp_scripts/make_interface.hpp"
#include "resources/ctp_scripts/make_reflect.hpp"
#include "resources/ctp_scripts/typeclass_instance.hpp"
#include "resources/ctp_scripts/typeclass.hpp"
#include "resources/ctp_scripts/reflect_enum.hpp"
#include "resources/ctp_scripts/make_removefuncbody.hpp"

#include "src/clangPipeline.hpp"

/// \note that function may be usefull only if Cling is turned off
/// because functions may be called by name in Cling
#if !defined(CLING_IS_ON)
void add_modulecallbacks() {
    clang_utils::add_cxxctp_callback("make_interface", &make_interface);
    clang_utils::add_cxxctp_callback("make_reflect", &make_reflect);
    clang_utils::add_cxxctp_callback("reflect_enum", &reflect_enum);
    clang_utils::add_cxxctp_callback("typeclass", &typeclass);
    clang_utils::add_cxxctp_callback("typeclass_instance", &typeclass_instance);
    clang_utils::add_cxxctp_callback("make_removefuncbody", &make_removefuncbody);
}
#endif // CLING_IS_ON
