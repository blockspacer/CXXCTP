#include "ctp_registry.h"

#include "app_loop.h"

void add_modulecallbacks() {
    add_cxxctp_callback("make_interface", &make_interface);
    add_cxxctp_callback("make_reflect", &make_reflect);
    add_cxxctp_callback("reflect_enum", &reflect_enum);
    add_cxxctp_callback("typeclass", &typeclass);
    add_cxxctp_callback("typeclass_instance", &typeclass_instance);
    add_cxxctp_callback("make_removefuncbody", &make_removefuncbody);
}
