﻿#pragma once

#include <vector>
#include <string>

// like `trait`
//template<typename S, typename A>
struct Spell {
  virtual void cast(const char* spellname, const int spellpower,
                    const char* target) const noexcept = 0;

  virtual void has_spell(const char* spellname) const noexcept = 0;

  virtual void add_spell(const char* spellname) const noexcept = 0;

  virtual void remove_spell(const char* spellname) const noexcept = 0;

  virtual void set_spell_power(const char* spellname,
                               const int spellpower) const noexcept = 0;

  /// \note same for all types
  // @gen(inject_to_all)
  //S interface_data;
};

