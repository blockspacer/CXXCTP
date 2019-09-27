#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "cxxctp_macros.hpp"

/// \note include here all required data structs
#include "FireSpell.hpp"

// like impl for trait
struct
  $apply(
    typeclass_instance(target = FireSpell, Spell, MagicItem)
  )
__tc_Impl1 {};

// like impl for trait
struct
  $apply(
    typeclass_instance(target = FireSpell, Printable)
  )
__tc_Impl2 {};
