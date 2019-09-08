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
#include <any>
#include <iostream>

#include "types_for_erasure.hpp"
#include "type_erasure_common.hpp"
#include "type_erasure_my_interface_externs.hpp"

namespace cxxctp {
namespace generated {

/*struct common__tc_model_t {
  virtual ~common__tc_model_t() { }
};*/

template<>
struct _tc_model_t<template_interface<int, const std::string&>> {
  virtual ~_tc_model_t() noexcept { }

  // from template S drawTo(A);
  //template <typename T>
  //int drawTo(const std::string& str);

  //virtual int __drawTo(const std::string& str) = 0;

  // TODO std::function
  // https://stackoverflow.com/a/45718187
  /*template<class ReturnType, class... Args>
  // , std::function<ReturnType(Args...) f
  bool has_func
    (const std::string& func_name) const {
      return false;
    };*/

  // TODO: param_types
  // https://stackoverflow.com/a/39196427
  // https://github.com/tompollok/paco/blob/master/main.cpp#L94
  // https://gn.googlesource.com/gn/+/refs/heads/master/base/bind_internal.h#630

  virtual std::unique_ptr<_tc_model_t> clone() noexcept = 0;
  virtual std::unique_ptr<_tc_model_t> move_clone() noexcept = 0;

  virtual const size_t getModelTypeIndex() const noexcept = 0;

  virtual bool __has_save() const noexcept = 0;

  //template <typename ...Params>
  //virtual void save(Params&&... args) = 0;
  //virtual void __save(const char* filename, const char* access) = 0;
  virtual void __save(const char* filename, const char* access) noexcept {
    printf("default (unimplemented) save called for %s %s\n", filename, access);
  }

  virtual bool __has_print_2() const noexcept = 0;
  virtual void __print_2(const char* text) const noexcept = 0;

  virtual bool __has_print() const noexcept = 0;

  //template <typename ...Params>
  //virtual void print(Params&&... args) = 0;
  virtual void __print(const char* text) const noexcept = 0;

  virtual void __set_data(const char* text) noexcept = 0;

  virtual void __print_data() const noexcept = 0;

  virtual void __draw(const char* surface) const noexcept = 0;

  template <typename T>
  T& ref_concrete() noexcept;

  // TODO: pseudo inheritance by code injection
  /// \note same for all types
  void set_interface_data(const char* text) noexcept;/* {
    interface_data = text;
  }*/

  template <typename U>
  _tc_impl_t<U, template_interface<int, const std::string&>>* as() noexcept
  {
    return nullptr;
  }

  /// \note same for all types
  void print_interface_data() const noexcept;/* {
    auto out = std::string("interface_data: ") + interface_data;
    puts(out.c_str());
  }*/
  /// \note same for all types
  std::string interface_data = "interface_data";

