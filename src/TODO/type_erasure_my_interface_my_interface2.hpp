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

/*struct my_interface;
struct forward_t;
struct reverse_t;
struct allcaps_t;*/

// TODO: inherit from multiple typeclass?

struct my_interface2 {
  virtual void print_2(const char* text) = 0;

  // @gen(extern)
  //virtual void draw_2(const char* surface) const = 0;
};

struct my_interface {
  // @gen(extern)
  virtual void draw(const char* surface) const = 0;

  // @gen(required)
  virtual void print(const char* text) = 0;

  // @gen(required)
  virtual void print_data() = 0;

  virtual void save(const char* filename, const char* access) = 0;

  virtual void set_data(const char* text) = 0;

  // TODO: pseudo inheritance by code injection
  // @gen(inject)
  void set_interface_data(const char* text);/* {
    interface_data = text;
  }*/
  // @gen(inject)
  void print_interface_data();/* {
    puts(interface_data.c_str());
  }*/
  // @gen(inject)
  std::string interface_data = "interface_data";
};

// Print the text in forward order.
// @gen(typeclass_instance(my_interface, my_interface2))
struct forward_t {
  void print_2(const char* text) {
    puts("print2: ");
    puts(text);
  }

  void print(const char* text) {
    puts(text);
  }

  void save(const char* filename, const char* access);/* {
    puts("forward_t::save called");
  }*/

  void set_data(const char* text);/* {
    forward_t_data = text;
  }*/

  void print_data();/* {
    puts(forward_t_data.c_str());
  }*/

  std::string forward_t_data = "forward_t_data";
};

// Print the text in reverse order.
// @gen(typeclass_instance(my_interface, my_interface2))
struct reverse_t {
  void print_2(const char* text) {
    puts("print2: ");
    puts(text);
  }

  void print(const char* text);/* {
    int len = strlen(text);
    for(int i = 0; i < len; ++i)
      putchar(text[len - 1 - i]);
    putchar('\n');
  }*/

  void set_data(const char* text);/* {
    reverse_t_data = text;
  }*/

  void print_data();/* {
    puts(reverse_t_data.c_str());
  }*/

  std::string reverse_t_data = "reverse_t_data";
};

// Print the text with caps.
// @gen(typeclass_instance(my_interface, my_interface2))
struct allcaps_t {
  void print_2(const char* text) {
    puts("print2: ");
    puts(text);
  }

  void print(const char* text);/* {
    while(char c = *text++)
      putchar(toupper(c));
    putchar('\n');
  }*/

  void set_data(const char* text);/* {
    allcaps_t_data = text;
  }*/

  void print_data();/* {
    puts(allcaps_t_data.c_str());
  }*/

  std::string allcaps_t_data = "allcaps_t_data";
};

namespace cxxctp {
namespace generated {

#if 0
// @gen(typeclass)
struct __my_interface_my_interface2 {
  virtual void print_2(const char* text) = 0;

  // @gen(extern)
  //virtual void draw_2(const char* surface) const = 0;

  // @gen(extern)
  virtual void draw(const char* surface) const = 0;

  // @gen(required)
  virtual void print(const char* text) = 0;

  // @gen(required)
  virtual void print_data() = 0;

  virtual void save(const char* filename, const char* access) = 0;

  virtual void set_data(const char* text) = 0;

  // TODO: pseudo inheritance by code injection
  // @gen(inject)
  void set_interface_data(const char* text);/* {
    interface_data = text;
  }*/
  // @gen(inject)
  void print_interface_data();/* {
    puts(interface_data.c_str());
  }*/
  // @gen(inject)
  std::string interface_data = "interface_data";
};
#endif // 0

/*struct common_model_t {
  virtual ~common_model_t() { }
};*/

// model_t is the base class for impl_t. impl_t has the storage for the
// object of type_t. model_t has a virtual dtor to trigger impl_t's dtor.
// model_t has a virtual clone function to copy-construct an instance of
// impl_t into heap memory, which is returned via unique_ptr. model_t has
// a pure virtual function for each method in the interface class typeclass.
template<typename... typeclass>
struct model_t /*: public common_model_t*/ {
  virtual ~model_t() { }

  virtual std::unique_ptr<model_t> clone() = 0;

