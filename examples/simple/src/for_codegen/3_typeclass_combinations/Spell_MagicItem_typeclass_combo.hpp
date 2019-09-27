#pragma once

#include "cxxctp_macros.hpp"

#include <vector>
#include <string>
#include <iostream>

// just wraps multiple `traits`, forwards calls
struct
  $apply(
    typeclass_combo(Spell, MagicItem)
  )
Spell_MagicItem {
};
