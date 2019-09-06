// A Circle implementation of the type erasure tactic implemented here:
// https://github.com/TartanLlama/typeclasses/blob/master/typeclass.hpp

//#include "../gems/util.hxx"
#include "type_erasure_my_interface_my_interface2.hpp"

namespace cxxctp {
namespace generated {
  template <>
  bool _tc_combined_t<template_interface<int, const std::string&>, my_interface2>::
    can_convert<template_interface<int, const std::string&>>() const
  {
    return true;
  }

  template <>
  bool _tc_combined_t<template_interface<int, const std::string&>, my_interface2>::
    can_convert<my_interface2>() const
  {
    return true;
  }

  template <>
  void _tc_combined_t<template_interface<int, const std::string&>, my_interface2>::set_set_bar<allcaps_t>(std::function<void(allcaps_t&, const std::string&)> arg) noexcept {
    if(!my_interface2_model) {
      //throw std::runtime_error("my_interface_model2 not set");
      std::terminate();
    }
    return static_cast<_tc_impl_t<allcaps_t, my_interface2>*>(my_interface2_model.get())
      ->__set_set_bar(std::forward<decltype(arg)>(arg));
  }

  template <>
  void _tc_combined_t<template_interface<int, const std::string&>, my_interface2>::set_set_bar<reverse_t>(std::function<void(reverse_t&, const std::string&)> arg) noexcept {
    if(!my_interface2_model) {
      //throw std::runtime_error("my_interface_model2 not set");
      std::terminate();
    }
    return static_cast<_tc_impl_t<reverse_t, my_interface2>*>(my_interface2_model.get())
      ->__set_set_bar(std::forward<decltype(arg)>(arg));
  }

  template <>
  void _tc_combined_t<template_interface<int, const std::string&>, my_interface2>::set_set_bar<forward_t>(std::function<void(forward_t&, const std::string&)> arg) noexcept {
    if(!my_interface2_model) {
      //throw std::runtime_error("my_interface_model2 not set");
      std::terminate();
    }
    return static_cast<_tc_impl_t<forward_t, my_interface2>*>(my_interface2_model.get())
      ->__set_set_bar(std::forward<decltype(arg)>(arg));
  }

  template <>
  void _tc_combined_t<template_interface<int, const std::string&>, my_interface2>::set_get_bar<allcaps_t>(std::function<std::string(allcaps_t&)> arg) noexcept {
    if(!my_interface2_model) {
      //throw std::runtime_error("my_interface_model2 not set");
      std::terminate();
    }
    return static_cast<_tc_impl_t<allcaps_t, my_interface2>*>(my_interface2_model.get())
      ->__set_get_bar(std::forward<decltype(arg)>(arg));
  }

  template <>
  void _tc_combined_t<template_interface<int, const std::string&>, my_interface2>::set_get_bar<reverse_t>(std::function<std::string(reverse_t&)> arg) noexcept {
    if(!my_interface2_model) {
      //throw std::runtime_error("my_interface_model2 not set");
      std::terminate();
    }
    return static_cast<_tc_impl_t<reverse_t, my_interface2>*>(my_interface2_model.get())
      ->__set_get_bar(std::forward<decltype(arg)>(arg));
  }

  template <>
  void _tc_combined_t<template_interface<int, const std::string&>, my_interface2>::set_get_bar<forward_t>(std::function<std::string(forward_t&)> arg) noexcept {
    if(!my_interface2_model) {
      //throw std::runtime_error("my_interface_model2 not set");
      std::terminate();
    }
    return static_cast<_tc_impl_t<forward_t, my_interface2>*>(my_interface2_model.get())
      ->__set_get_bar(std::forward<decltype(arg)>(arg));
  }

#if 0
  // ================
  template <>
  allcaps_t& _tc_combined_t<my_interface, my_interface2>::ref_concrete<allcaps_t, my_interface>() {
    /*return static_cast<_tc_impl_t<allcaps_t, my_interface>*>(my_interface_model.get())
      ->concrete;*/
    return my_interface_model->ref_concrete<allcaps_t>();
  }
  template <>
  reverse_t& _tc_combined_t<my_interface, my_interface2>::ref_concrete<reverse_t, my_interface>() {
    /*return static_cast<_tc_impl_t<reverse_t, my_interface>*>(my_interface_model.get())
      ->concrete;*/
    return my_interface_model->ref_concrete<reverse_t>();
  }
  template <>
  forward_t& _tc_combined_t<my_interface, my_interface2>::ref_concrete<forward_t, my_interface>() {
    /*return static_cast<_tc_impl_t<forward_t, my_interface>*>(my_interface_model.get())
      ->concrete;*/
    return my_interface_model->ref_concrete<forward_t>();
  }

  // ================
  template <>
  allcaps_t& _tc_combined_t<my_interface, my_interface2>::ref_concrete<allcaps_t, my_interface2>() {
    /*return static_cast<_tc_impl_t<allcaps_t, my_interface2>*>(my_interface2_model.get())
      ->concrete;*/
    return my_interface2_model->ref_concrete<allcaps_t>();
  }
  template <>
  reverse_t& _tc_combined_t<my_interface, my_interface2>::ref_concrete<reverse_t, my_interface2>() {
    /*return static_cast<_tc_impl_t<reverse_t, my_interface2>*>(my_interface2_model.get())
      ->concrete;*/
    return my_interface2_model->ref_concrete<reverse_t>();
  }
  template <>
  forward_t& _tc_combined_t<my_interface, my_interface2>::ref_concrete<forward_t, my_interface2>() {
    /*return static_cast<_tc_impl_t<forward_t, my_interface2>*>(my_interface2_model.get())
      ->concrete;*/
    return my_interface2_model->ref_concrete<forward_t>();
  }
#endif // 0

} // namespace cxxctp
} // namespace generated