  // Loop over each member function on the interface.
  /*@meta for(int i = 0; i < @method_count(typeclass); ++i) {

    @meta std::string func_name = @method_name(typeclass, i);

    // Declare a "has_" function.
    virtual bool @(format("has_%s", func_name.c_str()))() const = 0;

    // Declare a pure virtual function for each interface method.
    virtual @func_decl(@method_type(typeclass, i), func_name, args) = 0;
  }*/
};

template<>
struct model_t<my_interface, my_interface2> {
  virtual ~model_t() { }

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

  virtual std::unique_ptr<model_t> clone() = 0;
  virtual bool __has_save() const = 0;

  //template <typename ...Params>
  //virtual void save(Params&&... args) = 0;
  virtual void __save(const char* filename, const char* access) = 0;

  virtual bool __has_print_2() const = 0;
  virtual void __print_2(const char* text) = 0;

  virtual bool __has_print() const = 0;

  //template <typename ...Params>
  //virtual void print(Params&&... args) = 0;
  virtual void __print(const char* text) = 0;

  virtual void __set_data(const char* text) = 0;

  virtual void __print_data() = 0;

  virtual void __draw(const char* surface) const = 0;

  // TODO: pseudo inheritance by code injection
  void set_interface_data(const char* text);/* {
    interface_data = text;
  }*/
  void print_interface_data();/* {
    auto out = std::string("interface_data: ") + interface_data;
    puts(out.c_str());
  }*/
  std::string interface_data = "interface_data";

  // TODO: https://stackoverflow.com/a/26159287
  //template<typename... Args>
  //std::map<std::string, void(*)()> runtime_dispatch_table_;
};

template<typename type_t, typename... typeclass>
struct impl_t : public model_t<typeclass...> {

  // Construct the embedded concrete type.
  /*template<typename... args_t>
  impl_t(args_t&&... args) : concrete(std::forward<args_t>(args)...) { }

  std::unique_ptr<model_t<typeclass> > clone() override {
    // Copy-construct a new instance of impl_t on the heap.
    return std::make_unique<impl_t>(concrete);
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
    // function in model_t.
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
  //type_t concrete;
};

template<>
struct impl_t<allcaps_t, my_interface, my_interface2>
  : public model_t<my_interface, my_interface2> {
  //friend void draw(const allcaps_t&);

  // Construct the embedded concrete type.
  template<typename... args_t>
  impl_t(args_t&&... args) : concrete(std::forward<args_t>(args)...) { }

  explicit impl_t(const allcaps_t& concrete_arg);

  std::unique_ptr<
    model_t<my_interface, my_interface2>>
      clone() override;

  bool __has_save() const override;

  void __save(const char* filename, const char* access) override;

  /*template <typename ...Params>
  void print(Params&&... args) override {
    return concrete.print(std::forward<decltype(args)>(args)...);
  }*/

  bool __has_print_2() const override {
    return true;
  }
  void __print_2(const char* text) override {
    return concrete.print_2(std::forward<decltype(text)>(text));
  }

  bool __has_print() const override;

  void __print(const char* text) override;

  void __set_data(const char* text) override;

