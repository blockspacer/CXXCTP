#pragma once

//#include <iterator> // see https://vjordan.info/log/fpga/c-enum-range-based-for-loop.html
#include <array>
#include <memory>

namespace cxxctp {
namespace generated {

// _tc_model_t is the base class for _tc_impl_t. _tc_impl_t has the storage for the
// object of type_t. _tc_model_t has a virtual dtor to trigger _tc_impl_t's dtor.
// _tc_model_t has a virtual clone function to copy-construct an instance of
// _tc_impl_t into heap memory, which is returned via unique_ptr. _tc_model_t has
// a pure virtual function for each method in the interface class typeclass.
//#if 0
template<typename... typeclass>
struct _tc_model_t /*: public common__tc_model_t*/ {
  //typedef typeclass... typeclass_type_t;
  virtual ~_tc_model_t() noexcept { }

  virtual std::unique_ptr<_tc_model_t>
    clone() noexcept = 0;

  virtual std::unique_ptr<_tc_model_t>
    move_clone() noexcept = 0;

  virtual std::string
    get_GUID() noexcept = 0;

  // Loop over each member function on the interface.
  /*@meta for(int i = 0; i < @method_count(typeclass); ++i) {

    @meta std::string func_name = @method_name(typeclass, i);

    // Declare a "has_" function.
    virtual bool @(format("has_%s", func_name.c_str()))() const = 0;

    // Declare a pure virtual function for each interface method.
    virtual @func_decl(@method_type(typeclass, i), func_name, args) = 0;
  }*/
};
//#endif // 0

template<typename type_t, typename... typeclass>
struct _tc_impl_t : public _tc_model_t<typeclass...> {
  typedef type_t val_type_t;

  // Construct the embedded concrete type.
  /*template<typename... args_t>
  _tc_impl_t(args_t&&... args) : concrete(std::forward<args_t>(args)...) { }

  std::unique_ptr<_tc_model_t<typeclass> > clone() override {
    // Copy-construct a new instance of _tc_impl_t on the heap.
    return std::make_unique<_tc_impl_t>(concrete);
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
  //type_t concrete;
};

#if 0
// var_t is an 8-byte type that serves as the common wrapper for the
// type-erasure _tc_model_t. It implements move
template<typename... typeclass>
struct var_t {
  //typedef typeclass typeclass_t;

  // Default initializer creates an empty var_t.
  //var_t() = default;

  /*// Allow initialization from a unique_ptr.
  var_t(std::unique_ptr<_tc_model_t<typeclass> >&& model) :
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

  /*// The preferred initializer for a var_t. This constructs an _tc_impl_t of
  // type_t on the heap, and stores the pointer in a new var_t.
  template<typename type_t, typename... args_t>
  static var_t construct(args_t&&... args) {
    return var_t(std::make_unique<_tc_impl_t<typeclass, type_t> >(
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
  // the base type and rely on _tc_model_t's virtual dtor to free the object.
  std::unique_ptr<_tc_model_t<typeclass> > model;*/
};
#endif // 0

template<typename... typeclass>
struct _tc_combined_t {
};

// see https://github.com/joboccara/NamedType/blob/093e597e4d1d51614bc729fe2382c2db8925de75/named_type_impl.hpp#L18
template<typename T>
using IsNotReference = typename std::enable_if<!std::is_reference<T>::value, void>::type;

/*int constexpr strlength(const char* str)
{
    return *str ? 1 + strlength(str + 1) : 0;
}

size_t constexpr Hash(const char *first)
{   // FNV-1a hash function
    const size_t FNVoffsetBasis = 14695981039346656037ULL;
    const size_t FNVprime = 1099511628211ULL;
    const size_t count = strlength(first);
    size_t val = FNVoffsetBasis;
    for (size_t next = 0; next < count; ++next)
    {
        val ^= (size_t)first[next];
        val *= FNVprime;
    }
    return val;
}*/

/*#ifdef COMPILE_DLL
#define CXXCTP_EXPORT __declspec( dllexport )
#else
#define CXXCTP_EXPORT __declspec( dllimport )
#endif*/

} // namespace cxxctp
} // namespace generated