  // TODO: https://stackoverflow.com/a/26159287
  //template<typename... Args>
  //std::map<std::string, void(*)()> runtime_dispatch_table_;
};

// ==================

template <>
allcaps_t& _tc_model_t<template_interface<int, const std::string&>>::ref_concrete<allcaps_t>() noexcept;

template<>
struct _tc_impl_t<allcaps_t, template_interface<int, const std::string&>>
    : public _tc_model_t<template_interface<int, const std::string&>> {
  typedef allcaps_t val_type_t;
  //friend void draw(const allcaps_t&);

  //static size_t constexpr type_hash = Hash("reverse_t");

  // Construct the embedded concrete type.
  template<typename... args_t>
  _tc_impl_t(args_t&&... args) noexcept : concrete(std::forward<args_t>(args)...) { }

  explicit _tc_impl_t(const allcaps_t& concrete_arg) noexcept;

  const size_t getModelTypeIndex() const noexcept override final {
    return _tc_registry<template_interface<int, const std::string&>>::
      getTypeIndex<allcaps_t>();
  }

  std::unique_ptr<
    _tc_model_t<template_interface<int, const std::string&>>>
      clone() noexcept override final;

  std::unique_ptr<
    _tc_model_t<template_interface<int, const std::string&>>>
      move_clone() noexcept override final {
    return std::make_unique<_tc_impl_t>(std::move(concrete));
  }

  bool __has_save() const noexcept override final;

  void __save(const char* filename, const char* access) noexcept override final;

  /*template <typename ...Params>
  void print(Params&&... args) override final {
    return concrete.print(std::forward<decltype(args)>(args)...);
  }*/

  bool __has_print_2() const noexcept override final {
    return true;
  }
  void __print_2(const char* text) const noexcept override final {
    return concrete.print_2(concrete, std::forward<decltype(text)>(text));
  }

  bool __has_print() const noexcept override final;

  void __print(const char* text) const noexcept override final;

  void __set_data(const char* text) noexcept override final;

  void __print_data() const noexcept override final;

  void __draw(const char* surface) const noexcept override final;

  /*void set_interface_data(const char* text) {
    return set_interface_data(std::forward<decltype(text)>(text));
  }

  void print_interface_data() {
    return print_interface_data();
  }*/

  /*template <typename ...Params>
  void save(Params&&... args) override final {
    throw std::runtime_error("allcaps_t::save not implemented");
  }*/

  // Loop over each member function on the interface.
  /*@meta for(int i = 0; i < @method_count(typeclass); ++i) {

    @meta std::string func_name = @method_name(typeclass, i);

    @meta bool is_valid = @sfinae(
      std::declval<type_t>().@(func_name)(
        std::declval<@method_params(typeclass, i)>()...
      )
    );

    // Implement the has_XXX function.
    bool @(format("has_%s", func_name.c_str()))() const override final {
      return is_valid;
    }

    // Declare an override function with the same signature as the pure virtual
    // function in _tc_model_t.
    @func_decl(@method_type(typeclass, i), func_name, args) override final {

      @meta if(is_valid || @sfinae(typeclass::required::@(__func__))) {
        // Forward to the correspondingly-named member function in type_t.
        return concrete.@(__func__)(std::forward<decltype(args)>(args)...);

      } else {

        // We could also call __cxa_pure_virtual or std::terminate here.
        throw std::runtime_error(@string(format("%s::%s not implemented",
          @type_name(type_t), __func__
        )));
      }
    }
  }*/

  allcaps_t* operator->() {
      return &concrete;
  }

  // Our actual data.
  allcaps_t concrete;
};


// ==================

template <>
std::reference_wrapper<allcaps_t>& _tc_model_t<template_interface<int, const std::string&>>::ref_concrete<std::reference_wrapper<allcaps_t>>() noexcept;

template<>
struct _tc_impl_t<std::reference_wrapper<allcaps_t>, template_interface<int, const std::string&>>
    : public _tc_model_t<template_interface<int, const std::string&>> {
  typedef std::reference_wrapper<allcaps_t> val_type_t;
  //friend void draw(const allcaps_t&);

  //static size_t constexpr type_hash = Hash("_tc_impl_t");

  // Construct the embedded concrete type.
  template<typename... args_t>
  _tc_impl_t(args_t&&... args) noexcept : concrete(std::forward<args_t>(args)...) { }

  explicit _tc_impl_t(const std::reference_wrapper<allcaps_t>& concrete_arg) noexcept;

  std::unique_ptr<
    _tc_model_t<template_interface<int, const std::string&>>>
      clone() noexcept override final {
    std::cout << "called clone "
                 "for ref template_interface allcaps_t" << std::endl;
    // Copy-construct a new instance of _tc_impl_t on the heap.
    return std::make_unique<_tc_impl_t<allcaps_t, template_interface<int, const std::string&>>>
      (allcaps_t{concrete.get()});
    /*return std::make_unique<_tc_impl_t<allcaps_t, _tc_model_t<template_interface<int, const std::string&>>>
      (std::move(cloned));*/
  }

  const size_t getModelTypeIndex() const noexcept override final {
    return _tc_registry<template_interface<int, const std::string&>>::
      getTypeIndex<std::reference_wrapper<allcaps_t>>();
  }

#if 0
  /// \note disallow move on ref
  std::unique_ptr<
    _tc_model_t<template_interface<int, const std::string&>>>
      move_clone() noexcept override final {
    return nullptr;
  };
#endif

  std::unique_ptr<
    _tc_model_t<template_interface<int, const std::string&>>>
      move_clone() noexcept override final {
    std::cout << "called move_clone "
                 "for ref template_interface allcaps_t" << std::endl;
    /// \note moves data, not ref
    return std::make_unique<_tc_impl_t<allcaps_t, template_interface<int, const std::string&>>>
      (std::move(concrete.get()));
    /*return std::make_unique<_tc_impl_t<allcaps_t, _tc_model_t<template_interface<int, const std::string&>>>(
      std::move(concrete.get()));*/
  }

  bool __has_save() const noexcept override final;

  void __save(const char* filename, const char* access) noexcept override final;

  /*template <typename ...Params>
  void print(Params&&... args) override final {
    return concrete.print(std::forward<decltype(args)>(args)...);
  }*/

  bool __has_print_2() const noexcept override final {
    return true;
  }
  void __print_2(const char* text) const noexcept override final {
    /// \note passes data, not ref
    return concrete.get().print_2(concrete.get(), std::forward<decltype(text)>(text));
  }

  bool __has_print() const noexcept override final;

  void __print(const char* text) const noexcept override final;

  void __set_data(const char* text) noexcept override final;

  void __print_data() const noexcept override final;

  void __draw(const char* surface) const noexcept override final;

  /*void set_interface_data(const char* text) {
    return set_interface_data(std::forward<decltype(text)>(text));
  }

  void print_interface_data() {
    return print_interface_data();
  }*/

  /*template <typename ...Params>
  void save(Params&&... args) override {
    throw std::runtime_error("allcaps_t::save not implemented");
  }*/

  // Loop over each member function on the interface.
  /*@meta for(int i = 0; i < @method_count(typeclass); ++i) {

    @meta std::string func_name = @method_name(typeclass, i);

    @meta bool is_valid = @sfinae(
      std::declval<type_t>().@(func_name)(
        std::declval<@method_params(typeclass, i)>()...
      )
    );

    // Implement the has_XXX function.
    bool @(format("has_%s", func_name.c_str()))() const override {
      return is_valid;
    }

    // Declare an override function with the same signature as the pure virtual
    // function in _tc_model_t.
    @func_decl(@method_type(typeclass, i), func_name, args) override {

      @meta if(is_valid || @sfinae(typeclass::required::@(__func__))) {
        // Forward to the correspondingly-named member function in type_t.
        return concrete.@(__func__)(std::forward<decltype(args)>(args)...);

      } else {

        // We could also call __cxa_pure_virtual or std::terminate here.
        throw std::runtime_error(@string(format("%s::%s not implemented",
          @type_name(type_t), __func__
        )));
      }
    }
  }*/

  allcaps_t* operator->() {
      return &concrete.get();
  }

  // Our actual data.
  std::reference_wrapper<allcaps_t> concrete;
};

template <>
forward_t& _tc_model_t<template_interface<int, const std::string&>>::ref_concrete<forward_t>() noexcept;

template<>
struct _tc_impl_t<forward_t, template_interface<int, const std::string&>>
  : public _tc_model_t<template_interface<int, const std::string&>> {
  typedef forward_t val_type_t;

  //static size_t constexpr type_hash = Hash("forward_t");

  // Construct the embedded concrete type.
  template<typename... args_t>
  _tc_impl_t(args_t&&... args) noexcept
    : concrete(std::forward<args_t>(args)...) { }

  explicit _tc_impl_t(const forward_t& concrete_arg) noexcept
    : concrete(concrete_arg) {}

  std::unique_ptr<
    _tc_model_t<template_interface<int, const std::string&>>>
      clone() noexcept override final {
    // Copy-construct a new instance of _tc_impl_t on the heap.
    return std::make_unique<_tc_impl_t>(concrete);
  }

  const size_t getModelTypeIndex() const noexcept override final {
    return _tc_registry<template_interface<int, const std::string&>>::
      getTypeIndex<forward_t>();
  }

  std::unique_ptr<
    _tc_model_t<template_interface<int, const std::string&>>>
      move_clone() noexcept override final {
    return std::make_unique<_tc_impl_t>(std::move(concrete));
  }

  bool __has_save() const noexcept override final {
    return true;
  }

  void __save(const char* filename, const char* access) noexcept override final {
    return concrete.save(concrete, std::forward<decltype(filename)>(filename),
      std::forward<decltype(access)>(access));
  }

  /*template <typename ...Params>
  void save(Params&&... args) override final {
    return concrete.save(std::forward<decltype(args)>(args)...);
  }*/

  bool __has_print_2() const noexcept override final {
    return true;
  }
  void __print_2(const char* text) const noexcept override final {
    return concrete.print_2(concrete, std::forward<decltype(text)>(text));
  }

  bool __has_print() const noexcept override final {
    return true;
  }

  void __print(const char* text) const noexcept override final {
    return concrete.print(concrete, std::forward<decltype(text)>(text));
  }

  void __set_data(const char* text) noexcept override final {
    return concrete.set_data(concrete, std::forward<decltype(text)>(text));
  }

  void __print_data() const noexcept override final {
    return concrete.print_data(concrete);
  }

  void __draw(const char* surface) const noexcept override final;

  /*void set_interface_data(const char* text) {
    return set_interface_data(std::forward<decltype(text)>(text));
  }

  void print_interface_data() {
    return print_interface_data();
  }*/

  /*template <typename ...Params>
  void print(Params&&... args) override {
    return concrete.print(std::forward<decltype(args)>(args)...);
  }*/

  // Loop over each member function on the interface.
  /*@meta for(int i = 0; i < @method_count(typeclass); ++i) {

    @meta std::string func_name = @method_name(typeclass, i);

    @meta bool is_valid = @sfinae(
      std::declval<type_t>().@(func_name)(
        std::declval<@method_params(typeclass, i)>()...
      )
    );

    // Implement the has_XXX function.
    bool @(format("has_%s", func_name.c_str()))() const override {
      return is_valid;
    }

    // Declare an override function with the same signature as the pure virtual
    // function in _tc_model_t.
    @func_decl(@method_type(typeclass, i), func_name, args) override {

      @meta if(is_valid || @sfinae(typeclass::required::@(__func__))) {
        // Forward to the correspondingly-named member function in type_t.
        return concrete.@(__func__)(std::forward<decltype(args)>(args)...);

      } else {

        // We could also call __cxa_pure_virtual or std::terminate here.
        throw std::runtime_error(@string(format("%s::%s not implemented",
          @type_name(type_t), __func__
        )));
      }
    }
  }*/

  forward_t* operator->() {
      return &concrete;
  }

  // Our actual data.
  forward_t concrete;
};

template <>
reverse_t& _tc_model_t<template_interface<int, const std::string&>>::ref_concrete<reverse_t>() noexcept;

template<>
struct _tc_impl_t<reverse_t, template_interface<int, const std::string&>>
    : public _tc_model_t<template_interface<int, const std::string&>> {
  typedef reverse_t val_type_t;

  //static size_t constexpr type_hash = Hash("reverse_t");

  // Construct the embedded concrete type.
  template<typename... args_t>
  _tc_impl_t(args_t&&... args) noexcept
    : concrete(std::forward<args_t>(args)...) { }

  explicit _tc_impl_t(const reverse_t& concrete_arg) noexcept
    : concrete(concrete_arg) {}

  const size_t getModelTypeIndex() const noexcept override final {
    return _tc_registry<template_interface<int, const std::string&>>::
      getTypeIndex<reverse_t>();
  }

  std::unique_ptr<
    _tc_model_t<template_interface<int, const std::string&>>>
      clone() noexcept override final {
    // Copy-construct a new instance of _tc_impl_t on the heap.
    return std::make_unique<_tc_impl_t>(std::move(concrete));
  }

  std::unique_ptr<
    _tc_model_t<template_interface<int, const std::string&>>>
      move_clone() noexcept override final {
    return std::make_unique<_tc_impl_t>(std::move(concrete));
  }

  bool __has_save() const noexcept override final {
    return false;
  }

  void __save(const char* filename, const char* access) noexcept override final {
    // TODO: noexcept
    //throw std::runtime_error("reverse_t::save not implemented");
    std::terminate();
  }

  /*template <typename ...Params>
  void save(Params&&... args) override {
    return concrete.save(std::forward<decltype(args)>(args)...);
  }*/

  bool __has_print_2() const noexcept override final {
    return true;
  }
  void __print_2(const char* text) const noexcept override final {
    return concrete.print_2(concrete, std::forward<decltype(text)>(text));
  }

  bool __has_print() const noexcept override final {
    return true;
  }

  void __print(const char* text) const noexcept override final {
    return concrete.print(concrete, std::forward<decltype(text)>(text));
  }

  void __set_data(const char* text) noexcept override final {
    return concrete.set_data(concrete, std::forward<decltype(text)>(text));
  }

  void __print_data() const noexcept override final {
    return concrete.print_data(concrete);
  }

  void __draw(const char* surface) const noexcept override final;

  /*void set_interface_data(const char* text) {
    return set_interface_data(std::forward<decltype(text)>(text));
  }

  void print_interface_data() {
    return print_interface_data();
  }*/

  /*template <typename ...Params>
  void print(Params&&... args) override {
    return concrete.print(std::forward<decltype(args)>(args)...);
  }*/

  // Loop over each member function on the interface.
  /*@meta for(int i = 0; i < @method_count(typeclass); ++i) {

    @meta std::string func_name = @method_name(typeclass, i);

    @meta bool is_valid = @sfinae(
      std::declval<type_t>().@(func_name)(
        std::declval<@method_params(typeclass, i)>()...
      )
    );

    // Implement the has_XXX function.
    bool @(format("has_%s", func_name.c_str()))() const override {
      return is_valid;
    }

    // Declare an override function with the same signature as the pure virtual
    // function in _tc_model_t.
    @func_decl(@method_type(typeclass, i), func_name, args) override {

      @meta if(is_valid || @sfinae(typeclass::required::@(__func__))) {
        // Forward to the correspondingly-named member function in type_t.
        return concrete.@(__func__)(std::forward<decltype(args)>(args)...);

      } else {

        // We could also call __cxa_pure_virtual or std::terminate here.
        throw std::runtime_error(@string(format("%s::%s not implemented",
          @type_name(type_t), __func__
        )));
      }
    }
  }*/

  reverse_t* operator->() {
      return &concrete;
  }

  // Our actual data.
  reverse_t concrete;
};

////////////////////////////////////////////////////////////////////////////////
#if 0
template<>
struct var_t<my_interface> {
  //typedef my_interface, my_interface2 typeclass_t;

