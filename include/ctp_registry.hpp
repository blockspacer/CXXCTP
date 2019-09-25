#pragma once

/// \note that function may be usefull only if Cling is turned off
/// because functions may be called by name in Cling
#if !defined(CLING_IS_ON)
void add_modulecallbacks();
#endif // CLING_IS_ON
