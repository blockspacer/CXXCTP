#include "generated/MagicTemplated_std__string__int__ParentTemplated_1_const_char____ParentTemplated_2_const_int___.typeclass.generated.hpp"

#include "generated/FireSpell_MagicTemplated_std__string__int__ParentTemplated_1_const_char____ParentTemplated_2_const_int___.typeclass_instance.generated.hpp"

#include <vector>
#include <iostream>

namespace cxxctp {
namespace generated {

template<>
void has_T<
  MagicTemplated<std::string, int>,
  ParentTemplated_1<const char *>,
  ParentTemplated_2<const int &>
  , FireSpell >
(const FireSpell& data, const std::string &name1, const int &name2) noexcept {
    /// \note don`t use get_concrete<type> here, it may be get_concrete<ref_type>
    std::cout << "(Fire) has_T on " << name1
              << " by " << name2 << " "
              << std::endl;
}

template<>
void has_P1<
  MagicTemplated<std::string, int>,
  ParentTemplated_1<const char *>,
  ParentTemplated_2<const int &>
  , FireSpell >
(const FireSpell& data, const char *name1) noexcept {
    /// \note don`t use get_concrete<type> here, it may be get_concrete<ref_type>
    std::cout << "(FireSpell) has_P1 on " << name1
              << std::endl;
}

template<>
void has_P2<
  MagicTemplated<std::string, int>,
  ParentTemplated_1<const char *>,
  ParentTemplated_2<const int &>
  , FireSpell >
(const FireSpell& data, const int& name1) noexcept {
    /// \note don`t use get_concrete<type> here, it may be get_concrete<ref_type>
    std::cout << "(FireSpell) has_P2 on " << name1
              << std::endl;
}

} // namespace cxxctp
} // namespace generated