  // Default initializer creates an empty var_t.
  var_t() = default;

  template <class T>
  var_t(std::unique_ptr<T>&& u) :
    model(std::move(u)) {
    puts("var_t{unique_ptr} called");
  }

  template <class T>
  var_t(const T&& u) :
      model(
        std::make_unique<
          _tc_impl_t<T, my_interface>>
        (std::forward<const std::decay_t<T>>(u))) {
    puts("var_t{T} called");
  }

  // Move ctor/assign by default.
  var_t(var_t&&) = default;
  var_t& operator=(var_t&&) = default;

  // Call clone for copy ctor/assign.
  var_t(const var_t& rhs) {
    if(rhs)
      model = rhs.model->clone();
  }

  var_t& operator=(const var_t& rhs) {
    model.reset();
    if(rhs)
      model = rhs.model->clone();
    return *this;
  }

  // A virtual dtor triggers the dtor in the impl.
  virtual ~var_t() { }

  // The preferred initializer for a var_t. This constructs an _tc_impl_t of
  // type_t on the heap, and stores the pointer in a new var_t.
  template<typename type_t, typename... args_t>
  static var_t construct(args_t&&... args) {
    return var_t(std::make_unique<_tc_impl_t<type_t, my_interface> >(
      std::forward<args_t>(args)...
    ));
  }

