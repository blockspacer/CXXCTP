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
#include "type_erasure_my_interface2_externs.hpp"

namespace cxxctp {
namespace generated {

/*struct common__tc_model_t {
  virtual ~common__tc_model_t() { }
};*/

template<>
struct _tc_model_t<my_interface2> {
  virtual ~_tc_model_t() noexcept { }

  //static size_t constexpr type_hash = Hash("type_hash_unset");

  virtual const size_t getModelTypeIndex() const noexcept = 0;

  virtual std::unique_ptr<_tc_model_t> clone() noexcept = 0;
  virtual std::unique_ptr<_tc_model_t> move_clone() noexcept = 0;
  virtual bool __has_do_job() const noexcept = 0;

  virtual void __do_job(const char* filename, const char* access) noexcept = 0;

  //virtual void __set_get_bar(std::function<std::string()>& func);

  //virtual void __set_set_bar(std::function<void(const std::string&)>& func);

  virtual std::string __get_bar() noexcept = 0;
  virtual void __set_bar(const std::string& data) noexcept = 0;

  template <typename T, typename A>
  static std::string show(T const &, A const &) noexcept = delete;

  //virtual void __show() = 0;

  template <typename T>
  T& ref_concrete() noexcept;

#if 0
  //template<typename T>
  virtual void __set_get_bar(const std::any& func) = 0;/* {
    __get_bar = [this, &func]() {
      //return concrete.allcaps_t_bar;
      return func(this);
    };//func;
  }*/
#endif // 0

  /*template <typename T, typename ...Params>
  void set_set_bar(std::function<void(T&, Params&&...)> arg);*/

  //virtual void __set_set_bar(const std::any& func) = 0;
  /*{
    __set_bar = [this, &func](const std::string& arg1) {
      func(this, arg1);
      //concrete.allcaps_t_bar = arg1;
    };//func;
  }*/

  /*template <typename ...Params>
  void set_set_bar2(Params&&... args) {
  }*/

  template <typename T>
  std::string test_zoo(const std::string& arg) noexcept;

