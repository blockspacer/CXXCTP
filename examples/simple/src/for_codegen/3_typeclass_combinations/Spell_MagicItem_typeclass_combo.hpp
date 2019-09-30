#pragma once

#include "cxxctp_macros.hpp"

#include <vector>
#include <string>
#include <iostream>

// just wraps multiple `traits`, forwards calls
/// \note example of combined typeclasses
$typeclass_combo(
  typeclass_combo(Spell, MagicItem)
)
