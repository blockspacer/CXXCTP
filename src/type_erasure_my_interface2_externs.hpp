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
//#include "type_erasure_my_interface2.hpp"

namespace cxxctp {
namespace generated {

////////////////////////////////////////////////////////////////////////////////
// The var_t class template is specialized to include all member functions in
// my_interface. It makes forwarding calls from these to the virtual
// functions in _tc_model_t.

// The typedef helps emphasize that we have a single type that encompasses
// multiple impl types that aren't related by inheritance.
typedef _tc_model_t<my_interface2> my_interface2_model_t;
typedef _tc_combined_t<my_interface2> my_interface2_obj_t;
template<typename T> using my_interface2_impl_t = _tc_impl_t<T, my_interface2>;

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

template<typename A,
typename B,
typename C,
typename std::enable_if<std::is_same<my_interface2, A>::value>::type* = nullptr>
std::string show(const B& arg1, C const & arg2) {
  return my_interface2_impl_t<B>::show(arg1, arg2);
}

template<>
struct _tc_registry<my_interface2> {
  static constexpr size_t size = 4;

  template<typename concrete>
  static size_t getTypeIndex() noexcept;
};

template<>
size_t _tc_registry<my_interface2>::
    getTypeIndex<std::reference_wrapper<allcaps_t>>() noexcept;

template<>
size_t _tc_registry<my_interface2>::
    getTypeIndex<allcaps_t>() noexcept;

template<>
size_t _tc_registry<my_interface2>::
    getTypeIndex<reverse_t>() noexcept;

template<>
size_t _tc_registry<my_interface2>::
    getTypeIndex<forward_t>() noexcept;

} // namespace cxxctp
} // namespace generated
