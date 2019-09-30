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
    typeclass_instance(target = "FireSpell", "Spell", "MagicItem")
  )
__tc_impl_FireSpell_1 {};

// like impl for trait
struct
  $apply(
    typeclass_instance(target = "FireSpell", "Printable")
  )
__tc_impl_FireSpell_2 {};

// like impl for trait
struct
  $apply(
    typeclass_instance(target = "FireSpell", "MagicTemplated<std::string, int>")
  )
__tc_impl_FireSpell_3 {
};
