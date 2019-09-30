#pragma once

#include "cxxctp_macros.hpp"

#include <vector>
#include <string>

/// \note include here all required data structs
#include "MagicItem.hpp"

// like `trait`
$typeclass(MagicItem)

// like `trait`
$typeclass(MagicTemplated<std::string, int>)