  bool has_save() const {
    return model->__has_save(); // force to true if required
  }

  template <typename ...Params>
  void save(Params&&... args) {
    return model->__save(std::forward<decltype(args)>(args)...);
  }

  bool has_print_2() const {
    return model->__has_print_2(); // force to true if required
  }
  template <typename ...Params>
  void print_2(Params&&... args) {
    return model->__print_2(std::forward<decltype(args)>(args)...);
  }

  bool has_print() const {
    return model->__has_print(); // force to true if required
  }

  template <typename ...Params>
  void print(Params&&... args) {
    return model->__print(std::forward<decltype(args)>(args)...);
  }

  template <typename ...Params>
  void set_data(Params&&... args) {
    return model->__set_data(std::forward<decltype(args)>(args)...);
  }

  template <typename ...Params>
  void print_data(Params&&... args) {
    return model->__print_data(std::forward<decltype(args)>(args)...);
  }

  template <typename ...Params>
  void set_interface_data(Params&&... args) {
    return model->set_interface_data(std::forward<decltype(args)>(args)...);
  }

  template <typename ...Params>
  void print_interface_data(Params&&... args) {
    return model->print_interface_data(std::forward<decltype(args)>(args)...);
  }

  /*void print(const char* text) {
    return model->print(std::forward<decltype(text)>(text));
  }*/

