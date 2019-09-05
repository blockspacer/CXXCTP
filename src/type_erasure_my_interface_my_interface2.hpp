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

namespace cxxctp {
namespace generated {

template<>
struct _tc_combined_t<template_interface<int, const std::string&>, my_interface2> {
  //typedef my_interface, my_interface2 typeclass_t;

  // Default initializer creates an empty _tc_combined_t.
  _tc_combined_t() = default;

  /// \note moves passed argument
  /*template <class T>
  _tc_combined_t(std::shared_ptr<_tc_model_t<my_interface>>&& u) :
    my_interface_model(std::move(u)) {
    puts("_tc_combined_t{my_interface, my_interface2}(my_interface2) "
         "called, moves passed argument");
  }

  /// \note moves passed argument
  template <class T>
  _tc_combined_t(std::shared_ptr<_tc_model_t<my_interface2>>&& u) :
    my_interface2_model(std::move(u)) {
    puts("_tc_combined_t{my_interface, my_interface2}(my_interface2) "
         "called, moves passed argument");
  }*/

#if 0
  template <class T>
  _tc_combined_t(std::shared_ptr<T>&& u) :
    my_interface2_model(/*std::move*/(u)) {
    puts("_tc_combined_t{unique_ptr} called");
  }
#endif // 0

  _tc_combined_t(std::reference_wrapper<_tc_combined_t<my_interface2>>&& rhs) noexcept {
    puts("_tc_combined_t{my_interface2} ref copy ctor");
    if(rhs.get())
      my_interface2_model = rhs.get().my_interface2_model;
  }

  _tc_combined_t(std::reference_wrapper<_tc_combined_t<template_interface<int, const std::string&>>>&& rhs) noexcept {
    puts("_tc_combined_t{my_interface_mode} ref copy ctor");
    if(rhs.get())
      my_interface_model = rhs.get().my_interface_model;
  }

  template <
  class T,
  typename std::enable_if<!std::is_same<_tc_combined_t, T>::value>::type* = nullptr
  >
  _tc_combined_t(const std::reference_wrapper<T>& u) noexcept :
      my_interface2_model(
        std::make_shared<
          _tc_impl_t<std::reference_wrapper<T>, my_interface2>>
        (std::forward<const std::reference_wrapper<std::decay_t<T>>>(u))),
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
      my_interface2_model(
        std::make_shared<
          _tc_impl_t<T, my_interface2>>
        (std::forward<const std::decay_t<T>>(u))),
      my_interface_model(
        std::make_shared<
          _tc_impl_t<T, template_interface<int, const std::string&>>>
        (std::forward<const std::decay_t<T>>(u))) {
    puts("_tc_combined_t{T} called");
  }

  // Call clone for copy ctor/assign.
  explicit _tc_combined_t(const _tc_combined_t& rhs) noexcept {
    if(rhs) {
      my_interface_model = rhs.my_interface_model->clone();
      my_interface2_model = rhs.my_interface2_model->clone();
    }
  }

  // Call move_clone for move ctor/assign.
  explicit _tc_combined_t(_tc_combined_t&& rhs) noexcept {
    if(rhs) {
      my_interface_model = rhs.my_interface_model->move_clone();
      my_interface2_model = rhs.my_interface2_model->move_clone();
    }
  }

  /*template <class T>
  _tc_combined_t(std::unique_ptr<T>&& u) :
    my_interface2_model(std::move(u)) {
    puts("_tc_combined_t{unique_ptr} called");
  }

  template <class T>
  _tc_combined_t(const T&& u) :
      my_interface2_model(
        std::make_unique<
          _tc_impl_t<T, my_interface2>>
        (std::forward<const std::decay_t<T>>(u))) {
    puts("_tc_combined_t{T} called");
  }*/

  // Move ctor/assign by default.
  /*_tc_combined_t(_tc_combined_t&&) = default;
  _tc_combined_t& operator=(_tc_combined_t&&) = default;*/

  _tc_combined_t& operator=(_tc_combined_t&& rhs) noexcept {
    my_interface_model.reset();
    my_interface2_model.reset();
    if(rhs) {
      my_interface_model = rhs.my_interface_model->move_clone();
      my_interface2_model = rhs.my_interface2_model->move_clone();
    }
    return *this;
  }

  _tc_combined_t& operator=(const _tc_combined_t& rhs) noexcept {
    my_interface_model.reset();
    my_interface2_model.reset();
    if(rhs) {
      my_interface_model = rhs.my_interface_model->clone();
      my_interface2_model = rhs.my_interface2_model->clone();
    }
    return *this;
  }

  _tc_combined_t& operator=(const _tc_combined_t<template_interface<int, const std::string&>>& rhs) noexcept {
    my_interface_model.reset();
    if(rhs) {
      my_interface_model = rhs.my_interface_model->clone();
    }
    return *this;
  }