  virtual std::string __test_zoo(const std::string& arg) noexcept = 0;
};

/*template <typename T, typename M>
T& g_ref_concrete(M);*/

// ================
template <>
allcaps_t& _tc_model_t<my_interface2>::ref_concrete<allcaps_t>() noexcept;

template <>
std::string _tc_model_t<my_interface2>::test_zoo<allcaps_t>(const std::string& arg) noexcept;

template<>
struct _tc_impl_t<allcaps_t, my_interface2>
    : public _tc_model_t<my_interface2> {
  typedef allcaps_t val_type_t;

  //static size_t constexpr type_hash = Hash("allcaps_t");

  // Construct the embedded concrete type.
  template<typename... args_t>
  _tc_impl_t(args_t&&... args) noexcept : concrete(std::forward<args_t>(args)...) { }

  explicit _tc_impl_t(const allcaps_t& concrete_arg) noexcept;

  template<typename A>
  static std::string show(allcaps_t const &, A const & arg2) noexcept {
    std::cout << "show for allcaps_t " << arg2 << std::endl;
    return "show for allcaps_t";
  };

  const size_t getModelTypeIndex() const noexcept override final {
    return _tc_registry<my_interface2>::
      getTypeIndex<allcaps_t>();
  }

  std::unique_ptr<
    _tc_model_t<my_interface2>>
      clone() noexcept override final;

  std::unique_ptr<
    _tc_model_t<my_interface2>>
      move_clone() noexcept override final {
    return std::make_unique<_tc_impl_t>(std::move(concrete));
  }

  bool __has_do_job() const noexcept override final;

  void __do_job(const char* filename, const char* access) noexcept override final;

  virtual std::string __test_zoo(const std::string& arg) noexcept override final {
    return test_zoo<allcaps_t>(arg);
  }

  std::string __get_bar() noexcept override final {
    if(!__get_bar_func) {
      //throw std::runtime_error("get_bar not implemented");
      std::terminate();
    }
    return __get_bar_func(concrete);
  }

  void __set_bar(const std::string& data) noexcept override final {
    if(!__set_bar_func) {
      //throw std::runtime_error("set_bar not implemented");
      std::terminate();
    }
    return __set_bar_func(concrete, data);
  }

  std::function<std::string(allcaps_t&)> __get_bar_func;

  std::function<void(allcaps_t&, const std::string&)> __set_bar_func;

  void __set_get_bar(const std::function<std::string(allcaps_t&)>& func) {
    if(func) {
        __get_bar_func = func;
    } else {
      std::cout << "Wrong func in __set_set_bar\n";
    }
  }

  void __set_set_bar(const std::function<void(allcaps_t&, const std::string&)>& func) {
    if(func) {
        __set_bar_func = func;
    } else {
      std::cout << "Wrong func in __set_set_bar\n";
    }
  }

  // Our actual data.
  allcaps_t concrete;
};

// ================
template <>
std::reference_wrapper<allcaps_t>& _tc_model_t<my_interface2>::
  ref_concrete<std::reference_wrapper<allcaps_t>>() noexcept;

template <>
std::string _tc_model_t<my_interface2>::
  test_zoo<std::reference_wrapper<allcaps_t>>(const std::string& arg) noexcept;

template<>
struct _tc_impl_t<std::reference_wrapper<allcaps_t>, my_interface2>
    : public _tc_model_t<my_interface2> {
  typedef std::reference_wrapper<allcaps_t> val_type_t;

  //static size_t constexpr type_hash = Hash("allcaps_t");

  // Construct the embedded concrete type.
  template<typename... args_t>
  _tc_impl_t(args_t&&... args) noexcept
      : concrete(std::forward<args_t>(args)...) {
    std::cout << "_tc_impl_t ref for allcaps_t " << std::endl;
  }

  explicit _tc_impl_t(const std::reference_wrapper<allcaps_t>& concrete_arg) noexcept
    : concrete(concrete_arg) {}

  template<typename A>
  static std::string show(allcaps_t const &, A const & arg2) noexcept {
    std::cout << "show for allcaps_t " << arg2 << std::endl;
    return "show for allcaps_t";
  };

  std::unique_ptr<
    _tc_model_t<my_interface2>>
      clone() noexcept override final {
    std::cout << "called clone "
                 "for ref my_interface2 allcaps_t" << std::endl;
    // Copy-construct a new instance of _tc_impl_t on the heap.
    /// \note clones data, not ref
    allcaps_t cloned = concrete;
    return std::make_unique<_tc_impl_t<allcaps_t, my_interface2>>
      (std::move(cloned));
  }

  const size_t getModelTypeIndex() const noexcept override final {
    return _tc_registry<my_interface2>::getTypeIndex<allcaps_t>();
  }

  std::unique_ptr<
    _tc_model_t<my_interface2>>
      move_clone() noexcept override final {
    std::cout << "called move_clone "
                 "for ref my_interface2 allcaps_t" << std::endl;
    /// \note moves data, not ref
    return std::make_unique<_tc_impl_t<allcaps_t, my_interface2>>
      (std::move(concrete.get()));
  }

  bool __has_do_job() const noexcept override final {
    return false;
  }

  void __do_job(const char* filename, const char* access) noexcept override final {
      // TODO: noexcept
      /// \note passes data, not ref
      std::cout << "called __do_job for "
                   "std::reference_wrapper<allcaps_t> "
                   "with allcaps_t_data = "
                    << concrete.get().allcaps_t_data << std::endl;
      // TODO:
      //throw std::runtime_error("allcaps_t::do_job not implemented");
  }

  virtual std::string __test_zoo(const std::string& arg) noexcept override final {
    /// \note passes ref, not data!
    /// otherwize we won`t be able to call get_concrete<ref_type>
    return test_zoo<std::reference_wrapper<allcaps_t>>(arg);
  }

  std::string __get_bar() noexcept override final {
    if(!__get_bar_func) {
      //throw std::runtime_error("get_bar not implemented");
      std::terminate();
    }
    /// \note passes data, not ref
    return __get_bar_func(concrete.get());
  }

  void __set_bar(const std::string& data) noexcept override final {
    if(!__set_bar_func) {
      //throw std::runtime_error("set_bar not implemented");
      std::terminate();
    }
    /// \note passes data, not ref
    return __set_bar_func(concrete.get(), data);
  }

  std::function<std::string(allcaps_t&)> __get_bar_func;

  std::function<void(allcaps_t&, const std::string&)> __set_bar_func;

  void __set_get_bar(const std::function<std::string(allcaps_t&)>& func) noexcept {
    if(func) {
        __get_bar_func = func;
    } else {
      std::cout << "Wrong func in __set_set_bar\n";
    }
  }

  void __set_set_bar(const std::function<void(allcaps_t&, const std::string&)>& func) noexcept {
    if(func) {
        __set_bar_func = func;
    } else {
      std::cout << "Wrong func in __set_set_bar\n";
    }
  }

  // Our actual data.
  std::reference_wrapper<allcaps_t> concrete;
};

template <>
forward_t& _tc_model_t<my_interface2>::
  ref_concrete<forward_t>() noexcept;

template <>
std::string _tc_model_t<my_interface2>::
  test_zoo<forward_t>(const std::string& arg) noexcept;

template<>
struct _tc_impl_t<forward_t, my_interface2>
    : public _tc_model_t<my_interface2> {
  typedef forward_t val_type_t;

  //static size_t constexpr type_hash = Hash("forward_t");

  // Construct the embedded concrete type.
  template<typename... args_t>
  _tc_impl_t(args_t&&... args) noexcept
    : concrete(std::forward<args_t>(args)...) { }

  explicit _tc_impl_t(const forward_t& concrete_arg) noexcept
    : concrete(concrete_arg) {}

  std::unique_ptr<
    _tc_model_t<my_interface2>>
      clone() noexcept override final {
    // Copy-construct a new instance of _tc_impl_t on the heap.
    return std::make_unique<_tc_impl_t>(concrete);
  }

  const size_t getModelTypeIndex() const noexcept override final {
    return _tc_registry<my_interface2>::getTypeIndex<forward_t>();
  }

  std::unique_ptr<
    _tc_model_t<my_interface2>>
      move_clone() noexcept override final {
    return std::make_unique<_tc_impl_t>(std::move(concrete));
  }

  /*template<
  typename C,
  typename A,
  typename std::enable_if<std::is_same<forward_t, C>::value>::type* = nullptr
  >
  static std::string show(C const &, A const & arg2) {
    std::cout << "show for forward_t " << arg2 << std::endl;
    return "show for forward_t";
  };*/
  template<typename A>
  static std::string show(forward_t const &, A const & arg2) noexcept {
    std::cout << "show for forward_t " << arg2 << std::endl;
    return "show for forward_t";
  };
  /*void __show() override {
    show(concrete, "");
  }*/

  /*template <typename A>
  static std::string __show(A const & arg2) {
    std::cout << "__show for forward_t " << arg2 << std::endl;
    return "show for forward_t";
  };*/

  bool __has_do_job() const noexcept override final {
    return true;
  }

  void __do_job(const char* filename, const char* access) noexcept override final {
    return concrete.do_job(std::forward<decltype(filename)>(filename),
      std::forward<decltype(access)>(access));
  }

  virtual std::string __test_zoo(const std::string& arg) noexcept override final {
    return test_zoo<forward_t>(arg);
  }

  std::string __get_bar() noexcept override final {
    if(!__get_bar_func) {
      //throw std::runtime_error("get_bar not implemented");
      std::terminate();
    }
    return __get_bar_func(concrete);
  }

  void __set_bar(const std::string& data) noexcept override final {
    if(!__set_bar_func) {
      //throw std::runtime_error("set_bar not implemented");
      std::terminate();
    }
    return __set_bar_func(concrete, data);
  }

  /*void __set_get_bar(std::function<std::string()>& func) noexcept override final {
    __get_bar = func;
  }

  void __set_set_bar(std::function<void(const std::string&)>& func) noexcept override final {
    __set_bar = func;
  }*/

  std::function<std::string(forward_t&)> __get_bar_func;

  std::function<void(forward_t&, const std::string&)> __set_bar_func;

  void __set_get_bar(const std::function<std::string(forward_t&)>& func) {
    if(func) {
        __get_bar_func = func;
    } else {
      std::cout << "Wrong func in __set_set_bar\n";
    }
  }

#if 0
  void __set_set_bar(const std::any& func) noexcept override final {
    if(func.has_value()) {
      try {
        __set_bar_func = std::any_cast<
          std::function<void(forward_t&, const std::string&)>/*decltype(__set_bar_func)*/>(
            func);
      } catch(std::bad_any_cast&) {
          std::cout << "Wrong type in std::any\n";
      }
    } else {
      std::cout << "Wrong value in std::any\n";
    }
  }
#endif // 0

  void __set_set_bar(
      const std::function<void(forward_t&, const std::string&)>& func) noexcept {
    if(func) {
        __set_bar_func = func;
    } else {
      std::cout << "Wrong func in __set_set_bar\n";
    }
  }

  // Our actual data.
  forward_t concrete;
};


template <>
reverse_t& _tc_model_t<my_interface2>::
  ref_concrete<reverse_t>() noexcept;

template <>
std::string _tc_model_t<my_interface2>::
  test_zoo<reverse_t>(const std::string& arg) noexcept;

template<>
struct _tc_impl_t<reverse_t, my_interface2>
    : public _tc_model_t<my_interface2> {
  typedef reverse_t val_type_t;

  //static size_t constexpr type_hash = Hash("reverse_t");

  // Construct the embedded concrete type.
  template<typename... args_t>
  _tc_impl_t(args_t&&... args)
    : concrete(std::forward<args_t>(args)...) { }

  explicit _tc_impl_t(const reverse_t& concrete_arg)
    : concrete(concrete_arg) {}

  std::unique_ptr<
    _tc_model_t<my_interface2>>
      clone() noexcept override final {
    // Copy-construct a new instance of _tc_impl_t on the heap.
    return std::make_unique<_tc_impl_t>(concrete);
  }

  const size_t getModelTypeIndex() const noexcept override final {
    return _tc_registry<my_interface2>::getTypeIndex<reverse_t>();
  }

  std::unique_ptr<
    _tc_model_t<my_interface2>>
      move_clone() noexcept override final {
    return std::make_unique<_tc_impl_t>(std::move(concrete));
  }

  /*template<
  typename C,
  typename A,
  typename std::enable_if<std::is_same<reverse_t, C>::value>::type* = nullptr
  >*/
  template<typename A>
  static std::string show(reverse_t const &, A const & arg2) noexcept {
    std::cout << "show for reverse_t " << arg2 << std::endl;
    return "show for reverse_t";
  };
  /*void __show() override {
    show(concrete, "");
  }*/

  /*template <typename A>
  static std::string __show(A const & arg2) {
    std::cout << "__show for reverse_t " << arg2 << std::endl;
    return "show for reverse_t";
  };*/

  bool __has_do_job() const noexcept override final {
    return false;
  }

  void __do_job(const char* filename, const char* access) noexcept override final {
    // TODO: noexcept
    //throw std::runtime_error("reverse_t::do_job not implemented");
    std::terminate();
  }

  virtual std::string __test_zoo(const std::string& arg) noexcept override final {
    return test_zoo<reverse_t>(arg);
  }

  std::string __get_bar() noexcept override final {
    if(!__get_bar_func) {
      //throw std::runtime_error("get_bar not implemented");
      std::terminate();
    }
    return __get_bar_func(concrete);
  }

  void __set_bar(const std::string& data) noexcept override final {
    if(!__set_bar_func) {
      //throw std::runtime_error("set_bar not implemented");
      std::terminate();
    }
    return __set_bar_func(concrete, data);
  }

  /*void __set_get_bar(std::function<std::string()>& func) override final {
    __get_bar = func;
  }

  void __set_set_bar(std::function<void(const std::string&)>& func) override final {
    __set_bar = func;
  }*/

  std::function<std::string(reverse_t&)> __get_bar_func;

  std::function<void(reverse_t&, const std::string&)> __set_bar_func;

  void __set_get_bar(
      const std::function<std::string(reverse_t&)>& func) noexcept {
    if(func) {
        __get_bar_func = func;
    } else {
      std::cout << "Wrong func in __set_set_bar\n";
    }
  }

#if 0
  void __set_set_bar(const std::any& func) override final {
    if(func.has_value()) {
      try {
        __set_bar_func = std::any_cast<
          std::function<void(reverse_t&, const std::string&)>/*decltype(__set_bar_func)*/>(
            func);
      } catch(std::bad_any_cast&) {
          std::cout << "Wrong type in std::any\n";
      }
    } else {
      std::cout << "Wrong value in std::any\n";
    }
  }
#endif // 0

  void __set_set_bar(
      const std::function<void(reverse_t&, const std::string&)>& func) noexcept {
    if(func) {
        __set_bar_func = func;
    } else {
      std::cout << "Wrong func in __set_set_bar\n";
    }
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
          _tc_impl_t<T, my_interface2>>
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
    return var_t(std::make_unique<_tc_impl_t<type_t, my_interface2> >(
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
  // the base type and rely on _tc_model_t's virtual dtor to free the object.
  std::unique_ptr<_tc_model_t<my_interface2>> model;
};
#endif // 0

// https://stackoverflow.com/a/40430884
/*template<typename T>
struct is_reference_wrapper : std::false_type {};

template<typename T>
struct is_reference_wrapper<std::reference_wrapper<T>> : std::true_type{};
*/

template<>
struct _tc_combined_t<my_interface2> {
  //typedef my_interface, my_interface2 typeclass_t;

  // Default initializer creates an empty _tc_combined_t.
  _tc_combined_t() = default;

  _tc_combined_t(
      std::reference_wrapper<_tc_combined_t<my_interface2>>&& rhs) noexcept {
    puts("_tc_combined_t{my_interface2} ref copy ctor");
    if(rhs.get())
      my_interface2_model = rhs.get().my_interface2_model;
  }

  template <
  class T,
  typename std::enable_if<!std::is_same<_tc_combined_t, T>::value>::type* = nullptr
  >
  _tc_combined_t(const std::reference_wrapper<T>& u) noexcept :
      my_interface2_model(
        std::make_shared<
          _tc_impl_t<std::reference_wrapper<T>, my_interface2>>
        (std::forward<const std::reference_wrapper<std::decay_t<T>>>(u))) {
    puts("_tc_combined_t{T} reference_wrapper called");
  }

  // Call clone for copy ctor/assign.
  /*template <
  class T,
  typename = IsNotReference<T>,
  typename std::enable_if<std::is_same<_tc_combined_t<my_interface2>, T>::value>::type* = nullptr
  >*/
  explicit _tc_combined_t(const _tc_combined_t<my_interface2>& rhs) noexcept {
    puts("_tc_combined_t{my_interface2} copy ctor");
    if(rhs)
      my_interface2_model = rhs.my_interface2_model->clone();
  }

  // Call move_clone for move ctor/assign.
  explicit _tc_combined_t(_tc_combined_t&& rhs) noexcept {
    if(rhs)
      my_interface2_model = rhs.my_interface2_model->move_clone();
  }

  /// \note moves passed argument
  template <
  class T,
  typename = IsNotReference<T>,
  typename std::enable_if<!std::is_same<_tc_combined_t, T>::value>::type* = nullptr
  >
  _tc_combined_t(std::shared_ptr<T>&& u) noexcept :
      my_interface2_model(std::move(u)) {
   static_assert(!std::is_const<typename std::remove_reference<T>::type>::value,
      "You've attempted a cast to a const rvalue reference. "
      "Make sure you're not trying to move a const object, "
      "as this would likely result in a copy not a move. "
      "If you need it for real, call std::move(...) instead.");
    puts("_tc_combined_t{my_interface2} called, moves passed argument");
  }

  template <
  class T,
  typename = IsNotReference<T>,
  typename std::enable_if<!std::is_same<_tc_combined_t, T>::value>::type* = nullptr
  >
  _tc_combined_t(const std::shared_ptr<T>& u) noexcept :
      my_interface2_model(u) {
    puts("_tc_combined_t{my_interface2} called, shares passed argument");
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
        (std::forward<const std::decay_t<T>>(u))) {
    puts("_tc_combined_t{T} called");
  }

  // The preferred initializer for a _tc_combined_t. This constructs an _tc_impl_t of
  // type_t on the heap, and stores the pointer in a new _tc_combined_t.

  template<
    typename type_t,
    typename... args_t,
    typename = IsNotReference<type_t>
  >
  static _tc_combined_t construct(args_t&&... args) noexcept {
    return _tc_combined_t(std::make_shared<_tc_impl_t<type_t, my_interface2> >(
      std::forward<args_t>(args)...
    ));
  }

  /*template <class T>
  _tc_combined_t(const T& u) :
      my_interface2_model(
        std::make_shared<
          _tc_impl_t<T, my_interface2>>
        (std::forward<const std::decay_t<T>>(u))) {
    puts("_tc_combined_t{T} called");
  }*/

  // Move ctor/assign by default.
  /*_tc_combined_t(_tc_combined_t&&) = default;
  _tc_combined_t& operator=(_tc_combined_t&&) = default;*/

  _tc_combined_t& operator=(const _tc_combined_t& rhs) noexcept {
    my_interface2_model.reset();
    if(rhs)
      my_interface2_model = rhs.my_interface2_model->clone();
    return *this;
  }

  _tc_combined_t& operator=(_tc_combined_t&& rhs) noexcept {
    my_interface2_model.reset();
    if(rhs)
      my_interface2_model = rhs.my_interface2_model->move_clone();
    return *this;
  }

  void reset() noexcept {
    my_interface2_model.reset();
  }

  // A virtual dtor triggers the dtor in the impl.
  virtual ~_tc_combined_t() noexcept { }

  bool has_do_job() const noexcept {
    if(!my_interface2_model) {
      //throw std::runtime_error("my_interface2_model not set");
      std::terminate();
    }
    return my_interface2_model->__has_do_job(); // force to true if required
  }

  template <typename ...Params>
  void do_job(Params&&... args) noexcept {
    if(!my_interface2_model) {
      //throw std::runtime_error("my_interface2_model not set");
      std::terminate();
    }
    return my_interface2_model->__do_job(std::forward<decltype(args)>(args)...);
  }

  template<
  typename B,
  typename C>
  std::string show(const B& arg1, C const & arg2) noexcept {
    //std::cout << my_interface2_model->type_hash << std::endl;
    return _tc_impl_t<B, my_interface2>::show(arg1, arg2);
  }

  /*template <typename T, typename ...Params>
  static std::string show(Params&&... args) {
    //std::cout << "show for forward_t" << std::endl;
    //return "show for forward_t";
    return my_interface2_obj_t::show(std::forward<decltype(args)>(args)...);
  };*/

  /*template <typename ...Params>
  std::string __show(Params&&... args) {
    if(!my_interface2_model) {
      throw std::runtime_error("my_interface2_model not set");
    }

    {
      auto p = static_cast<_tc_impl_t<forward_t, my_interface2>*>(my_interface2_model.get());

      if(p) {
        return p->__show(std::forward<decltype(args)>(args)...);
      }
    }

    {
      auto p = static_cast<_tc_impl_t<reverse_t, my_interface2>*>(my_interface2_model.get());

      if(p) {
        return p->__show(std::forward<decltype(args)>(args)...);
      }
    }

    {
      auto p = static_cast<_tc_impl_t<allcaps_t, my_interface2>*>(my_interface2_model.get());

      if(p) {
        return p->__show(std::forward<decltype(args)>(args)...);
      }
    }

    throw std::runtime_error("can`t find dynamic_pointer_cast for show");
    return "";
  }*/

  template <typename ...Params>
  std::string get_bar(Params&&... args) noexcept {
    if(!my_interface2_model) {
      //throw std::runtime_error("my_interface2_model not set");
      std::terminate();
    }
    return my_interface2_model->__get_bar(std::forward<decltype(args)>(args)...);
  }

  /*template <typename ...Params>
  void set_get_bar(Params&&... args) {
    if(!my_interface2_model) {
      throw std::runtime_error("my_interface2_model not set");
    }
    return my_interface2_model->__set_get_bar(std::forward<decltype(args)>(args)...);
  }*/
  template <typename T>
  void set_get_bar(std::function<std::string(T&)> arg) noexcept;

  template <typename ...Params>
  void set_bar(Params&&... args) noexcept {
    if(!my_interface2_model) {
      //throw std::runtime_error("my_interface2_model not set");
      std::terminate();
    }
    return my_interface2_model->__set_bar(std::forward<decltype(args)>(args)...);
  }

  /*template <typename ...Params>
  void set_set_bar(Params&&... args) {
    if(!my_interface2_model) {
      throw std::runtime_error("my_interface2_model not set");
    }
    return my_interface2_model->__set_set_bar(std::forward<decltype(args)>(args)...);
  }*/

  template <typename T>
  void set_set_bar(std::function<void(T&, const std::string&)> arg) noexcept;

  explicit operator bool() const noexcept {
    return (bool)my_interface2_model;
  }

  std::shared_ptr<_tc_model_t<my_interface2>> ref_my_interface2_model() const noexcept {
    if(!my_interface2_model) {
      //throw std::runtime_error("my_interface2_model not set");
      std::terminate();
    }
    return my_interface2_model;
  }

  std::unique_ptr<_tc_model_t<my_interface2>> clone_my_interface2_model() const noexcept {
    if(!my_interface2_model) {
      //throw std::runtime_error("my_interface2_model not set");
      std::terminate();
    }
    return my_interface2_model->clone();
  }

  const _tc_model_t<my_interface2>* raw_my_interface2_model() const noexcept {
    return my_interface2_model.get();
  }

  void replace_my_interface2_model(
      const std::shared_ptr<_tc_model_t<my_interface2>> rhs) noexcept {
    my_interface2_model = rhs;
  }

  const size_t getModelTypeIndex() {
    if(!my_interface2_model) {
      std::terminate();
    }
    return my_interface2_model->getModelTypeIndex();
  }

  template <typename T>
  static const size_t getGlobalTypeIndex() {
    return _tc_registry<my_interface2>::getTypeIndex<T>();
  }

  template <typename T>
  T& ref_concrete() noexcept {
    if(!my_interface2_model || my_interface2_model->getModelTypeIndex()
        != getGlobalTypeIndex<T>()) {
      std::terminate();
    }
    return my_interface2_model->ref_concrete<T>();
  }

  /*template <typename T>
  T& ref_concrete() {
    return g_ref_concrete<T, my_interface2>(my_interface2_model);
  }*/

  /*template <typename ...Params>
  std::string test_zoo(Params&&... args) {
    return my_interface2_model->__test_zoo(std::forward<decltype(args)>(args)...);
  }*/

  std::string test_zoo(const std::string& arg) noexcept;

  // This is actually a unique_ptr to an impl type. We store a pointer to
  // the base type and rely on _tc_model_t's virtual dtor to free the object.
  std::shared_ptr<_tc_model_t<my_interface2>> my_interface2_model;
};

/*template<
typename A,
typename T,
typename C,
typename std::enable_if<std::is_same<my_interface2, A>::value>::type* = nullptr,
typename std::enable_if<std::is_same<allcaps_t, T>::value>::type* = nullptr
>
void show(const T& arg1, const C& arg2) {
    my_interface2_impl_t<T>::show(arg1, arg2);
}

template<
typename A,
typename T,
typename C,
typename std::enable_if<std::is_same<my_interface2, A>::value>::type* = nullptr,
typename std::enable_if<std::is_same<reverse_t, T>::value>::type* = nullptr
>
void show(const T& arg1, const C& arg2) {
    my_interface2_impl_t<T>::show(arg1, arg2);
}

template<
typename A,
typename T,
typename C,
typename std::enable_if<std::is_same<my_interface2, A>::value>::type* = nullptr,
typename std::enable_if<std::is_same<forward_t, T>::value>::type* = nullptr
>
void show(const T& arg1, const C& arg2) {
    my_interface2_impl_t<T>::show(arg1, arg2);
}*/

/*template<typename C>
std::string show(const forward_t& arg1, C const & arg2) {
  return my_interface2_impl_t<my_interface2>::show(arg1, arg2);
}*/

/*template<typename T>
std::string foo1(T a) {

}*/

#if 0
// ================
template <>
allcaps_t& g_ref_concrete<allcaps_t, my_interface2>(std::shared_ptr<_tc_model_t<my_interface2>> model) {
  return static_cast<_tc_impl_t<reverse_t, my_interface2>*>(model.get())
    ->concrete;
}
template <>
reverse_t& _tc_model_t<my_interface2>::ref_concrete<reverse_t>() {
  return static_cast<_tc_impl_t<reverse_t, my_interface2>*>(this)
    ->concrete;
}
template <>
forward_t& _tc_model_t<my_interface2>::ref_concrete<forward_t>() {
  return static_cast<_tc_impl_t<forward_t, my_interface2>*>(this)
    ->concrete;
}

  template <>
  std::string _tc_model_t<my_interface2>::test_zoo<allcaps_t>(const std::string& arg) {
    auto& data = ref_concrete<allcaps_t>();
    return arg + " test_zoo for allcaps_t " + data.allcaps_t_data;
  }

  template <>
  std::string _tc_model_t<my_interface2>::test_zoo<reverse_t>(const std::string& arg) {
    auto& data = ref_concrete<reverse_t>();
    return arg + " test_zoo for reverse_t " + data.reverse_t_data;
  }

  template <>
  std::string _tc_model_t<my_interface2>::test_zoo<forward_t>(const std::string& arg) {
    auto& data = ref_concrete<forward_t>();
    return arg + " test_zoo for forward_t " + data.forward_t_data;
  }

// ================
/*template <>
allcaps_t& _tc_combined_t<my_interface2>::ref_concrete<allcaps_t>() {
  return static_cast<_tc_impl_t<allcaps_t, my_interface2>*>(my_interface2_model.get())
    ->concrete;
}
template <>
reverse_t& _tc_combined_t<my_interface2>::ref_concrete<reverse_t>() {
  return static_cast<_tc_impl_t<reverse_t, my_interface2>*>(my_interface2_model.get())
    ->concrete;
}
template <>
forward_t& _tc_combined_t<my_interface2>::ref_concrete<forward_t>() {
  return static_cast<_tc_impl_t<forward_t, my_interface2>*>(my_interface2_model.get())
    ->concrete;
}*/
#endif // 0

} // namespace cxxctp
} // namespace generated