  /*friend void draw(const var_t<my_interface>& d) {
    d.model->do_draw();
  }*/

  void draw(const char* surface) {
    model->__draw(surface);
  }

  /*// Loop over each member function on the interface.
  @meta for(int i = 0; i < @method_count(my_interface); ++i) {

    // Define a has_XXX member function.
    bool @(format("has_%s", @method_name(my_interface, i)))() const {
      @meta if(@sfinae(my_interface::required::@(@method_name(my_interface, i))))
        return true;
      else
        return model->@(__func__)();
    }

    // Declare a non-virtual forwarding function for each interface method.
    @func_decl(@method_type(my_interface, i), @method_name(my_interface, i), args) {
      // Forward to the model's virtual function.
      return model->@(__func__)(std::forward<decltype(args)>(args)...);
    }
  }*/

  explicit operator bool() const {
    return (bool)model;
  }

  /*bool is_valid() const {
    return (bool)model;
  }*/

  // TODO: https://stackoverflow.com/a/38367549
  /*void f1(int) {  }

  std::map<std::string, void( var_t<my_interface>::* )(int)>
    funcs_to_names = {
      { "draw", &var_t<my_interface>::f1 }, };*/

  // This is actually a unique_ptr to an impl type. We store a pointer to
  // the base type and rely on _tc_model_t's virtual dtor to free the object.
  std::unique_ptr<_tc_model_t<my_interface>> model;
};
#endif // 0

template<>
struct _tc_combined_t<template_interface<int, const std::string&>> {
  //typedef my_interface typeclass_t;