  _tc_combined_t& operator=(const _tc_combined_t<my_interface2>& rhs) noexcept {
    my_interface2_model.reset();
    if(rhs) {
      my_interface2_model = rhs.my_interface2_model->clone();
    }
    return *this;
  }

  // A virtual dtor triggers the dtor in the impl.
  virtual ~_tc_combined_t() noexcept { }

  // The preferred initializer for a _tc_combined_t. This constructs an _tc_impl_t of
  // type_t on the heap, and stores the pointer in a new _tc_combined_t.
  /*template<typename T, typename type_t, typename... args_t>
  static _tc_combined_t construct(args_t&&... args) {
    return _tc_combined_t(std::make_unique<_tc_impl_t<type_t, T> >(
      std::forward<args_t>(args)...
    ));
  }*/

  /*template<typename type_t, typename... args_t>
  static _tc_combined_t set_my_interface_model(args_t&&... args) {
    my_interface_model = (std::make_unique<_tc_impl_t<type_t, my_interface_model> >(
      std::forward<args_t>(args)...
    ));
  }*/

  /*template <class T>
  void set_my_interface2_model(std::unique_ptr<_tc_impl_t<T, my_interface2>>&& u) :
    my_interface2_model(std::move(u)) {
    puts("_tc_combined_t{unique_ptr} called");
  }*/

  void reset() noexcept {
    my_interface_model.reset();
    my_interface2_model.reset();
  }

  bool has_do_job() const noexcept {
    if(!my_interface2_model) {
      //throw std::runtime_error("my_interface_model2 not set");
      return false;
    }
    return my_interface2_model->__has_do_job(); // force to true if required
  }

  template <typename ...Params>
  void do_job(Params&&... args) noexcept {
    if(!my_interface2_model) {
      //throw std::runtime_error("my_interface_model2 not set");
      std::terminate();
    }
    return my_interface2_model->__do_job(std::forward<decltype(args)>(args)...);
  }

  template <typename ...Params>
  std::string get_bar(Params&&... args) noexcept {
    if(!my_interface2_model) {
      //throw std::runtime_error("my_interface_model2 not set");
      std::terminate();
    }
    return my_interface2_model->__get_bar(std::forward<decltype(args)>(args)...);
  }

  /*template <typename ...Params>
  void set_get_bar(Params&&... args) {
    if(!my_interface2_model) {
      throw std::runtime_error("my_interface_model2 not set");
    }
    return my_interface2_model->__set_get_bar(std::forward<decltype(args)>(args)...);
  }*/

  template <typename T>
  void set_get_bar(std::function<std::string(T&)> arg) noexcept;

  template <typename ...Params>
  void set_bar(Params&&... args) noexcept {
    if(!my_interface2_model) {
      //throw std::runtime_error("my_interface_model2 not set");
      std::terminate();
    }
    return my_interface2_model->__set_bar(std::forward<decltype(args)>(args)...);
  }

  /*template <typename ...Params>
  void set_set_bar(Params&&... args) {
    if(!my_interface2_model) {
      throw std::runtime_error("my_interface_model2 not set");
    }
    return my_interface2_model->__set_set_bar(std::forward<decltype(args)>(args)...);
  }*/

  template <typename T>
  void set_set_bar(std::function<void(T&, const std::string&)> arg) noexcept;

  template <typename T, typename C>
  T& ref_concrete() noexcept;

  template <typename ...Params>
  std::string test_zoo(Params&&... args) noexcept {
    return my_interface2_model->__test_zoo(std::forward<decltype(args)>(args)...);
  }

  template<
  typename T,
  typename C,
  typename std::enable_if<std::is_same<my_interface2, T>::value>::type* = nullptr
  >
  T& ref_concrete() noexcept {
    if(!my_interface2_model) {
      //throw std::runtime_error("my_interface_model2 not set");
      std::terminate();
    }
    return my_interface2_model->ref_concrete<C>();
  }

  template<
  typename T,
  typename C,
  typename std::enable_if<std::is_same<template_interface<int, const std::string&>, T>::value>::type* = nullptr
  >
  T& ref_concrete() noexcept {
    if(!my_interface_model) {
      //throw std::runtime_error("my_interface_model2 not set");
      std::terminate();
    }
    return my_interface_model->ref_concrete<C>();
  }

