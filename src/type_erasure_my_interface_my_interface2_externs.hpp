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
#include "type_erasure_my_interface.hpp"
#include "type_erasure_my_interface2.hpp"
#include "type_erasure_my_interface_my_interface2.hpp"

namespace cxxctp {
namespace generated {

// fixes warnings if func is explicitly instantiated in another translation unit
template <>
void _tc_combined_t<template_interface<int, const std::string&>, my_interface2>::set_set_bar<allcaps_t>(std::function<void(allcaps_t&, const std::string&)> arg) noexcept;

// fixes warnings if func is explicitly instantiated in another translation unit
template <>
void _tc_combined_t<template_interface<int, const std::string&>, my_interface2>::set_set_bar<reverse_t>(std::function<void(reverse_t&, const std::string&)> arg) noexcept;

// fixes warnings if func is explicitly instantiated in another translation unit
template <>
void _tc_combined_t<template_interface<int, const std::string&>, my_interface2>::set_set_bar<forward_t>(std::function<void(forward_t&, const std::string&)> arg) noexcept;

// fixes warnings if func is explicitly instantiated in another translation unit
template <>
void _tc_combined_t<template_interface<int, const std::string&>, my_interface2>::set_get_bar<allcaps_t>(std::function<std::string(allcaps_t&)> arg) noexcept;

// fixes warnings if func is explicitly instantiated in another translation unit
template <>
void _tc_combined_t<template_interface<int, const std::string&>, my_interface2>::set_get_bar<reverse_t>(std::function<std::string(reverse_t&)> arg) noexcept;

// fixes warnings if func is explicitly instantiated in another translation unit
template <>
void _tc_combined_t<template_interface<int, const std::string&>, my_interface2>::set_get_bar<forward_t>(std::function<std::string(forward_t&)> arg) noexcept;

////////////////////////////////////////////////////////////////////////////////
// The var_t class template is specialized to include all member functions in
// my_interface. It makes forwarding calls from these to the virtual
// functions in _tc_model_t.

// The typedef helps emphasize that we have a single type that encompasses
// multiple impl types that aren't related by inheritance.
typedef _tc_combined_t<template_interface<int, const std::string&>, my_interface2> my_interface_my_interface2_obj_t;

} // namespace cxxctp
} // namespace generated
