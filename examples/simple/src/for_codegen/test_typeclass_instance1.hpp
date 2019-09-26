#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "cxxctp_macros.hpp"

struct $apply(typeclass_instance(Spell))
        FireSpell {
    std::string title = "FireSpell";
    std::string description = "FireSpell";
};

struct $apply(typeclass_instance(Spell))
        WaterSpell {
    std::string title = "WaterSpell";
    std::string description = "WaterSpell";
};
