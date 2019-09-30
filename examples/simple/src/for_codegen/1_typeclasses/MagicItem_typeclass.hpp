#pragma once

#include "cxxctp_macros.hpp"

#include <vector>
#include <string>

/// \note include here all required data structs
#include "MagicItem.hpp"

// like `trait`
struct
  $apply(
    typeclass
  )
__tc_MagicItem_1 : public MagicItem {
};

//typedef MagicTemplated<std::string, int> MagicTemplated1;

// like `trait`
struct
  $apply(
    typeclass
  )
__tc_MagicTemplated_1 : public MagicTemplated<std::string, int> {
};
