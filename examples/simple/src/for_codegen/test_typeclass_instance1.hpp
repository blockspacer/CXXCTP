#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "cxxctp_macros.hpp"

// like impl for trait
struct
  $apply(
    typeclass_instance(Spell, MagicItem);
    typeclass_instance(Printable)
  )
FireSpell {
  std::string title = "FireSpell";
  std::string description = "FireSpell";
};

// like impl for trait
struct
  $apply(
    typeclass_instance(Spell, MagicItem);
    typeclass_instance(Printable)
  )
WaterSpell {
  std::string title = "WaterSpell";
  std::string description = "WaterSpell";
};
