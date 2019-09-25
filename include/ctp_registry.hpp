#pragma once

namespace ctp_utils {

/// \brief scripts placed here will be bundled with CXXCTP_tool
/// (will become built-in C++ plugins)
/// \note that function may be usefull if Cling is turned off
/// because functions may be called by name in Cling
void add_modulecallbacks();

} // namespace ctp_utils
