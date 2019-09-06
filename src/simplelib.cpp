#include <iostream>
#include <cstring>
#include <type_traits>

#include "types_for_erasure.hpp"
#include "type_erasure_my_interface.hpp"
#include "type_erasure_my_interface_externs.hpp"
#include "type_erasure_my_interface2.hpp"
#include "type_erasure_my_interface2_externs.hpp"
#include "type_erasure_my_interface_my_interface2.hpp"
#include "type_erasure_my_interface_my_interface2_externs.hpp"

// see https://michael-thomas-greer.com/faq/enum/macro-trick/

// ==============

namespace cxxctp {
namespace generated {

  template<>
  void draw<template_interface<int, const std::string&>/*obj_t::typeclass_t*/>
      (const allcaps_t& data, const char* surface) noexcept {
    /// \note don`t use get_concrete<type> here, it may be get_concrete<ref_type>
    std::cout << "(lib1) Drawing allcaps_t on " << surface
      << " with data " << data.allcaps_t_data << std::endl;
  }

  template<>
  void draw<template_interface<int, const std::string&>/*obj_t::typeclass_t*/>
      (const forward_t& data, const char* surface) noexcept {
    /// \note don`t use get_concrete<type> here, it may be get_concrete<ref_type>
    std::cout << "(lib1) Drawing forward_t on " << surface
      << " with data " << data.forward_t_data << std::endl;
  }

  template<>
  void draw<template_interface<int, const std::string&>/*obj_t::typeclass_t*/>
      (const reverse_t& data, const char* surface) noexcept {
    /// \note don`t use get_concrete<type> here, it may be get_concrete<ref_type>
    std::cout << "(lib1) Drawing reverse_t on " << surface
      << " with data " << data.reverse_t_data << std::endl;
  }

  /*template<typename A>
  std::string _tc_impl_t<allcaps_t, my_interface2>::
    show(allcaps_t const &, A const & arg2) noexcept {
    std::cout << "(lib) show for allcaps_t !!!" << arg2 << std::endl;
    return "(lib) show for allcaps_t !!!";
  };

  template<typename A>
  std::string _tc_impl_t<reverse_t, my_interface2>::
    show(reverse_t const &, A const & arg2) noexcept {
    std::cout << "(lib) show for reverse_t !!!" << arg2 << std::endl;
    return "(lib) show for reverse_t !!!";
  };

  template<typename A>
  std::string _tc_impl_t<forward_t, my_interface2>::
    show(forward_t const &, A const & arg2) noexcept {
    std::cout << "(lib) show for forward_t !!!" << arg2 << std::endl;
    return "(lib) show for forward_t !!!";
  };*/

} // namespace cxxctp
} // namespace generated
