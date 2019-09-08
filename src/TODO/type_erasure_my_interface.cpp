// A Circle implementation of the type erasure tactic implemented here:
// https://github.com/TartanLlama/typeclasses/blob/master/typeclass.hpp

//#include "../gems/util.hxx"
#include "type_erasure_my_interface.hpp"
#include "type_erasure_my_interface_externs.hpp"

namespace cxxctp {
namespace generated {

template <>
bool _tc_combined_t<template_interface<int, const std::string&>>::
  can_convert<template_interface<int, const std::string&>>() const
{
  return true;
}

///////////////////////////////////////////////////////////////////////////////

/*template <>
std::shared_ptr<_tc_model_t<template_interface<int, const std::string&>>>
  _tc_combined_t<template_interface<int, const std::string&>>
    ::ref_model<template_interface<int, const std::string&>>() const noexcept {
  return my_interface_model;
}*/

///////////////////////////////////////////////////////////////////////////////

template <>
_tc_impl_t<std::reference_wrapper<allcaps_t>, template_interface<int, const std::string&>>*
  _tc_model_t<template_interface<int, const std::string&>>::
    as<std::reference_wrapper<allcaps_t>>() noexcept {
  if(getModelTypeIndex()
      != _tc_combined_t<template_interface<int, const std::string&>>
        ::getGlobalTypeIndex<std::reference_wrapper<allcaps_t>>()) {
    return nullptr;
  }
  return static_cast<
    _tc_impl_t<std::reference_wrapper<allcaps_t>, template_interface<int, const std::string&>>*>(this);
}

template <>
_tc_impl_t<allcaps_t, template_interface<int, const std::string&>>*
  _tc_model_t<template_interface<int, const std::string&>>
    ::as<allcaps_t>() noexcept {
  if(getModelTypeIndex()
      != _tc_combined_t<template_interface<int, const std::string&>>
        ::getGlobalTypeIndex<allcaps_t>()) {
    return nullptr;
  }
  return static_cast<
    _tc_impl_t<allcaps_t, template_interface<int, const std::string&>>*>(this);
}

template <>
_tc_impl_t<reverse_t, template_interface<int, const std::string&>>*
  _tc_model_t<template_interface<int, const std::string&>>
    ::as<reverse_t>() noexcept {
  if(getModelTypeIndex()
      != _tc_combined_t<template_interface<int, const std::string&>>
        ::getGlobalTypeIndex<reverse_t>()) {
    return nullptr;
  }
  return static_cast<
    _tc_impl_t<reverse_t, template_interface<int, const std::string&>>*>(this);
}

template <>
_tc_impl_t<forward_t, template_interface<int, const std::string&>>*
  _tc_model_t<template_interface<int, const std::string&>>
    ::as<forward_t>() noexcept {
  if(getModelTypeIndex()
      != _tc_combined_t<template_interface<int, const std::string&>>
        ::getGlobalTypeIndex<forward_t>()) {
    return nullptr;
  }
  return static_cast<
    _tc_impl_t<forward_t, template_interface<int, const std::string&>>*>(this);
}

///////////////////////////////////////////////////////////////////////////////

template <>
std::reference_wrapper<allcaps_t>& _tc_model_t<template_interface<int, const std::string&>>::ref_concrete<std::reference_wrapper<allcaps_t>>() noexcept {
  const auto casted = as<std::reference_wrapper<allcaps_t>>();
  if(!casted) {
    std::terminate();
  }
  return casted
    ->concrete;
}

template <>
allcaps_t& _tc_model_t<template_interface<int, const std::string&>>::ref_concrete<allcaps_t>() noexcept {
  const auto casted = as<allcaps_t>();
  if(!casted) {
    std::terminate();
  }
  return casted
    ->concrete;
}

template <>
reverse_t& _tc_model_t<template_interface<int, const std::string&>>::ref_concrete<reverse_t>() noexcept {
  const auto casted = as<reverse_t>();
  if(!casted) {
    std::terminate();
  }
  return casted
    ->concrete;
}

template <>
forward_t& _tc_model_t<template_interface<int, const std::string&>>::ref_concrete<forward_t>() noexcept {
  const auto casted = as<forward_t>();
  if(!casted) {
    std::terminate();
  }
  return casted
    ->concrete;
}

///////////////////////////////////////////////////////////////////////////////

#if 0
extern template
 /*explicit*/ void draw<my_interface>
  (const allcaps_t&, const char* surface);

extern template
 /*explicit*/ void draw<my_interface>
  (const allcaps_t&, const char* surface);

extern template
 /*explicit*/ void draw<my_interface>
  (const reverse_t&, const char* surface);
#endif // 0

void _tc_model_t<template_interface<int, const std::string&>>::
    set_interface_data(const char* text) noexcept {
  interface_data = text;
}

void _tc_model_t<template_interface<int, const std::string&>>::
    print_interface_data() const noexcept {
  auto out = std::string("interface_data: ") + interface_data;
  puts(out.c_str());
}

// ====

_tc_impl_t<allcaps_t, template_interface<int, const std::string&>>::
    _tc_impl_t(const allcaps_t& concrete_arg) noexcept
  : concrete(concrete_arg) {}

std::unique_ptr<_tc_model_t<template_interface<int, const std::string&>>>
 _tc_impl_t<allcaps_t, template_interface<int, const std::string&>>::clone() noexcept {
  // Copy-construct a new instance of _tc_impl_t on the heap.
  return std::make_unique<_tc_impl_t>(concrete);
}

bool _tc_impl_t<allcaps_t, template_interface<int, const std::string&>>
    ::__has_save() const noexcept {
  return false;
}

void _tc_impl_t<allcaps_t, template_interface<int, const std::string&>>
    ::__save(const char* filename, const char* access) noexcept {
  // TODO: noexcept
  //throw std::runtime_error("allcaps_t::save not implemented");
  std::terminate();
}

/*template <typename ...Params>
void print(Params&&... args) override final {
  return concrete.print(std::forward<decltype(args)>(args)...);
}*/

bool _tc_impl_t<allcaps_t, template_interface<int, const std::string&>>
    ::__has_print() const noexcept {
  return true;
}

void _tc_impl_t<allcaps_t, template_interface<int, const std::string&>>
    ::__print(const char* text) const noexcept {
  return concrete.print(concrete, std::forward<decltype(text)>(text));
}

void _tc_impl_t<allcaps_t, template_interface<int, const std::string&>>
    ::__set_data(const char* text) noexcept {
  return concrete.set_data(concrete, std::forward<decltype(text)>(text));
}

void _tc_impl_t<allcaps_t, template_interface<int, const std::string&>>
    ::__print_data() const noexcept {
  return concrete.print_data(concrete);
}

void _tc_impl_t<allcaps_t, template_interface<int, const std::string&>>
    ::__draw(const char* surface) const noexcept {
  return draw<template_interface<int, const std::string&>>(concrete, surface);
}


// ====

_tc_impl_t<std::reference_wrapper<allcaps_t>, template_interface<int, const std::string&>>::
    _tc_impl_t(const std::reference_wrapper<allcaps_t>& concrete_arg) noexcept
  : concrete(concrete_arg) {}

#if 0
std::unique_ptr<_tc_model_t<template_interface<int, const std::string&>>>
 _tc_impl_t<std::reference_wrapper<allcaps_t>, template_interface<int, const std::string&>>::clone() {
  // Copy-construct a new instance of _tc_impl_t on the heap.
  /// \note clones data, not ref
  return std::make_unique<_tc_impl_t>(concrete/*.get()*/);
}
#endif // 0

bool _tc_impl_t<std::reference_wrapper<allcaps_t>, template_interface<int, const std::string&>>::__has_save() const noexcept {
  return false;
}

void _tc_impl_t<std::reference_wrapper<allcaps_t>, template_interface<int, const std::string&>>::__save(const char* filename, const char* access) noexcept {
  // TODO: noexcept
  //throw std::runtime_error("allcaps_t::save not implemented");
  std::terminate();
}

/*template <typename ...Params>
void print(Params&&... args) override final {
  return concrete.print(std::forward<decltype(args)>(args)...);
}*/

bool _tc_impl_t<std::reference_wrapper<allcaps_t>, template_interface<int, const std::string&>>::__has_print() const noexcept {
  return true;
}

void _tc_impl_t<std::reference_wrapper<allcaps_t>, template_interface<int, const std::string&>>::__print(const char* text) const noexcept {
  /// \note passes data, not ref
  return concrete.get().print(concrete, std::forward<decltype(text)>(text));
}

void _tc_impl_t<std::reference_wrapper<allcaps_t>, template_interface<int, const std::string&>>::__set_data(const char* text) noexcept {
  /// \note passes data, not ref
  return concrete.get().set_data(concrete, std::forward<decltype(text)>(text));
}

void _tc_impl_t<std::reference_wrapper<allcaps_t>, template_interface<int, const std::string&>>::__print_data() const noexcept {
  /// \note passes data, not ref
  return concrete.get().print_data(concrete);
}

void _tc_impl_t<std::reference_wrapper<allcaps_t>, template_interface<int, const std::string&>>::__draw(const char* surface) const noexcept {
  /// \note passes data, not ref
  return draw<template_interface<int, const std::string&>>(concrete.get(), surface);
}

// ====

void _tc_impl_t<forward_t, template_interface<int, const std::string&>>::__draw(const char* surface) const noexcept {
  return draw<template_interface<int, const std::string&>>(concrete, surface);
}

// ====

void _tc_impl_t<reverse_t, template_interface<int, const std::string&>>::__draw(const char* surface) const noexcept {
  return draw<template_interface<int, const std::string&>>(concrete, surface);
}

// ====

#if 0
int main() {

  // Construct an object a.
  obj_t a = obj_t::construct<allcaps_t>();
  a.print("Hello a");

  // Copy-construc a to get b.
  obj_t b = a;
  b.print("Hello b");

  if(b.has_save())
    b.save("my.save", "w");

  // Copy-assign a to get c.
  obj_t c;
  c = b;
  c.print("Hello c");

  // Create a forward object.
  obj_t d = obj_t::construct<forward_t>();
  d.print("Hello d");
  d.save("foo.save", "w");

  // Create a reverse object.
  obj_t e = obj_t::construct<reverse_t>();
  e.print("Hello e");

  // Throws:
  // terminate called after throwing an instance of 'std::runtime_error'
  //   what():  reverse_t::save not implemented
  e.save("bar.save", "w");

  return 0;
}
#endif // 0

/*template<>
void _tc_impl_t<allcaps_t, my_interface>::draw(const allcaps_t &)
{

}*/

template<>
size_t _tc_registry<template_interface<int, const std::string&>>::
    getTypeIndex<std::reference_wrapper<allcaps_t>>() noexcept {
 constexpr size_t ret = 0;
 static_assert(ret < std::numeric_limits<size_t>::max(),
    "Registered too many types in"
    " _tc_registry<template_interface<int, const std::string&>>");
  return ret;
}

template<>
size_t _tc_registry<template_interface<int, const std::string&>>::
    getTypeIndex<allcaps_t>() noexcept {
 constexpr size_t ret = 1;
 static_assert(ret < std::numeric_limits<size_t>::max(),
    "Registered too many types in"
    " _tc_registry<template_interface<int, const std::string&>>");
  return ret;
}

template<>
size_t _tc_registry<template_interface<int, const std::string&>>::
    getTypeIndex<reverse_t>() noexcept {
 constexpr size_t ret = 2;
 static_assert(ret < std::numeric_limits<size_t>::max(),
    "Registered too many types in"
    " _tc_registry<template_interface<int, const std::string&>>");
  return ret;
}

template<>
size_t _tc_registry<template_interface<int, const std::string&>>::
    getTypeIndex<forward_t>() noexcept {
 constexpr size_t ret = 3;
 static_assert(ret < std::numeric_limits<size_t>::max(),
    "Registered too many types in"
    " _tc_registry<template_interface<int, const std::string&>>");
  return ret;
}

} // namespace cxxctp
} // namespace generated