  // Default initializer creates an empty _tc_combined_t.
  _tc_combined_t() = default;

  _tc_combined_t(std::reference_wrapper<_tc_combined_t<template_interface<int, const std::string&>>>&& rhs) noexcept {
    puts("_tc_combined_t{my_interface} ref copy ctor");
    if(rhs.get())
      my_interface_model = rhs.get().my_interface_model;
  }

  /// \note moves passed argument
  template <
  class T,
  typename = IsNotReference<T>,
  typename std::enable_if<!std::is_same<_tc_combined_t, T>::value>::type* = nullptr
  >
  _tc_combined_t(std::shared_ptr<T>&& u) noexcept :
      my_interface_model(std::move(u)) {
   static_assert(!std::is_const<typename std::remove_reference<T>::type>::value,
      "You've attempted a cast to a const rvalue reference. "
      "Make sure you're not trying to move a const object, "
      "as this would likely result in a copy not a move. "
      "If you need it for real, call std::move(...) instead.");
    puts("_tc_combined_t{my_interface} called, moves passed argument");
  }

  template <
  class T,
  typename = IsNotReference<T>,
  typename std::enable_if<!std::is_same<_tc_combined_t, T>::value>::type* = nullptr
  >
  _tc_combined_t(const std::shared_ptr<T>& u) noexcept :
      my_interface_model(u) {
    puts("_tc_combined_t{my_interface} called, shares passed argument");
  }

  template <
  class T,
  typename std::enable_if<!std::is_same<_tc_combined_t, T>::value>::type* = nullptr
  >
  _tc_combined_t(const std::reference_wrapper<T>& u) noexcept :
      my_interface_model(
        std::make_shared<
          _tc_impl_t<std::reference_wrapper<T>, template_interface<int, const std::string&>>>
        (std::forward<const std::reference_wrapper<std::decay_t<T>>>(u))) {
    puts("_tc_combined_t{T} reference_wrapper called");
  }

  template<
  typename T,
  typename = IsNotReference<T>,
  typename std::enable_if<!std::is_same<_tc_combined_t, T>::value>::type* = nullptr
  >
  _tc_combined_t(const T&& u) noexcept :
      my_interface_model(
        std::make_shared<
          _tc_impl_t<T, template_interface<int, const std::string&>>>
        (std::forward<const std::decay_t<T>>(u))) {
    puts("_tc_combined_t{T} called");
  }

  // Call clone for copy ctor/assign.
  explicit _tc_combined_t(const _tc_combined_t& rhs) noexcept {
    puts("_tc_combined_t{my_interface} copy ctor");
    if(rhs)
      my_interface_model = rhs.my_interface_model->clone();
  }

  // Move ctor/assign by default.
  /*_tc_combined_t(_tc_combined_t&&) = default;
  _tc_combined_t& operator=(_tc_combined_t&&) = default;*/

  // Call move_clone for move ctor/assign.
  explicit _tc_combined_t(_tc_combined_t&& rhs) noexcept {
    if(rhs)
      my_interface_model = rhs.my_interface_model->move_clone();
  }

  // The preferred initializer for a _tc_combined_t. This constructs an _tc_impl_t of
  // type_t on the heap, and stores the pointer in a new _tc_combined_t.
  template<
    typename type_t,
    typename... args_t,
    typename = IsNotReference<type_t>
  >
  static _tc_combined_t construct(args_t&&... args) noexcept {
    return _tc_combined_t(std::make_shared<_tc_impl_t<type_t, template_interface<int, const std::string&>> >(
      std::forward<args_t>(args)...
    ));
  }

  _tc_combined_t& operator=(_tc_combined_t&& rhs) noexcept {
    my_interface_model.reset();
    if(rhs)
      my_interface_model = rhs.my_interface_model->move_clone();
    return *this;
  }

  _tc_combined_t& operator=(const _tc_combined_t& rhs) noexcept {
    my_interface_model.reset();
    if(rhs)
      my_interface_model = rhs.my_interface_model->clone();
    return *this;
  }

  void reset() noexcept {
    my_interface_model.reset();
  }

