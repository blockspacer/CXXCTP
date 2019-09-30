#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "cxxctp_macros.hpp"

/// \note include here all required data structs
#include "WaterSpell.hpp"

// like impl for trait
struct
  $apply(
    typeclass_instance(target = "WaterSpell", "Spell", "MagicItem");
    typeclass_instance(target = "WaterSpell", "Printable")
  )
__tc_impl_WaterSpell_1 {
};

// like impl for trait
struct
  $apply(
    typeclass_instance(target = "WaterSpell", "MagicTemplated<std::string, int>")
  )
__tc_impl_WaterSpell_2 {
};
