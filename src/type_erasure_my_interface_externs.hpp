#pragma once

// A Circle implementation of the type erasure tactic implemented here:
// https://github.com/TartanLlama/typeclasses/blob/master/typeclass.hpp

//#include "../gems/util.hxx"
#include <memory>
#include <vector>
#include <map>
#include <cstdlib>
#include <cstring>
#include <type_traits>
#include <functional>
#include <string>

#include "types_for_erasure.hpp"
#include "type_erasure_common.hpp"

namespace cxxctp {
namespace generated {

////////////////////////////////////////////////////////////////////////////////
// The var_t class template is specialized to include all member functions in
// my_interface. It makes forwarding calls from these to the virtual
// functions in _tc_model_t.

// The typedef helps emphasize that we have a single type that encompasses
// multiple impl types that aren't related by inheritance.
typedef _tc_model_t<template_interface<int, const std::string&>> my_interface_model_t;
typedef _tc_combined_t<template_interface<int, const std::string&>> my_interface_obj_t;
template<typename T> using my_interface_impl_t = _tc_impl_t<T, template_interface<int, const std::string&>>;

template<
  typename T,
  typename V,
  typename std::enable_if<std::is_same<template_interface<int, const std::string&>, T>::value>::type* = nullptr
>
void draw(const V&, const char* surface) noexcept;

template<>
void draw<template_interface<int, const std::string&>, allcaps_t>(const allcaps_t&, const char* surface) noexcept;

template<>
void draw<template_interface<int, const std::string&>, forward_t>(const forward_t&, const char* surface) noexcept;

template<>
void draw<template_interface<int, const std::string&>, reverse_t>(const reverse_t&, const char* surface) noexcept;

/*template<
  typename T,
  typename std::enable_if<std::is_same<my_interface, T>::value>::type* = nullptr
>
void draw(const allcaps_t&, const char* surface);

template<
  typename T,
  typename std::enable_if<std::is_same<my_interface, T>::value>::type* = nullptr
>
void draw(const forward_t&, const char* surface);

template<
  typename T,
  typename std::enable_if<std::is_same<my_interface, T>::value>::type* = nullptr
>
void draw(const reverse_t&, const char* surface);*/

template<>
struct _tc_registry<template_interface<int, const std::string&>> {
  static constexpr size_t size = 3;

  template<typename concrete>
  static size_t getTypeIndex() noexcept;
};

template<>
size_t _tc_registry<template_interface<int, const std::string&>>::
    getTypeIndex<allcaps_t>() noexcept;

template<>
size_t _tc_registry<template_interface<int, const std::string&>>::
    getTypeIndex<reverse_t>() noexcept;

template<>
size_t _tc_registry<template_interface<int, const std::string&>>::
    getTypeIndex<forward_t>() noexcept;

} // namespace cxxctp
} // namespace generated
