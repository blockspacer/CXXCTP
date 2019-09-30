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
__tc_combo_Spell_MagicItem_1 {
};