  // A virtual dtor triggers the dtor in the impl.
  virtual ~_tc_combined_t() noexcept { }

  bool has_save() const noexcept {
    if(!my_interface_model) {
      //throw std::runtime_error("my_interface_model not set");
      std::terminate();
    }
    return my_interface_model->__has_save(); // force to true if required
  }

  template <typename ...Params>
  void save(Params&&... args) noexcept {
    if(!my_interface_model) {
      //throw std::runtime_error("my_interface_model not set");
      std::terminate();
    }
    return my_interface_model->__save(std::forward<decltype(args)>(args)...);
  }

  bool has_print_2() const noexcept {
    if(!my_interface_model) {
      //throw std::runtime_error("my_interface_model not set");
      std::terminate();
    }
    return my_interface_model->__has_print_2(); // force to true if required
  }
  template <typename ...Params>
  void print_2(Params&&... args) const noexcept {
    if(!my_interface_model) {
      //throw std::runtime_error("my_interface_model not set");
      std::terminate();
    }
    return my_interface_model->__print_2(std::forward<decltype(args)>(args)...);
  }

  bool has_print() const noexcept {
    if(!my_interface_model) {
      //throw std::runtime_error("my_interface_model not set");
      std::terminate();
    }
    return my_interface_model->__has_print(); // force to true if required
  }

  template <typename ...Params>
  void print(Params&&... args) const noexcept {
    if(!my_interface_model) {
      //throw std::runtime_error("my_interface_model not set");
      std::terminate();
    }
    return my_interface_model->__print(std::forward<decltype(args)>(args)...);
  }

  template <typename ...Params>
  void set_data(Params&&... args) noexcept {
    if(!my_interface_model) {
      //throw std::runtime_error("my_interface_model not set");
      std::terminate();
    }
    return my_interface_model->__set_data(std::forward<decltype(args)>(args)...);
  }

  template <typename ...Params>
  void print_data(Params&&... args) const noexcept {
    if(!my_interface_model) {
      //throw std::runtime_error("my_interface_model not set");
      std::terminate();
    }
    return my_interface_model->__print_data(std::forward<decltype(args)>(args)...);
  }

  // from template S drawTo(A);
  /*int drawTo(const std::string& str) {
    return my_interface_model->drawTo(str);
  }*/

  template <typename ...Params>
  void set_interface_data(Params&&... args) noexcept {
    if(!my_interface_model) {
      //throw std::runtime_error("my_interface_model not set");
      std::terminate();
    }
    return my_interface_model->set_interface_data(std::forward<decltype(args)>(args)...);
  }

  template <typename ...Params>
  void print_interface_data(Params&&... args) const noexcept {
    if(!my_interface_model) {
      //throw std::runtime_error("my_interface_model not set");
      std::terminate();
    }
    return my_interface_model->print_interface_data(std::forward<decltype(args)>(args)...);
  }

  /*void print(const char* text) {
    return model->print(std::forward<decltype(text)>(text));
  }*/

  /*friend void draw(const var_t<my_interface>& d) {
    d.model->do_draw();
  }*/

  void draw(const char* surface) noexcept {
    if(!my_interface_model) {
      //throw std::runtime_error("my_interface_model not set");
      std::terminate();
    }
    my_interface_model->__draw(surface);
  }

  /*// Loop over each member function on the interface.
  @meta for(int i = 0; i < @method_count(my_interface); ++i) {

    // Define a has_XXX member function.
    bool @(format("has_%s", @method_name(my_interface, i)))() const {
      @meta if(@sfinae(my_interface::required::@(@method_name(my_interface, i))))
        return true;
      else
        return model->@(__func__)();
    }

    // Declare a non-virtual forwarding function for each interface method.
    @func_decl(@method_type(my_interface, i), @method_name(my_interface, i), args) {
      // Forward to the model's virtual function.
      return model->@(__func__)(std::forward<decltype(args)>(args)...);
    }
  }*/

  explicit operator bool() const noexcept {
    return (bool)my_interface_model;
  }

  std::shared_ptr<_tc_model_t<template_interface<int, const std::string&>>> ref_model() const noexcept {
    return my_interface_model;
  }

  /*template<typename T>
  std::shared_ptr<_tc_model_t<T>> ref_model() const noexcept {
    return nullptr;
  }*/

  std::unique_ptr<_tc_model_t<template_interface<int, const std::string&>>> clone_model() const noexcept {
    if(!my_interface_model) {
      //throw std::runtime_error("my_interface_model not set");
      std::terminate();
    }
    return my_interface_model->clone();
  }

