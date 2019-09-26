#pragma once

#include "cxxctp_macros.hpp"

#include <vector>
#include <string>
#include <iostream>

/*  $export (
static int resultSomeInt = 2345;
  )*/

struct $apply(typeclass)
        Spell {
    virtual void cast(const char* spellname, const int spellpower,
                      const char* target) const noexcept = 0;

    virtual void has_spell(const char* spellname) const noexcept = 0;

    virtual void add_spell(const char* spellname) const noexcept = 0;

    virtual void remove_spell(const char* spellname) const noexcept = 0;

    virtual void set_spell_power(const char* spellname,
                                 const int spellpower) const noexcept = 0;
};
