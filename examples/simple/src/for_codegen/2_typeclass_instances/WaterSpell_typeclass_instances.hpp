#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "cxxctp_macros.hpp"

/// \note include here all required data structs
#include "WaterSpell.hpp"

// like impl for trait
$typeclass_impl(
  typeclass_instance(target = "WaterSpell", "Spell", "MagicItem");
  typeclass_instance(target = "WaterSpell", "Printable")
)

// like impl for trait
$typeclass_impl(
  typeclass_instance(target = "WaterSpell", "MagicTemplated<std::string, int>")
)
