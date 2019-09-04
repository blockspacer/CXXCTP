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

/*struct common__tc_model_t {
  virtual ~common__tc_model_t() { }
};*/

template<>
struct _tc_model_t<template_interface<int, const std::string&>> {
  virtual ~_tc_model_t() { }

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

  virtual std::unique_ptr<_tc_model_t> clone() = 0;
  virtual std::unique_ptr<_tc_model_t> move_clone() = 0;

  virtual bool __has_save() const = 0;

  //template <typename ...Params>
  //virtual void save(Params&&... args) = 0;
  //virtual void __save(const char* filename, const char* access) = 0;
  virtual void __save(const char* filename, const char* access) {
    printf("default (unimplemented) save called for %s %s\n", filename, access);
  }

  virtual bool __has_print_2() const = 0;
  virtual void __print_2(const char* text) const = 0;

  virtual bool __has_print() const = 0;

  //template <typename ...Params>
  //virtual void print(Params&&... args) = 0;
  virtual void __print(const char* text) const = 0;

  virtual void __set_data(const char* text) = 0;

  virtual void __print_data() const = 0;

  virtual void __draw(const char* surface) const = 0;

  template <typename T>
  T& ref_concrete();

  // TODO: pseudo inheritance by code injection
  /// \note same for all types
  void set_interface_data(const char* text);/* {
    interface_data = text;
  }*/

  /// \note same for all types
  void print_interface_data() const;/* {
    auto out = std::string("interface_data: ") + interface_data;
    puts(out.c_str());
  }*/
  /// \note same for all types
  std::string interface_data = "interface_data";

  // TODO: https://stackoverflow.com/a/26159287
  //template<typename... Args>
  //std::map<std::string, void(*)()> runtime_dispatch_table_;
};

template <>
allcaps_t& _tc_model_t<template_interface<int, const std::string&>>::ref_concrete<allcaps_t>();

template<>
struct _tc_impl_t<allcaps_t, template_interface<int, const std::string&>>
    : public _tc_model_t<template_interface<int, const std::string&>> {
  typedef allcaps_t val_type_t;
  //friend void draw(const allcaps_t&);

  // Construct the embedded concrete type.
  template<typename... args_t>
  _tc_impl_t(args_t&&... args) : concrete(std::forward<args_t>(args)...) { }

  explicit _tc_impl_t(const allcaps_t& concrete_arg);

  std::unique_ptr<
    _tc_model_t<template_interface<int, const std::string&>>>
      clone() override;

  std::unique_ptr<
    _tc_model_t<template_interface<int, const std::string&>>>
      move_clone() override {
    return std::make_unique<_tc_impl_t>(std::move(concrete));
  }

  bool __has_save() const override;

  void __save(const char* filename, const char* access) override;

  /*template <typename ...Params>
  void print(Params&&... args) override {
    return concrete.print(std::forward<decltype(args)>(args)...);
  }*/

  bool __has_print_2() const override {
    return true;
  }
  void __print_2(const char* text) const override {
    return concrete.print_2(std::forward<decltype(text)>(text));
  }

  bool __has_print() const override;

  void __print(const char* text) const override;

  void __set_data(const char* text) override;

  void __print_data() const override;

  void __draw(const char* surface) const override;

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

  // Our actual data.
  allcaps_t concrete;
};

template <>
forward_t& _tc_model_t<template_interface<int, const std::string&>>::ref_concrete<forward_t>();

template<>
struct _tc_impl_t<forward_t, template_interface<int, const std::string&>>
  : public _tc_model_t<template_interface<int, const std::string&>> {
  typedef forward_t val_type_t;

  // Construct the embedded concrete type.
  template<typename... args_t>
  _tc_impl_t(args_t&&... args)
    : concrete(std::forward<args_t>(args)...) { }

  explicit _tc_impl_t(const forward_t& concrete_arg)
    : concrete(concrete_arg) {}

  std::unique_ptr<
    _tc_model_t<template_interface<int, const std::string&>>>
      clone() override {
    // Copy-construct a new instance of _tc_impl_t on the heap.
    return std::make_unique<_tc_impl_t>(concrete);
  }

  std::unique_ptr<
    _tc_model_t<template_interface<int, const std::string&>>>
      move_clone() override {
    return std::make_unique<_tc_impl_t>(std::move(concrete));
  }

  bool __has_save() const override {
    return true;
  }

  void __save(const char* filename, const char* access) override {
    return concrete.save(std::forward<decltype(filename)>(filename),
      std::forward<decltype(access)>(access));
  }

  /*template <typename ...Params>
  void save(Params&&... args) override {
    return concrete.save(std::forward<decltype(args)>(args)...);
  }*/

  bool __has_print_2() const override {
    return true;
  }
  void __print_2(const char* text) const override {
    return concrete.print_2(std::forward<decltype(text)>(text));
  }

  bool __has_print() const override {
    return true;
  }

  void __print(const char* text) const override {
    return concrete.print(std::forward<decltype(text)>(text));
  }

  void __set_data(const char* text) override {
    return concrete.set_data(std::forward<decltype(text)>(text));
  }

  void __print_data() const override {
    return concrete.print_data();
  }

  void __draw(const char* surface) const override;

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

  // Our actual data.
  forward_t concrete;
};