  const _tc_model_t<template_interface<int, const std::string&>>* raw_model() const noexcept {
    return my_interface_model.get();
  }

  void replace_model(
    const std::shared_ptr<_tc_model_t<template_interface<int, const std::string&>>> rhs) noexcept {
    my_interface_model = rhs;
  }

  const size_t getModelTypeIndex() {
    if(!my_interface_model) {
      std::terminate();
    }
    return my_interface_model->getModelTypeIndex();
  }

  template <typename T>
  static const size_t getGlobalTypeIndex() {
    return _tc_registry<template_interface<int, const std::string&>>
      ::getTypeIndex<T>();
  }

  template <typename T>
  T& ref_concrete() noexcept {
    if(!my_interface_model || my_interface_model->getModelTypeIndex()
        != getGlobalTypeIndex<T>()) {
      std::terminate();
    }
    return my_interface_model->ref_concrete<T>();
  }

  template <typename U>
  bool can_convert() const
  {
    return false;
  }

  /*template<
  typename B,
  typename C>
  static std::string external(const B& arg1, C const & arg2) noexcept;*/

  /*bool is_valid() const {
    return (bool)model;
  }*/

  // TODO: https://stackoverflow.com/a/38367549
  /*void f1(int) {  }

  std::map<std::string, void( var_t<my_interface>::* )(int)>
    funcs_to_names = {
      { "draw", &var_t<my_interface>::f1 }, };*/

  // This is actually a unique_ptr to an impl type. We store a pointer to
  // the base type and rely on _tc_model_t's virtual dtor to free the object.
  private:
    std::shared_ptr<_tc_model_t<template_interface<int, const std::string&>>> my_interface_model;
};

/*template <>
allcaps_t& _tc_combined_t<my_interface>::ref_concrete<allcaps_t>() {
  return static_cast<_tc_impl_t<allcaps_t, my_interface>*>(my_interface_model.get())
    ->concrete;
}
template <>
reverse_t& _tc_combined_t<my_interface>::ref_concrete<reverse_t>() {
  return static_cast<_tc_impl_t<reverse_t, my_interface>*>(my_interface_model.get())
    ->concrete;
}
template <>
forward_t& _tc_combined_t<my_interface>::ref_concrete<forward_t>() {
  return static_cast<_tc_impl_t<forward_t, my_interface>*>(my_interface_model.get())
    ->concrete;
}*/

#if 0
// ================
template <>
allcaps_t& _tc_model_t<my_interface>::ref_concrete<allcaps_t>() {
  return static_cast<_tc_impl_t<allcaps_t, my_interface>*>(this)
    ->concrete;
}
template <>
reverse_t& _tc_model_t<my_interface>::ref_concrete<reverse_t>() {
  return static_cast<_tc_impl_t<reverse_t, my_interface>*>(this)
    ->concrete;
}
template <>
forward_t& _tc_model_t<my_interface>::ref_concrete<forward_t>() {
  return static_cast<_tc_impl_t<forward_t, my_interface>*>(this)
    ->concrete;
}
#endif // 0

/*template<typename T> int freeGet() = delete;

extern template
 int freeGet<int>();*/

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

////////////////////////////////////////////////////////////////////////////////

template <>
bool _tc_combined_t<template_interface<int, const std::string&>>::
  can_convert<template_interface<int, const std::string&>>() const;

///////////////////////////////////////////////////////////////////////////////

template <>
_tc_impl_t<std::reference_wrapper<allcaps_t>, template_interface<int, const std::string&>>*
  _tc_model_t<template_interface<int, const std::string&>>::
    as<std::reference_wrapper<allcaps_t>>() noexcept;

template <>
_tc_impl_t<allcaps_t, template_interface<int, const std::string&>>*
  _tc_model_t<template_interface<int, const std::string&>>
    ::as<allcaps_t>() noexcept;

template <>
_tc_impl_t<reverse_t, template_interface<int, const std::string&>>*
  _tc_model_t<template_interface<int, const std::string&>>
    ::as<reverse_t>() noexcept;

template <>
_tc_impl_t<forward_t, template_interface<int, const std::string&>>*
  _tc_model_t<template_interface<int, const std::string&>>
    ::as<forward_t>() noexcept;

///////////////////////////////////////////////////////////////////////////////

/*template <>
std::shared_ptr<_tc_model_t<template_interface<int, const std::string&>>>
  _tc_combined_t<template_interface<int, const std::string&>>
    ::ref_model<template_interface<int, const std::string&>>() const noexcept;*/

} // namespace cxxctp
} // namespace generated
