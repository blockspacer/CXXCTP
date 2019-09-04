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
  virtual ~_tc_model_t() { }

  virtual std::unique_ptr<_tc_model_t> clone() = 0;
  virtual std::unique_ptr<_tc_model_t> move_clone() = 0;
  virtual bool __has_do_job() const = 0;

  virtual void __do_job(const char* filename, const char* access) = 0;

  //virtual void __set_get_bar(std::function<std::string()>& func);

  //virtual void __set_set_bar(std::function<void(const std::string&)>& func);

  virtual std::string __get_bar() = 0;
  virtual void __set_bar(const std::string& data) = 0;

  template <typename T, typename A>
  static std::string show(T const &, A const &) = delete;
  //virtual void __show() = 0;

  template <typename T>
  T& ref_concrete();

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
  std::string test_zoo(const std::string& arg);

  virtual std::string __test_zoo(const std::string& arg) = 0;
};

/*template <typename T, typename M>
T& g_ref_concrete(M);*/

// ================
template <>
allcaps_t& _tc_model_t<my_interface2>::ref_concrete<allcaps_t>();

template <>
std::string _tc_model_t<my_interface2>::test_zoo<allcaps_t>(const std::string& arg);

template<>
struct _tc_impl_t<allcaps_t, my_interface2>
    : public _tc_model_t<my_interface2> {
  typedef allcaps_t val_type_t;
  //friend void draw(const allcaps_t&);

  // Construct the embedded concrete type.
  template<typename... args_t>
  _tc_impl_t(args_t&&... args) : concrete(std::forward<args_t>(args)...) { }

  explicit _tc_impl_t(const allcaps_t& concrete_arg);

  /*template<
  typename C,
  typename A,
  typename std::enable_if<std::is_same<allcaps_t, C>::value>::type* = nullptr
  >*/
  template<typename A>
  static std::string show(allcaps_t const &, A const & arg2) {
    std::cout << "show for allcaps_t " << arg2 << std::endl;
    return "show for allcaps_t";
  };

  /*template <typename A>
  static std::string __show(A const & arg2) {
    std::cout << "__show for allcaps_t " << arg2 << std::endl;
    return "show for allcaps_t";
  };*/

  /*void __show() override {
    show(concrete, "");
  }*/

  std::unique_ptr<
    _tc_model_t<my_interface2>>
      clone() override;

  std::unique_ptr<
    _tc_model_t<my_interface2>>
      move_clone() override {
    return std::make_unique<_tc_impl_t>(std::move(concrete));
  }

  bool __has_do_job() const override;

  void __do_job(const char* filename, const char* access) override;

  virtual std::string __test_zoo(const std::string& arg) override {
    return test_zoo<allcaps_t>(arg);
  }

  std::string __get_bar() override {
    if(!__get_bar_func) {
      throw std::runtime_error("get_bar not implemented");
    }
    return __get_bar_func(concrete);
  }

  void __set_bar(const std::string& data) override {
    if(!__set_bar_func) {
      throw std::runtime_error("set_bar not implemented");
    }
    return __set_bar_func(concrete, data);
  }

  /*template <>
  void set_set_bar<allcaps_t, const std::string&>
    (std::function<void(allcaps_t&, const std::string&)> arg) {

  }*/

  /*void __set_get_bar(
   std::function<std::string(const _tc_model_t<my_interface2>*)>& func) override {
    __get_bar = [this, &func](){
      //return concrete.allcaps_t_bar;
      return func(this);
    };//func;
  }

  void __set_set_bar(std::function<void(const std::string&)>& func) override {
    __set_bar = [this](const std::string& arg1){
      //concrete.allcaps_t_bar = arg1;
    };//func;
  }*/

  std::function<std::string(allcaps_t&)> __get_bar_func;

  std::function<void(allcaps_t&, const std::string&)> __set_bar_func;

  void __set_get_bar(const std::function<std::string(allcaps_t&)>& func) {
    if(func) {
        __get_bar_func = func;
    } else {
      std::cout << "Wrong func in __set_set_bar\n";
    }
  }

#if 0
  void __set_set_bar(const std::any& func) override {
    if(func.has_value()) {
      try {
        __set_bar_func = std::any_cast<
          std::function<void(allcaps_t&, const std::string&)>/*decltype(__set_bar_func)*/>(
            func);
      } catch(std::bad_any_cast&) {
          std::cout << "Wrong type in std::any\n";
      }
    } else {
      std::cout << "Wrong value in std::any\n";
    }
  }
#endif
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

template <>
forward_t& _tc_model_t<my_interface2>::ref_concrete<forward_t>();

template <>
std::string _tc_model_t<my_interface2>::test_zoo<forward_t>(const std::string& arg);

template<>
struct _tc_impl_t<forward_t, my_interface2>
    : public _tc_model_t<my_interface2> {
  typedef forward_t val_type_t;

  // Construct the embedded concrete type.
  template<typename... args_t>
  _tc_impl_t(args_t&&... args)
    : concrete(std::forward<args_t>(args)...) { }

  explicit _tc_impl_t(const forward_t& concrete_arg)
    : concrete(concrete_arg) {}

  std::unique_ptr<
    _tc_model_t<my_interface2>>
      clone() override {
    // Copy-construct a new instance of _tc_impl_t on the heap.
    return std::make_unique<_tc_impl_t>(concrete);
  }

  std::unique_ptr<
    _tc_model_t<my_interface2>>
      move_clone() override {
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
  static std::string show(forward_t const &, A const & arg2) {
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

  bool __has_do_job() const override {
    return true;
  }

  void __do_job(const char* filename, const char* access) override {
    return concrete.do_job(std::forward<decltype(filename)>(filename),
      std::forward<decltype(access)>(access));
  }

  virtual std::string __test_zoo(const std::string& arg) override {
    return test_zoo<forward_t>(arg);
  }

  std::string __get_bar() override {
    if(!__get_bar_func) {
      throw std::runtime_error("get_bar not implemented");
    }
    return __get_bar_func(concrete);
  }

  void __set_bar(const std::string& data) override {
    if(!__set_bar_func) {
      throw std::runtime_error("set_bar not implemented");
    }
    return __set_bar_func(concrete, data);
  }

  /*void __set_get_bar(std::function<std::string()>& func) override {
    __get_bar = func;
  }

  void __set_set_bar(std::function<void(const std::string&)>& func) override {
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
  void __set_set_bar(const std::any& func) override {
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

  void
   __set_set_bar(const std::function<void(forward_t&, const std::string&)>& func) {
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
reverse_t& _tc_model_t<my_interface2>::ref_concrete<reverse_t>();

template <>
std::string _tc_model_t<my_interface2>::test_zoo<reverse_t>(const std::string& arg);

template<>
struct _tc_impl_t<reverse_t, my_interface2>
    : public _tc_model_t<my_interface2> {
  typedef reverse_t val_type_t;

  // Construct the embedded concrete type.
  template<typename... args_t>
  _tc_impl_t(args_t&&... args)
    : concrete(std::forward<args_t>(args)...) { }

  explicit _tc_impl_t(const reverse_t& concrete_arg)
    : concrete(concrete_arg) {}

  std::unique_ptr<
    _tc_model_t<my_interface2>>
      clone() override {
    // Copy-construct a new instance of _tc_impl_t on the heap.
    return std::make_unique<_tc_impl_t>(concrete);
  }

  std::unique_ptr<
    _tc_model_t<my_interface2>>
      move_clone() override {
    return std::make_unique<_tc_impl_t>(std::move(concrete));
  }

  /*template<
  typename C,
  typename A,
  typename std::enable_if<std::is_same<reverse_t, C>::value>::type* = nullptr
  >*/
  template<typename A>
  static std::string show(reverse_t const &, A const & arg2) {
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

  bool __has_do_job() const override {
    return false;
  }

  void __do_job(const char* filename, const char* access) override {
    // TODO: noexcept
    throw std::runtime_error("reverse_t::do_job not implemented");
  }

  virtual std::string __test_zoo(const std::string& arg) override {
    return test_zoo<reverse_t>(arg);
  }

  std::string __get_bar() override {
    if(!__get_bar_func) {
      throw std::runtime_error("get_bar not implemented");
    }
    return __get_bar_func(concrete);
  }

  void __set_bar(const std::string& data) override {
    if(!__set_bar_func) {
      throw std::runtime_error("set_bar not implemented");
    }
    return __set_bar_func(concrete, data);
  }

  /*void __set_get_bar(std::function<std::string()>& func) override {
    __get_bar = func;
  }

  void __set_set_bar(std::function<void(const std::string&)>& func) override {
    __set_bar = func;
  }*/

  std::function<std::string(reverse_t&)> __get_bar_func;

  std::function<void(reverse_t&, const std::string&)> __set_bar_func;

  void __set_get_bar(const std::function<std::string(reverse_t&)>& func) {
    if(func) {
        __get_bar_func = func;
    } else {
      std::cout << "Wrong func in __set_set_bar\n";
    }
  }

#if 0
  void __set_set_bar(const std::any& func) override {
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

  void __set_set_bar(const std::function<void(reverse_t&, const std::string&)>& func) {
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

template<>
struct _tc_combined_t<my_interface2> {
  //typedef my_interface, my_interface2 typeclass_t;

  // Default initializer creates an empty _tc_combined_t.
  _tc_combined_t() = default;

  /// \note moves passed argument
  template <class T>
  _tc_combined_t(std::shared_ptr<T>&& u) :
    my_interface2_model(std::move(u)) {
    puts("_tc_combined_t{my_interface2} called, moves passed argument");
  }

  template <class T>
  _tc_combined_t(const T&& u) :
      my_interface2_model(
        std::make_shared<
          _tc_impl_t<T, my_interface2>>
        (std::forward<const std::decay_t<T>>(u))) {
    puts("_tc_combined_t{T} called");
  }

  // Move ctor/assign by default.
  /*_tc_combined_t(_tc_combined_t&&) = default;
  _tc_combined_t& operator=(_tc_combined_t&&) = default;*/

  // Call clone for copy ctor/assign.
  _tc_combined_t(const _tc_combined_t& rhs) {
    if(rhs)
      my_interface2_model = rhs.my_interface2_model->clone();
  }

  _tc_combined_t& operator=(const _tc_combined_t& rhs) {
    my_interface2_model.reset();
    if(rhs)
      my_interface2_model = rhs.my_interface2_model->clone();
    return *this;
  }

  // Call move_clone for move ctor/assign.
  _tc_combined_t(_tc_combined_t&& rhs) {
    if(rhs)
      my_interface2_model = rhs.my_interface2_model->move_clone();
  }

  _tc_combined_t& operator=(_tc_combined_t&& rhs) {
    my_interface2_model.reset();
    if(rhs)
      my_interface2_model = rhs.my_interface2_model->move_clone();
    return *this;
  }

  void reset() {
    my_interface2_model.reset();
  }

  // A virtual dtor triggers the dtor in the impl.
  virtual ~_tc_combined_t() { }

  // The preferred initializer for a _tc_combined_t. This constructs an _tc_impl_t of
  // type_t on the heap, and stores the pointer in a new _tc_combined_t.
  template<typename type_t, typename... args_t>
  static _tc_combined_t construct(args_t&&... args) {
    return _tc_combined_t(std::make_shared<_tc_impl_t<type_t, my_interface2> >(
      std::forward<args_t>(args)...
    ));
  }

  bool has_do_job() const {
    if(!my_interface2_model) {
      throw std::runtime_error("my_interface2_model not set");
    }
    return my_interface2_model->__has_do_job(); // force to true if required
  }

  template <typename ...Params>
  void do_job(Params&&... args) {
    if(!my_interface2_model) {
      throw std::runtime_error("my_interface2_model not set");
    }
    return my_interface2_model->__do_job(std::forward<decltype(args)>(args)...);
  }

  template<
  typename B,
  typename C>
  std::string show(const B& arg1, C const & arg2) {
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
  std::string get_bar(Params&&... args) {
    if(!my_interface2_model) {
      throw std::runtime_error("my_interface2_model not set");
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
  void set_get_bar(std::function<std::string(T&)> arg);

  template <typename ...Params>
  void set_bar(Params&&... args) {
    if(!my_interface2_model) {
      throw std::runtime_error("my_interface2_model not set");
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
  void set_set_bar(std::function<void(T&, const std::string&)> arg);

  explicit operator bool() const {
    return (bool)my_interface2_model;
  }

  std::shared_ptr<_tc_model_t<my_interface2>> ref_my_interface2_model() const {
    if(!my_interface2_model) {
      throw std::runtime_error("my_interface2_model not set");
    }
    return my_interface2_model;
  }

  std::unique_ptr<_tc_model_t<my_interface2>> clone_my_interface2_model() const {
    if(!my_interface2_model) {
      throw std::runtime_error("my_interface2_model not set");
    }
    return my_interface2_model->clone();
  }

  const _tc_model_t<my_interface2>* raw_my_interface2_model() const {
    return my_interface2_model.get();
  }

  void replace_my_interface2_model(
    const std::shared_ptr<_tc_model_t<my_interface2>> rhs) {
    my_interface2_model = rhs;
  }

  template <typename T>
  T& ref_concrete() {
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

  std::string test_zoo(const std::string& arg);

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

