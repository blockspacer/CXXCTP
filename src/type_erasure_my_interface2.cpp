// A Circle implementation of the type erasure tactic implemented here:
// https://github.com/TartanLlama/typeclasses/blob/master/typeclass.hpp

//#include "../gems/util.hxx"
#include "type_erasure_my_interface2.hpp"

namespace cxxctp {
namespace generated {

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

/*void model_t<my_interface2>::set_interface_data(const char* text) {
  interface_data = text;
}

void model_t<my_interface2>::print_interface_data() {
  auto out = std::string("interface_data: ") + interface_data;
  puts(out.c_str());
}*/

impl_t<allcaps_t, my_interface2>::impl_t(const allcaps_t& concrete_arg)
  : concrete(concrete_arg) {}

std::unique_ptr<model_t<my_interface2>>
 impl_t<allcaps_t, my_interface2>::clone() {
  // Copy-construct a new instance of impl_t on the heap.
  return std::make_unique<impl_t>(concrete);
}

bool impl_t<allcaps_t, my_interface2>::__has_do_job() const {
  return false;
}

void impl_t<allcaps_t, my_interface2>::__do_job
  (const char* filename, const char* access) {
    // TODO: noexcept
    throw std::runtime_error("allcaps_t::do_job not implemented");
}

/*template <typename ...Params>
void print(Params&&... args) override {
  return concrete.print(std::forward<decltype(args)>(args)...);
}*/

/*
bool impl_t<allcaps_t, my_interface2>::__has_print() const {
  return true;
}

void impl_t<allcaps_t, my_interface2>::__print(const char* text) {
  return concrete.print(std::forward<decltype(text)>(text));
}

void impl_t<allcaps_t, my_interface2>::__set_data(const char* text) {
  return concrete.set_data(std::forward<decltype(text)>(text));
}

void impl_t<allcaps_t, my_interface2>::__print_data() {
  return concrete.print_data();
}

void impl_t<allcaps_t, my_interface2>::__draw(const char* surface) const {
  return draw<my_interface2>(concrete, surface);
}

// ====

void impl_t<forward_t, my_interface2>::__draw(const char* surface) const {
  return draw<my_interface2>(concrete, surface);
}

// ====

void impl_t<reverse_t, my_interface2>::__draw(const char* surface) const {
  return draw<my_interface2>(concrete, surface);
}

// ====
*/

} // namespace cxxctp
} // namespace generated
