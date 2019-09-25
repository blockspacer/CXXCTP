#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "cxxctp_macros.hpp"

    //$apply(typeclass_instance(Spell))

// Print the text in forward order.
struct __attribute__((annotate("{gen};{funccall};typeclass_instance(Spell)")))
        SpellBook {
    std::string title = "MySpellBook";
    std::string description = "spell book full of spells";
};
