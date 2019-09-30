#pragma once

#include "cxxctp_macros.hpp"

#include <vector>
#include <string>
#include <iostream>

// just wraps multiple `traits`, forwards calls
$typeclass_combo(
  typeclass_combo(Spell, MagicItem)
)
