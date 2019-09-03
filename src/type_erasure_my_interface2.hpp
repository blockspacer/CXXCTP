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

/*struct common_model_t {
  virtual ~common_model_t() { }
};*/

template<>
struct model_t<my_interface2> {
  virtual ~model_t() { }

  virtual std::unique_ptr<model_t> clone() = 0;
  virtual bool __has_do_job() const = 0;

  virtual void __do_job(const char* filename, const char* access) = 0;
};

template<>
struct impl_t<allcaps_t, my_interface2>
    : public model_t<my_interface2> {
  typedef allcaps_t val_type_t;
  //friend void draw(const allcaps_t&);

  // Construct the embedded concrete type.
  template<typename... args_t>
  impl_t(args_t&&... args) : concrete(std::forward<args_t>(args)...) { }

  explicit impl_t(const allcaps_t& concrete_arg);

  std::unique_ptr<
    model_t<my_interface2>>
      clone() override;

  bool __has_do_job() const override;

  void __do_job(const char* filename, const char* access) override;

  // Our actual data.
  allcaps_t concrete;
};

template<>
struct impl_t<forward_t, my_interface2>
    : public model_t<my_interface2> {
  typedef forward_t val_type_t;

  // Construct the embedded concrete type.
  template<typename... args_t>
  impl_t(args_t&&... args)
    : concrete(std::forward<args_t>(args)...) { }

  explicit impl_t(const forward_t& concrete_arg)
    : concrete(concrete_arg) {}

  std::unique_ptr<
    model_t<my_interface2>>
      clone() override {
    // Copy-construct a new instance of impl_t on the heap.
    return std::make_unique<impl_t>(concrete);
  }

  bool __has_do_job() const override {
    return true;
  }

  void __do_job(const char* filename, const char* access) override {
    return concrete.do_job(std::forward<decltype(filename)>(filename),
      std::forward<decltype(access)>(access));
  }

  // Our actual data.
  forward_t concrete;
};


template<>
struct impl_t<reverse_t, my_interface2>
    : public model_t<my_interface2> {
  typedef reverse_t val_type_t;

  // Construct the embedded concrete type.
  template<typename... args_t>
  impl_t(args_t&&... args)
    : concrete(std::forward<args_t>(args)...) { }

  explicit impl_t(const reverse_t& concrete_arg)
    : concrete(concrete_arg) {}

  std::unique_ptr<
    model_t<my_interface2>>
      clone() override {
    // Copy-construct a new instance of impl_t on the heap.
    return std::make_unique<impl_t>(concrete);
  }

  bool __has_do_job() const override {
    return false;
  }

  void __do_job(const char* filename, const char* access) override {
    // TODO: noexcept
    throw std::runtime_error("reverse_t::do_job not implemented");
  }

  // Our actual data.
  reverse_t concrete;
};

////////////////////////////////////////////////////////////////////////////////
#if 0
template<>
struct var_t<my_interface2> {
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
          impl_t<T, my_interface2>>
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

  // The preferred initializer for a var_t. This constructs an impl_t of
  // type_t on the heap, and stores the pointer in a new var_t.
  template<typename type_t, typename... args_t>
  static var_t construct(args_t&&... args) {
    return var_t(std::make_unique<impl_t<type_t, my_interface2> >(
      std::forward<args_t>(args)...
    ));
  }

  bool has_do_job() const {
    return model->__has_do_job(); // force to true if required
  }

  template <typename ...Params>
  void do_job(Params&&... args) {
    return model->__do_job(std::forward<decltype(args)>(args)...);
  }

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
  // the base type and rely on model_t's virtual dtor to free the object.
  std::unique_ptr<model_t<my_interface2>> model;
};
#endif // 0

template<>
struct combined_t<my_interface2> {
  //typedef my_interface, my_interface2 typeclass_t;

  // Default initializer creates an empty combined_t.
  combined_t() = default;

  /// \note moves passed argument
  template <class T>
  combined_t(std::shared_ptr<T>&& u) :
    my_interface2_model(std::move(u)) {
    puts("combined_t{my_interface2} called, moves passed argument");
  }

  template <class T>
  combined_t(const T&& u) :
      my_interface2_model(
        std::make_shared<
          impl_t<T, my_interface2>>
        (std::forward<const std::decay_t<T>>(u))) {
    puts("combined_t{T} called");
  }

  // Move ctor/assign by default.
  combined_t(combined_t&&) = default;
  combined_t& operator=(combined_t&&) = default;

  // Call clone for copy ctor/assign.
  combined_t(const combined_t& rhs) {
    if(rhs)
      my_interface2_model = rhs.my_interface2_model->clone();
  }

  combined_t& operator=(const combined_t& rhs) {
    my_interface2_model.reset();
    if(rhs)
      my_interface2_model = rhs.my_interface2_model->clone();
    return *this;
  }

  void reset() {
    my_interface2_model.reset();
  }

  // A virtual dtor triggers the dtor in the impl.
  virtual ~combined_t() { }

  // The preferred initializer for a combined_t. This constructs an impl_t of
  // type_t on the heap, and stores the pointer in a new combined_t.
  template<typename type_t, typename... args_t>
  static combined_t construct(args_t&&... args) {
    return combined_t(std::make_shared<impl_t<type_t, my_interface2> >(
      std::forward<args_t>(args)...
    ));
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

  explicit operator bool() const {
    return (bool)my_interface2_model;
  }

  std::shared_ptr<model_t<my_interface2>> ref_my_interface2_model() const {
    if(!my_interface2_model) {
      throw std::runtime_error("my_interface_model2 not set");
    }
    return my_interface2_model;
  }

  std::unique_ptr<model_t<my_interface2>> clone_my_interface2_model() const {
    if(!my_interface2_model) {
      throw std::runtime_error("my_interface_model2 not set");
    }
    return my_interface2_model->clone();
  }

  const model_t<my_interface2>* raw_my_interface2_model() const {
    return my_interface2_model.get();
  }

  void replace_my_interface2_model(
    const std::shared_ptr<model_t<my_interface2>> rhs) {
    my_interface2_model = rhs;
  }

  // This is actually a unique_ptr to an impl type. We store a pointer to
  // the base type and rely on model_t's virtual dtor to free the object.
  std::shared_ptr<model_t<my_interface2>> my_interface2_model;
};

////////////////////////////////////////////////////////////////////////////////
// The var_t class template is specialized to include all member functions in
// my_interface. It makes forwarding calls from these to the virtual
// functions in model_t.

// The typedef helps emphasize that we have a single type that encompasses
// multiple impl types that aren't related by inheritance.
typedef combined_t<my_interface2> my_interface2_obj_t;

/*template<typename T> int freeGet() = delete;

extern template
 int freeGet<int>();*/

template<
  typename T,
  typename std::enable_if<std::is_same<my_interface2, T>::value>::type* = nullptr
>
void draw(const allcaps_t&, const char* surface);

template<
  typename T,
  typename std::enable_if<std::is_same<my_interface2, T>::value>::type* = nullptr
>
void draw(const forward_t&, const char* surface);

template<
  typename T,
  typename std::enable_if<std::is_same<my_interface2, T>::value>::type* = nullptr
>
void draw(const reverse_t&, const char* surface);

} // namespace cxxctp
} // namespace generated
