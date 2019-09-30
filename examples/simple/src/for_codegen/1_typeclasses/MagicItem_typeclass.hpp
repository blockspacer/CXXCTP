#pragma once

#include "cxxctp_macros.hpp"

#include <vector>
#include <string>

/// \note include here all required data structs
#include "MagicItem.hpp"

// like `trait`
$typeclass(public MagicItem)

// like `trait`
/// \note example of merged typeclasses
/// \note in most cases prefer combined typeclasses to merged
$typeclass(
    public MagicTemplated<std::string, int>
    , public ParentTemplated_1<const char *>
    , public ParentTemplated_2<const int &>)
