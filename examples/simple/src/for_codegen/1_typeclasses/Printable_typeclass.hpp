#pragma once

#include "cxxctp_macros.hpp"

#include <vector>
#include <string>

// like `trait`
struct
  $apply(
    typeclass
  )
Printable {
    virtual void print() const noexcept = 0;
};

