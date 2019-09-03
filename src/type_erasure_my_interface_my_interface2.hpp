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
struct combined_t<my_interface, my_interface2> {
  //typedef my_interface, my_interface2 typeclass_t;

  // Default initializer creates an empty combined_t.
  combined_t() = default;

  /// \note moves passed argument
  /*template <class T>
  combined_t(std::shared_ptr<model_t<my_interface>>&& u) :
    my_interface_model(std::move(u)) {
    puts("combined_t{my_interface, my_interface2}(my_interface2) "
         "called, moves passed argument");
  }

  /// \note moves passed argument
  template <class T>
  combined_t(std::shared_ptr<model_t<my_interface2>>&& u) :
    my_interface2_model(std::move(u)) {
    puts("combined_t{my_interface, my_interface2}(my_interface2) "
         "called, moves passed argument");
  }*/

#if 0
  template <class T>
  combined_t(std::shared_ptr<T>&& u) :
    my_interface2_model(/*std::move*/(u)) {
    puts("combined_t{unique_ptr} called");
  }
#endif // 0

  template <class T>
  combined_t(const T&& u) :
      my_interface2_model(
        std::make_shared<
          impl_t<T, my_interface2>>
        (std::forward<const std::decay_t<T>>(u))),
      my_interface_model(
        std::make_shared<
          impl_t<T, my_interface>>
        (std::forward<const std::decay_t<T>>(u))) {
    puts("combined_t{T} called");
  }

  /*template <class T>
  combined_t(std::unique_ptr<T>&& u) :
    my_interface2_model(std::move(u)) {
    puts("combined_t{unique_ptr} called");
  }

  template <class T>
  combined_t(const T&& u) :
      my_interface2_model(
        std::make_unique<
          impl_t<T, my_interface2>>
        (std::forward<const std::decay_t<T>>(u))) {
    puts("combined_t{T} called");
  }*/

  // Move ctor/assign by default.
  combined_t(combined_t&&) = default;
  combined_t& operator=(combined_t&&) = default;

  // Call clone for copy ctor/assign.
  combined_t(const combined_t& rhs) {
    if(rhs) {
      my_interface_model = rhs.my_interface_model->clone();
      my_interface2_model = rhs.my_interface2_model->clone();
    }
  }

  combined_t& operator=(const combined_t& rhs) {
    my_interface_model.reset();
    my_interface2_model.reset();
    if(rhs) {
      my_interface_model = rhs.my_interface_model->clone();
      my_interface2_model = rhs.my_interface2_model->clone();
    }
    return *this;
  }

  combined_t& operator=(const combined_t<my_interface>& rhs) {
    my_interface_model.reset();
    if(rhs) {
      my_interface_model = rhs.my_interface_model->clone();
    }
    return *this;
  }

  combined_t& operator=(const combined_t<my_interface2>& rhs) {
    my_interface2_model.reset();
    if(rhs) {
      my_interface2_model = rhs.my_interface2_model->clone();
    }
    return *this;
  }

  // A virtual dtor triggers the dtor in the impl.
  virtual ~combined_t() { }

  // The preferred initializer for a combined_t. This constructs an impl_t of
  // type_t on the heap, and stores the pointer in a new combined_t.
  /*template<typename T, typename type_t, typename... args_t>
  static combined_t construct(args_t&&... args) {
    return combined_t(std::make_unique<impl_t<type_t, T> >(
      std::forward<args_t>(args)...
    ));
  }*/

  /*template<typename type_t, typename... args_t>
  static combined_t set_my_interface_model(args_t&&... args) {
    my_interface_model = (std::make_unique<impl_t<type_t, my_interface_model> >(
      std::forward<args_t>(args)...
    ));
  }*/

  /*template <class T>
  void set_my_interface2_model(std::unique_ptr<impl_t<T, my_interface2>>&& u) :
    my_interface2_model(std::move(u)) {
    puts("combined_t{unique_ptr} called");
  }*/

  void reset() {
    my_interface_model.reset();
    my_interface2_model.reset();
  }

  bool has_do_job() const {
    if(!my_interface2_model) {
      throw std::runtime_error("my_interface_model2 not set");
    }
    return my_interface2_model->__has_do_job(); // force to true if required
  }

  template <typename ...Params>
  void do_job(Params&&... args) {
    if(!my_interface2_model) {
      throw std::runtime_error("my_interface_model2 not set");
    }
    return my_interface2_model->__do_job(std::forward<decltype(args)>(args)...);
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

  void draw(const char* surface) {
    if(!my_interface_model) {
      throw std::runtime_error("my_interface_model not set");
    }
    my_interface_model->__draw(surface);
  }

  explicit operator bool() const {
    return (bool)my_interface_model && (bool)my_interface2_model;
  }

  template <class T>
  void create_my_interface2_model(const T&& u) {
    my_interface2_model = std::make_shared<
      impl_t<T, my_interface2>>
        (std::forward<const std::decay_t<T>>(u));
    puts("create_my_interface2_model{T} called");
  }

  template <class T>
  void create_my_interface_model(const T&& u) {
    my_interface_model = std::make_shared<
      impl_t<T, my_interface>>
        (std::forward<const std::decay_t<T>>(u));
    puts("create_my_interface_model{T} called");
  }

  template <class T>
  void set_common_model(const T&& u) {
    create_my_interface_model(std::forward<const std::decay_t<T>>(u));
    create_my_interface2_model(std::forward<const std::decay_t<T>>(u));
    puts("set_common_model{T} called");
  }

  bool has_my_interface_model() const {
    return (bool)my_interface_model;
  }

  bool has_my_interface2_model() const {
    return (bool)my_interface2_model;
  }

  std::shared_ptr<model_t<my_interface>> ref_my_interface_model() const {
    return my_interface_model;
  }

  std::shared_ptr<model_t<my_interface2>> ref_my_interface2_model() const {
    return my_interface2_model;
  }

  std::unique_ptr<model_t<my_interface>> clone_my_interface_model() const {
    if(!my_interface_model) {
      throw std::runtime_error("my_interface_model not set");
    }
    return my_interface_model->clone();
  }

  std::unique_ptr<model_t<my_interface2>> clone_my_interface2_model() const {
    if(!my_interface2_model) {
      throw std::runtime_error("my_interface_model2 not set");
    }
    return my_interface2_model->clone();
  }

  const model_t<my_interface>* raw_my_interface_model() const {
    return my_interface_model.get();
  }

  const model_t<my_interface2>* raw_my_interface2_model() const {
    return my_interface2_model.get();
  }

  void replace_my_interface_model(
    const std::shared_ptr<model_t<my_interface>> rhs) {
    my_interface_model = rhs;
  }

  void replace_my_interface2_model(
    const std::shared_ptr<model_t<my_interface2>> rhs) {
    my_interface2_model = rhs;
  }

  // TODO: a.castTo(base) calls base.castFrom<a>

  // This is actually a unique_ptr to an impl type. We store a pointer to
  // the base type and rely on model_t's virtual dtor to free the object.
  std::shared_ptr<model_t<my_interface>> my_interface_model;
  std::shared_ptr<model_t<my_interface2>> my_interface2_model;
  /// ... TODO: change to std::array and add typeclass_by_string?
};

////////////////////////////////////////////////////////////////////////////////
// The var_t class template is specialized to include all member functions in
// my_interface. It makes forwarding calls from these to the virtual
// functions in model_t.

// The typedef helps emphasize that we have a single type that encompasses
// multiple impl types that aren't related by inheritance.
typedef combined_t<my_interface, my_interface2> my_interface_my_interface2_obj_t;

} // namespace cxxctp
} // namespace generated
