#pragma once

#include <vector>
#include <string>

// like `trait`
struct
MagicItem {
  virtual void has_enough_mana(const char* spellname) const noexcept = 0;

  /// \note same for all types
  // @gen(inject_to_all)
  //S interface_data;
};

template<typename T1>
struct
ParentTemplated_1 {
  virtual void has_P1(T1 name1) const noexcept = 0;
};

template<typename T1>
struct
ParentTemplated_2 {
  virtual void has_P2(T1 name1) const noexcept = 0;
};

// like `trait`
template<typename T1, typename T2>
struct
MagicTemplated {
  virtual void has_T(const T1& name1, const T2& name2) const noexcept = 0;

  /// \note same for all types
  // @gen(inject_to_all)
  //S interface_data;
};