  void __print_data() override;

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
    // function in model_t.
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

template<>
struct impl_t<forward_t, my_interface, my_interface2>
  : public model_t<my_interface, my_interface2> {

  // Construct the embedded concrete type.
  template<typename... args_t>
  impl_t(args_t&&... args)
    : concrete(std::forward<args_t>(args)...) { }

  explicit impl_t(const forward_t& concrete_arg)
    : concrete(concrete_arg) {}

  std::unique_ptr<
    model_t<my_interface, my_interface2>>
      clone() override {
    // Copy-construct a new instance of impl_t on the heap.
    return std::make_unique<impl_t>(concrete);
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
  void __print_2(const char* text) override {
    return concrete.print_2(std::forward<decltype(text)>(text));
  }

  bool __has_print() const override {
    return true;
  }

  void __print(const char* text) override {
    return concrete.print(std::forward<decltype(text)>(text));
  }

  void __set_data(const char* text) override {
    return concrete.set_data(std::forward<decltype(text)>(text));
  }

  void __print_data() override {
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
    // function in model_t.
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


template<>
struct impl_t<reverse_t, my_interface, my_interface2>
  : public model_t<my_interface, my_interface2> {

  // Construct the embedded concrete type.
  template<typename... args_t>
  impl_t(args_t&&... args)
    : concrete(std::forward<args_t>(args)...) { }

  explicit impl_t(const reverse_t& concrete_arg)
    : concrete(concrete_arg) {}

  std::unique_ptr<
    model_t<my_interface, my_interface2>>
      clone() override {
    // Copy-construct a new instance of impl_t on the heap.
    return std::make_unique<impl_t>(concrete);
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
  void __print_2(const char* text) override {
    return concrete.print_2(std::forward<decltype(text)>(text));
  }

  bool __has_print() const override {
    return true;
  }

  void __print(const char* text) override {
    return concrete.print(std::forward<decltype(text)>(text));
  }

  void __set_data(const char* text) override {
    return concrete.set_data(std::forward<decltype(text)>(text));
  }

  void __print_data() override {
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
    // function in model_t.
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

template<>
struct impl_t<reverse_t, my_interface>
  : public model_t<my_interface> {

  // Construct the embedded concrete type.
  template<typename... args_t>
  impl_t(args_t&&... args)
    : concrete(std::forward<args_t>(args)...) { }

  explicit impl_t(const reverse_t& concrete_arg)
    : concrete(concrete_arg) {}

  std::unique_ptr<
    model_t<my_interface>>
      clone() override {
    // Copy-construct a new instance of impl_t on the heap.
    return std::make_unique<impl_t>(concrete);
  }

#if 0
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

  bool __has_print() const override {
    return true;
  }

  void __print(const char* text) override {
    return concrete.print(std::forward<decltype(text)>(text));
  }

  void __set_data(const char* text) override {
    return concrete.set_data(std::forward<decltype(text)>(text));
  }

  void __print_data() override {
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
    // function in model_t.
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
#endif // 0

  // Our actual data.
  reverse_t concrete;
};

////////////////////////////////////////////////////////////////////////////////
template<typename... typeclass>
struct combined_t {
};

// var_t is an 8-byte type that serves as the common wrapper for the
// type-erasure model_t. It implements move

template<typename... typeclass>
struct var_t {
  //typedef typeclass typeclass_t;

  // Default initializer creates an empty var_t.
  //var_t() = default;

  /*// Allow initialization from a unique_ptr.
  var_t(std::unique_ptr<model_t<typeclass> >&& model) :
    model(std::move(model)) { }

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
  }*/

  // A virtual dtor triggers the dtor in the impl.
  //virtual ~var_t() { }

  /*// The preferred initializer for a var_t. This constructs an impl_t of
  // type_t on the heap, and stores the pointer in a new var_t.
  template<typename type_t, typename... args_t>
  static var_t construct(args_t&&... args) {
    return var_t(std::make_unique<impl_t<typeclass, type_t> >(
      std::forward<args_t>(args)...
    ));
  }

  // Loop over each member function on the interface.
  @meta for(int i = 0; i < @method_count(typeclass); ++i) {

    // Define a has_XXX member function.
    bool @(format("has_%s", @method_name(typeclass, i)))() const {
      @meta if(@sfinae(typeclass::required::@(@method_name(typeclass, i))))
        return true;
      else
        return model->@(__func__)();
    }

    // Declare a non-virtual forwarding function for each interface method.
    @func_decl(@method_type(typeclass, i), @method_name(typeclass, i), args) {
      // Forward to the model's virtual function.
      return model->@(__func__)(std::forward<decltype(args)>(args)...);
    }
  }

  explicit operator bool() const {
    return (bool)model;
  }

  // This is actually a unique_ptr to an impl type. We store a pointer to
  // the base type and rely on model_t's virtual dtor to free the object.
  std::unique_ptr<model_t<typeclass> > model;*/
};

template<>
struct var_t<my_interface> {
  //typedef my_interface typeclass_t;

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
          impl_t<T, my_interface>>
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
    return var_t(std::make_unique<impl_t<type_t, my_interface> >(
      std::forward<args_t>(args)...
    ));
  }

#if 0
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
#endif // 0

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
  std::unique_ptr<model_t<my_interface>> model;
};

template<>
struct var_t<my_interface, my_interface2> {
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
          impl_t<T, my_interface, my_interface2>>
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
    return var_t(std::make_unique<impl_t<type_t, my_interface, my_interface2> >(
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
  // the base type and rely on model_t's virtual dtor to free the object.
  std::unique_ptr<model_t<my_interface, my_interface2>> model;
};

template<>
struct combined_t<my_interface, my_interface2> {
  //typedef my_interface, my_interface2 typeclass_t;

  // Default initializer creates an empty combined_t.
  combined_t() = default;

  template <class T>
  combined_t(std::unique_ptr<T>&& u) :
    my_interface_model(std::move(u)) {
    puts("combined_t{unique_ptr} called");
  }

  template <class T>
  combined_t(const T&& u) :
      my_interface_model(
        std::make_unique<
          impl_t<T, my_interface, my_interface2>>
        (std::forward<const std::decay_t<T>>(u))) {
    puts("combined_t{T} called");
  }

  // Move ctor/assign by default.
  combined_t(combined_t&&) = default;
  combined_t& operator=(combined_t&&) = default;

  // Call clone for copy ctor/assign.
  combined_t(const combined_t& rhs) {
    if(rhs)
      my_interface_model = rhs.my_interface_model->clone();
  }

  combined_t& operator=(const combined_t& rhs) {
    my_interface_model.reset();
    if(rhs)
      my_interface_model = rhs.my_interface_model->clone();
    return *this;
  }

  // A virtual dtor triggers the dtor in the impl.
  virtual ~combined_t() { }

  // The preferred initializer for a combined_t. This constructs an impl_t of
  // type_t on the heap, and stores the pointer in a new combined_t.
  template<typename type_t, typename... args_t>
  static combined_t construct(args_t&&... args) {
    return combined_t(std::make_unique<impl_t<type_t, my_interface, my_interface2> >(
      std::forward<args_t>(args)...
    ));
  }

  bool has_save() const {
    return my_interface_model->__has_save(); // force to true if required
  }

  template <typename ...Params>
  void save(Params&&... args) {
    return my_interface_model->__save(std::forward<decltype(args)>(args)...);
  }

  bool has_print_2() const {
    return my_interface_model->__has_print_2(); // force to true if required
  }
  template <typename ...Params>
  void print_2(Params&&... args) {
    return my_interface_model->__print_2(std::forward<decltype(args)>(args)...);
  }

  bool has_print() const {
    return my_interface_model->__has_print(); // force to true if required
  }

  template <typename ...Params>
  void print(Params&&... args) {
    return my_interface_model->__print(std::forward<decltype(args)>(args)...);
  }

  template <typename ...Params>
  void set_data(Params&&... args) {
    return my_interface_model->__set_data(std::forward<decltype(args)>(args)...);
  }

  template <typename ...Params>
  void print_data(Params&&... args) {
    return my_interface_model->__print_data(std::forward<decltype(args)>(args)...);
  }

  template <typename ...Params>
  void set_interface_data(Params&&... args) {
    return my_interface_model->set_interface_data(std::forward<decltype(args)>(args)...);
  }

  template <typename ...Params>
  void print_interface_data(Params&&... args) {
    return my_interface_model->print_interface_data(std::forward<decltype(args)>(args)...);
  }

  /*void print(const char* text) {
    return model->print(std::forward<decltype(text)>(text));
  }*/

  /*friend void draw(const var_t<my_interface>& d) {
    d.model->do_draw();
  }*/

  void draw(const char* surface) {
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
    return (bool)my_interface_model && (bool)my_interface2_model;
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
  std::unique_ptr<model_t<my_interface>> my_interface_model;
  std::unique_ptr<model_t<my_interface2>> my_interface2_model;
};

////////////////////////////////////////////////////////////////////////////////
// The var_t class template is specialized to include all member functions in
// my_interface. It makes forwarding calls from these to the virtual
// functions in model_t.

// The typedef helps emphasize that we have a single type that encompasses
// multiple impl types that aren't related by inheritance.
typedef combined_t<my_interface, my_interface2> obj_t;
typedef combined_t<my_interface> one_obj_t;

/*template<typename T> int freeGet() = delete;

extern template
 int freeGet<int>();*/

template<
  typename T,
  typename std::enable_if<std::is_same<my_interface, T>::value>::type* = nullptr
>
void draw(const allcaps_t&, const char* surface);

template<
  typename T,
  typename std::enable_if<std::is_same<my_interface, T>::value>::type* = nullptr
>
void draw(const forward_t&, const char* surface);

template<
  typename T,
  typename std::enable_if<std::is_same<my_interface, T>::value>::type* = nullptr
>
void draw(const reverse_t&, const char* surface);

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
