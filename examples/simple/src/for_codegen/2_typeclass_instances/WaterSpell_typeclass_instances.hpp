#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "cxxctp_macros.hpp"

/// \note include here all required data structs
#include "WaterSpell.hpp"

// like impl for trait
/// \note example of combined typeclasses, see `typeclass_combo`
$typeclass_impl(
  typeclass_instance(target = "WaterSpell",
    "Spell", "MagicItem");
  typeclass_instance(target = "WaterSpell",
    "Printable")
)

// like impl for trait
/// \note example of merged typeclasses
/// \note in most cases prefer combined typeclasses to merged
$typeclass_impl(
  typeclass_instance(
    target = "WaterSpell",
    "MagicTemplated<std::string, int>,"
    "ParentTemplated_1<const char *>,"
    "ParentTemplated_2<const int &>")
)
