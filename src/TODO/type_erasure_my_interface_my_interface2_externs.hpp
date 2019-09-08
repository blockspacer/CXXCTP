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
//#include "type_erasure_my_interface.hpp"
//#include "type_erasure_my_interface2.hpp"
//#include "type_erasure_my_interface_my_interface2.hpp"

namespace cxxctp {
namespace generated {

////////////////////////////////////////////////////////////////////////////////
// The var_t class template is specialized to include all member functions in
// my_interface. It makes forwarding calls from these to the virtual
// functions in _tc_model_t.

// The typedef helps emphasize that we have a single type that encompasses
// multiple impl types that aren't related by inheritance.
typedef _tc_combined_t<template_interface<int, const std::string&>, my_interface2> my_interface_my_interface2_obj_t;

} // namespace cxxctp
} // namespace generated