  bool has_save() const noexcept {
    if(!my_interface_model) {
      //throw std::runtime_error("my_interface_model not set");
      return false;
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
      return false;
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
      return false;
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

#if 0
  bool has_func_by_name(const char& func_name) {
    return false; // TODO: func by name
  }

  bool call_func_by_name(const char& func_name) {
    return false; // TODO: func by name
  }

  bool runtime_add_func_by_name() {
    return false; // TODO
  }

  template<
  typename T,
  typename std::enable_if<std::is_same<my_interface2, T>::value>::type* = nullptr
  >
  bool is_func_inherited(const char& func_name, signature) {
    return false; // TODO: func by name, filtered by typeclass
  }

  template<
  typename T,
  typename std::enable_if<std::is_same<my_interface, T>::value>::type* = nullptr
  >
  bool is_func_inherited(const char& func_name, signature) {
    return false;
  }

  template<
  typename T,
  typename std::enable_if<std::is_same<my_interface2, T>::value>::type* = nullptr
  >
  bool has_func(const char& func_name, signature) {
    if(!my_interface2_model) {
      return false;
    }
    return my_interface2_model->has_func(func_name); // TODO
  }
#endif // 0

  void draw(const char* surface) noexcept {
    if(!my_interface_model) {
      //throw std::runtime_error("my_interface_model not set");
      std::terminate();
    }
    my_interface_model->__draw(surface);
  }

  explicit operator bool() const noexcept {
    return (bool)my_interface_model && (bool)my_interface2_model;
  }

  template <class T>
  void create_my_interface2_model(const T&& u) noexcept {
    my_interface2_model = std::make_shared<
      _tc_impl_t<T, my_interface2>>
        (std::forward<const std::decay_t<T>>(u));
    puts("create_my_interface2_model{T} called");
  }

  template <class T>
  void create_my_interface_model(const T&& u) noexcept {
    my_interface_model = std::make_shared<
      _tc_impl_t<T, template_interface<int, const std::string&>>>
        (std::forward<const std::decay_t<T>>(u));
    puts("create_my_interface_model{T} called");
  }

  template <class T>
  void set_common_model(const T&& u) noexcept {
    create_my_interface_model(std::forward<const std::decay_t<T>>(u));
    create_my_interface2_model(std::forward<const std::decay_t<T>>(u));
    puts("set_common_model{T} called");
  }

  bool has_my_interface_model() const noexcept {
    return (bool)my_interface_model;
  }

  bool has_my_interface2_model() const noexcept {
    return (bool)my_interface2_model;
  }

  std::shared_ptr<_tc_model_t<template_interface<int, const std::string&>>> ref_my_interface_model() const noexcept {
    return my_interface_model;
  }

  std::shared_ptr<_tc_model_t<my_interface2>> ref_my_interface2_model() const noexcept {
    return my_interface2_model;
  }

  std::unique_ptr<_tc_model_t<template_interface<int, const std::string&>>> clone_my_interface_model() const noexcept {
    if(!my_interface_model) {
      //throw std::runtime_error("my_interface_model not set");
      std::terminate();
    }
    return my_interface_model->clone();
  }

  std::unique_ptr<_tc_model_t<my_interface2>> clone_my_interface2_model() const noexcept {
    if(!my_interface2_model) {
      //throw std::runtime_error("my_interface_model2 not set");
      std::terminate();
    }
    return my_interface2_model->clone();
  }

  const _tc_model_t<template_interface<int, const std::string&>>* raw_my_interface_model() const noexcept {
    return my_interface_model.get();
  }

  const _tc_model_t<my_interface2>* raw_my_interface2_model() const noexcept {
    return my_interface2_model.get();
  }

  void replace_my_interface_model(
    const std::shared_ptr<_tc_model_t<template_interface<int, const std::string&>>> rhs) noexcept {
    my_interface_model = rhs;
  }

  void replace_my_interface2_model(
    const std::shared_ptr<_tc_model_t<my_interface2>> rhs) noexcept {
    my_interface2_model = rhs;
  }

  /*operator _tc_combined_t<my_interface2> {
    return _tc_combined_t<my_interface2>{forward_t{}};
  }*/

  operator const _tc_combined_t<my_interface2>() const noexcept {
      return _tc_combined_t<
        my_interface2>{ my_interface2_model/*->clone()*/ };
  }

  operator const _tc_combined_t<template_interface<int, const std::string&>>() const noexcept {
      return _tc_combined_t<
        template_interface<int, const std::string&>>
          { my_interface_model/*->clone()*/ };
  }

  /*operator _tc_combined_t<my_interface2>&&() const {
      return _tc_combined_t<
        my_interface2>{ my_interface2_model->move_clone() };
  }

  operator _tc_combined_t<template_interface<int, const std::string&>>&&() const {
      return _tc_combined_t<
        template_interface<int, const std::string&>>
          { my_interface_model->move_clone() };
  }*/

  // TODO: a.castTo(base) calls base.castFrom<a>

  // This is actually a unique_ptr to an impl type. We store a pointer to
  // the base type and rely on _tc_model_t's virtual dtor to free the object.
  std::shared_ptr<_tc_model_t<template_interface<int, const std::string&>>> my_interface_model;
  std::shared_ptr<_tc_model_t<my_interface2>> my_interface2_model;
  /// ... TODO: change to std::array and add typeclass_by_string?
};

} // namespace cxxctp
} // namespace generated
