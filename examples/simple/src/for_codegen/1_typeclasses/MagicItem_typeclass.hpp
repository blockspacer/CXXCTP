#pragma once

#include "cxxctp_macros.hpp"

#include <vector>
#include <string>

// like `trait`
struct
  $apply(
    typeclass
  )
MagicItem {
  virtual void has_enough_mana(const char* spellname) const noexcept = 0;

  /// \note same for all types
  // @gen(inject_to_all)
  //S interface_data;
};