template <>
reverse_t& _tc_model_t<template_interface<int, const std::string&>>::ref_concrete<reverse_t>();

template<>
struct _tc_impl_t<reverse_t, template_interface<int, const std::string&>>
    : public _tc_model_t<template_interface<int, const std::string&>> {
  typedef reverse_t val_type_t;

  // Construct the embedded concrete type.
  template<typename... args_t>
  _tc_impl_t(args_t&&... args)
    : concrete(std::forward<args_t>(args)...) { }

  explicit _tc_impl_t(const reverse_t& concrete_arg)
    : concrete(concrete_arg) {}

  std::unique_ptr<
    _tc_model_t<template_interface<int, const std::string&>>>
      clone() override {
    // Copy-construct a new instance of _tc_impl_t on the heap.
    return std::make_unique<_tc_impl_t>(std::move(concrete));
  }

  std::unique_ptr<
    _tc_model_t<template_interface<int, const std::string&>>>
      move_clone() override {
    return std::make_unique<_tc_impl_t>(std::move(concrete));
  }

  bool __has_save() const override {
    return false;
  }

  void __save(const char* filename, const char* access) override {
    // TODO: noexcept
    throw std::runtime_error("reverse_t::save not implemented");
  }

  /*template <typename ...Params>
  void save(Params&&... args) override {
    return concrete.save(std::forward<decltype(args)>(args)...);
  }*/

  bool __has_print_2() const override {
    return true;
  }
  void __print_2(const char* text) const override {
    return concrete.print_2(std::forward<decltype(text)>(text));
  }

  bool __has_print() const override {
    return true;
  }

  void __print(const char* text) const override {
    return concrete.print(std::forward<decltype(text)>(text));
  }

  void __set_data(const char* text) override {
    return concrete.set_data(std::forward<decltype(text)>(text));
  }

  void __print_data() const override {
    return concrete.print_data();
  }

  void __draw(const char* surface) const override;

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
  //typedef my_interface, my_interface2 typeclass_t;

  // Default initializer creates an empty _tc_combined_t.
  _tc_combined_t() = default;

  /// \note moves passed argument
  template <class T>
  _tc_combined_t(std::shared_ptr<T>&& u) :
    my_interface_model(std::move(u)) {
    puts("_tc_combined_t{my_interface} called, moves passed argument");
  }

  template <class T>
  _tc_combined_t(const T&& u) :
      my_interface_model(
        std::make_shared<
          _tc_impl_t<T, template_interface<int, const std::string&>>>
        (std::forward<const std::decay_t<T>>(u))) {
    puts("_tc_combined_t{T} called");
  }

  // Move ctor/assign by default.
  /*_tc_combined_t(_tc_combined_t&&) = default;
  _tc_combined_t& operator=(_tc_combined_t&&) = default;*/

  // Call move_clone for move ctor/assign.
  _tc_combined_t(_tc_combined_t&& rhs) {
    if(rhs)
      my_interface_model = rhs.my_interface_model->move_clone();
  }

  _tc_combined_t& operator=(_tc_combined_t&& rhs) {
    my_interface_model.reset();
    if(rhs)
      my_interface_model = rhs.my_interface_model->move_clone();
    return *this;
  }

  // Call clone for copy ctor/assign.
  _tc_combined_t(const _tc_combined_t& rhs) {
    if(rhs)
      my_interface_model = rhs.my_interface_model->clone();
  }

  _tc_combined_t& operator=(const _tc_combined_t& rhs) {
    my_interface_model.reset();
    if(rhs)
      my_interface_model = rhs.my_interface_model->clone();
    return *this;
  }

  void reset() {
    my_interface_model.reset();
  }

  // A virtual dtor triggers the dtor in the impl.
  virtual ~_tc_combined_t() { }

  // The preferred initializer for a _tc_combined_t. This constructs an _tc_impl_t of
  // type_t on the heap, and stores the pointer in a new _tc_combined_t.
  template<typename type_t, typename... args_t>
  static _tc_combined_t construct(args_t&&... args) {
    return _tc_combined_t(std::make_shared<_tc_impl_t<type_t, template_interface<int, const std::string&>> >(
      std::forward<args_t>(args)...
    ));
  }

  bool has_save() const {
    if(!my_interface_model) {
      throw std::runtime_error("my_interface_model not set");
    }
    return my_interface_model->__has_save(); // force to true if required
  }

  template <typename ...Params>
  void save(Params&&... args) {
    if(!my_interface_model) {
      throw std::runtime_error("my_interface_model not set");
    }
    return my_interface_model->__save(std::forward<decltype(args)>(args)...);
  }

  bool has_print_2() const {
    if(!my_interface_model) {
      throw std::runtime_error("my_interface_model not set");
    }
    return my_interface_model->__has_print_2(); // force to true if required
  }
  template <typename ...Params>
  void print_2(Params&&... args) const {
    if(!my_interface_model) {
      throw std::runtime_error("my_interface_model not set");
    }
    return my_interface_model->__print_2(std::forward<decltype(args)>(args)...);
  }

  bool has_print() const {
    if(!my_interface_model) {
      throw std::runtime_error("my_interface_model not set");
    }
    return my_interface_model->__has_print(); // force to true if required
  }

  template <typename ...Params>
  void print(Params&&... args) const {
    if(!my_interface_model) {
      throw std::runtime_error("my_interface_model not set");
    }
    return my_interface_model->__print(std::forward<decltype(args)>(args)...);
  }

  template <typename ...Params>
  void set_data(Params&&... args) {
    if(!my_interface_model) {
      throw std::runtime_error("my_interface_model not set");
    }
    return my_interface_model->__set_data(std::forward<decltype(args)>(args)...);
  }

  template <typename ...Params>
  void print_data(Params&&... args) const {
    if(!my_interface_model) {
      throw std::runtime_error("my_interface_model not set");
    }
    return my_interface_model->__print_data(std::forward<decltype(args)>(args)...);
  }

  // from template S drawTo(A);
  /*int drawTo(const std::string& str) {
    return my_interface_model->drawTo(str);
  }*/

  template <typename ...Params>
  void set_interface_data(Params&&... args) {
    if(!my_interface_model) {
      throw std::runtime_error("my_interface_model not set");
    }
    return my_interface_model->set_interface_data(std::forward<decltype(args)>(args)...);
  }

  template <typename ...Params>
  void print_interface_data(Params&&... args) const {
    if(!my_interface_model) {
      throw std::runtime_error("my_interface_model not set");
    }
    return my_interface_model->print_interface_data(std::forward<decltype(args)>(args)...);
  }

  /*void print(const char* text) {
    return model->print(std::forward<decltype(text)>(text));
  }*/

  /*friend void draw(const var_t<my_interface>& d) {
    d.model->do_draw();
  }*/

  void draw(const char* surface) {
    if(!my_interface_model) {
      throw std::runtime_error("my_interface_model not set");
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

  explicit operator bool() const {
    return (bool)my_interface_model;
  }

  std::shared_ptr<_tc_model_t<template_interface<int, const std::string&>>> ref_my_interface_model() const {
    return my_interface_model;
  }

  std::unique_ptr<_tc_model_t<template_interface<int, const std::string&>>> clone_my_interface_model() const {
    if(!my_interface_model) {
      throw std::runtime_error("my_interface_model not set");
    }
    return my_interface_model->clone();
  }

  const _tc_model_t<template_interface<int, const std::string&>>* raw_my_interface_model() const {
    return my_interface_model.get();
  }

  void replace_my_interface_model(
    const std::shared_ptr<_tc_model_t<template_interface<int, const std::string&>>> rhs) {
    my_interface_model = rhs;
  }

  template <typename T>
  T& ref_concrete() {
    return my_interface_model->ref_concrete<T>();
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

} // namespace cxxctp
} // namespace generated
