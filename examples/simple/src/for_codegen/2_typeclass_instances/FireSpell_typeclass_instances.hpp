#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "cxxctp_macros.hpp"

/// \note include here all required data structs
#include "FireSpell.hpp"

// like impl for trait
$typeclass_impl(
  typeclass_instance(target = "FireSpell", "Spell", "MagicItem")
)

// like impl for trait
$typeclass_impl(
  typeclass_instance(target = "FireSpell", "Printable")
)

// like impl for trait
$typeclass_impl(
  typeclass_instance(target = "FireSpell", "MagicTemplated<std::string, int>")
)
