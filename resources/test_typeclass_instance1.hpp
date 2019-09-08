#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "cling_common.hpp"

// Print the text in forward order.
struct
    $apply(typeclass_instance(Spell))
        SpellBook {
    std::string title = "MySpellBook";
    std::string description = "spell book full of spells";
};
