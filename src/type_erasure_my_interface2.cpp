// A Circle implementation of the type erasure tactic implemented here:
// https://github.com/TartanLlama/typeclasses/blob/master/typeclass.hpp

//#include "../gems/util.hxx"
#include "type_erasure_my_interface2.hpp"
#include "type_erasure_my_interface2_externs.hpp"

namespace cxxctp {
namespace generated {

template <>
allcaps_t& _tc_model_t<my_interface2>::ref_concrete<allcaps_t>() noexcept {
  return static_cast<_tc_impl_t<allcaps_t, my_interface2>*>(this)
    ->concrete;
}

template <>
std::reference_wrapper<allcaps_t>& _tc_model_t<my_interface2>::ref_concrete<std::reference_wrapper<allcaps_t>>() noexcept {
  /// \note passes ref, not data!
  return static_cast<_tc_impl_t<std::reference_wrapper<allcaps_t>, my_interface2>*>(this)
    ->concrete;
}

template <>
reverse_t& _tc_model_t<my_interface2>::ref_concrete<reverse_t>() noexcept {
  return static_cast<_tc_impl_t<reverse_t, my_interface2>*>(this)
    ->concrete;
}

template <>
forward_t& _tc_model_t<my_interface2>::ref_concrete<forward_t>() noexcept {
  return static_cast<_tc_impl_t<forward_t, my_interface2>*>(this)
    ->concrete;
}

#if 0
extern template
 /*explicit*/ void draw<my_interface2>
  (const allcaps_t&, const char* surface);

extern template
 /*explicit*/ void draw<my_interface2>
  (const allcaps_t&, const char* surface);

extern template
 /*explicit*/ void draw<my_interface2>
  (const reverse_t&, const char* surface);
#endif // 0

/*void _tc_model_t<my_interface2>::set_interface_data(const char* text) {
  interface_data = text;
}

void _tc_model_t<my_interface2>::print_interface_data() {
  auto out = std::string("interface_data: ") + interface_data;
  puts(out.c_str());
}*/

_tc_impl_t<allcaps_t, my_interface2>::_tc_impl_t(const allcaps_t& concrete_arg) noexcept
  : concrete(concrete_arg) {}

std::unique_ptr<_tc_model_t<my_interface2>>
 _tc_impl_t<allcaps_t, my_interface2>::clone() noexcept {
  // Copy-construct a new instance of _tc_impl_t on the heap.
  return std::make_unique<_tc_impl_t>(concrete);
}

bool _tc_impl_t<allcaps_t, my_interface2>::__has_do_job() const noexcept {
  return false;
}

void _tc_impl_t<allcaps_t, my_interface2>::__do_job
  (const char* filename, const char* access) noexcept {
    std::cout << "called __do_job for "
                 "allcaps_t "
                 "with allcaps_t_data = "
                  << concrete.allcaps_t_data << std::endl;

    // TODO: noexcept
    //throw std::runtime_error("allcaps_t::do_job not implemented");
}

template <>
void _tc_combined_t<my_interface2>::set_set_bar<allcaps_t>
    (std::function<void(allcaps_t&, const std::string&)> arg) noexcept {
  if(!my_interface2_model) {
    //throw std::runtime_error("my_interface2_model not set");
    std::terminate();
  }
  return static_cast<_tc_impl_t<allcaps_t, my_interface2>*>(my_interface2_model.get())
    ->__set_set_bar(std::forward<decltype(arg)>(arg));
}

template <>
void _tc_combined_t<my_interface2>::set_set_bar<reverse_t>
    (std::function<void(reverse_t&, const std::string&)> arg) noexcept {
  if(!my_interface2_model) {
    //throw std::runtime_error("my_interface2_model not set");
    std::terminate();
  }
  return static_cast<_tc_impl_t<reverse_t, my_interface2>*>(my_interface2_model.get())
    ->__set_set_bar(std::forward<decltype(arg)>(arg));
}

template <>
void _tc_combined_t<my_interface2>::set_set_bar<forward_t>
    (std::function<void(forward_t&, const std::string&)> arg) noexcept {
  if(!my_interface2_model) {
    //throw std::runtime_error("my_interface2_model not set");
    std::terminate();
  }
  return static_cast<_tc_impl_t<forward_t, my_interface2>*>(my_interface2_model.get())
    ->__set_set_bar(std::forward<decltype(arg)>(arg));
}

template <>
void _tc_combined_t<my_interface2>::set_get_bar<allcaps_t>
    (std::function<std::string(allcaps_t&)> arg) noexcept {
  if(!my_interface2_model) {
    //throw std::runtime_error("my_interface2_model not set");
    std::terminate();
  }
  return static_cast<_tc_impl_t<allcaps_t, my_interface2>*>(my_interface2_model.get())
    ->__set_get_bar(std::forward<decltype(arg)>(arg));
}

template <>
void _tc_combined_t<my_interface2>::set_get_bar<reverse_t>
    (std::function<std::string(reverse_t&)> arg) noexcept {
  if(!my_interface2_model) {
    //throw std::runtime_error("my_interface2_model not set");
    std::terminate();
  }
  return static_cast<_tc_impl_t<reverse_t, my_interface2>*>(my_interface2_model.get())
    ->__set_get_bar(std::forward<decltype(arg)>(arg));
}

template <>
void _tc_combined_t<my_interface2>::set_get_bar<forward_t>
    (std::function<std::string(forward_t&)> arg) noexcept {
  if(!my_interface2_model) {
    //throw std::runtime_error("my_interface2_model not set");
    std::terminate();
  }
  return static_cast<_tc_impl_t<forward_t, my_interface2>*>(my_interface2_model.get())
    ->__set_get_bar(std::forward<decltype(arg)>(arg));
}

std::string _tc_combined_t<my_interface2>::test_zoo(const std::string &arg) noexcept {
  //return my_interface2_model->test_zoo<reverse_t>(arg);
  return my_interface2_model->__test_zoo(arg);
}

/*template <typename ...Params>
void print(Params&&... args) override final {
  return concrete.print(std::forward<decltype(args)>(args)...);
}*/

/*
bool _tc_impl_t<allcaps_t, my_interface2>::__has_print() const {
  return true;
}

void _tc_impl_t<allcaps_t, my_interface2>::__print(const char* text) {
  return concrete.print(std::forward<decltype(text)>(text));
}

void _tc_impl_t<allcaps_t, my_interface2>::__set_data(const char* text) {
  return concrete.set_data(std::forward<decltype(text)>(text));
}

void _tc_impl_t<allcaps_t, my_interface2>::__print_data() {
  return concrete.print_data();
}

void _tc_impl_t<allcaps_t, my_interface2>::__draw(const char* surface) const {
  return draw<my_interface2>(concrete, surface);
}

// ====

void _tc_impl_t<forward_t, my_interface2>::__draw(const char* surface) const {
  return draw<my_interface2>(concrete, surface);
}

// ====

void _tc_impl_t<reverse_t, my_interface2>::__draw(const char* surface) const {
  return draw<my_interface2>(concrete, surface);
}

// ====
*/

template<>
size_t _tc_registry<my_interface2>::
    getTypeIndex<allcaps_t>() noexcept {
 constexpr size_t ret = 0;
 static_assert(ret < std::numeric_limits<size_t>::max(),
    "Registered too many types in"
    " _tc_registry<my_interface2>");
  return ret;
}

template<>
size_t _tc_registry<my_interface2>::
    getTypeIndex<reverse_t>() noexcept {
 constexpr size_t ret = 1;
 static_assert(ret < std::numeric_limits<size_t>::max(),
    "Registered too many types in"
    " _tc_registry<my_interface2>");
  return ret;
}

template<>
size_t _tc_registry<my_interface2>::
    getTypeIndex<forward_t>() noexcept {
 constexpr size_t ret = 2;
 static_assert(ret < std::numeric_limits<size_t>::max(),
    "Registered too many types in"
    " _tc_registry<my_interface2>");
  return ret;
}

} // namespace cxxctp
} // namespace generated
