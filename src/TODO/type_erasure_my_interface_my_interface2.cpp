// A Circle implementation of the type erasure tactic implemented here:
// https://github.com/TartanLlama/typeclasses/blob/master/typeclass.hpp

//#include "../gems/util.hxx"
#include "type_erasure_my_interface.hpp"

void my_interface::set_interface_data(const char* text) {
    interface_data = text;
}

void my_interface::print_interface_data() {
  puts(interface_data.c_str());
}

void forward_t::save(const char* filename, const char* access) {
  puts("forward_t::save called");
}

void forward_t::set_data(const char* text) {
  forward_t_data = text;
}

void forward_t::print_data() {
  puts(forward_t_data.c_str());
}

void reverse_t::print(const char* text) {
  int len = strlen(text);
  for(int i = 0; i < len; ++i)
    putchar(text[len - 1 - i]);
  putchar('\n');
}

void reverse_t::set_data(const char* text) {
  reverse_t_data = text;
}

void reverse_t::print_data() {
  puts(reverse_t_data.c_str());
}

void allcaps_t::print(const char* text) {
  while(char c = *text++)
    putchar(toupper(c));
  putchar('\n');
}

void allcaps_t::set_data(const char* text) {
  allcaps_t_data = text;
}

void allcaps_t::print_data() {
  puts(allcaps_t_data.c_str());
}

//namespace obj_t::typeclass_t {
//  extern void draw(const allcaps_t&, const char* surface);
//}

//namespace obj_t::typeclass_t {
//  extern void draw(const forward_t&, const char* surface);
//}

//namespace obj_t::typeclass_t {
  /*extern template
   void draw<my_interface, my_interface2>(const reverse_t&, const char* surface);*/
//}

namespace cxxctp {
namespace generated {

extern template
 /*explicit*/ void draw<my_interface>
  (const allcaps_t&, const char* surface);

extern template
 /*explicit*/ void draw<my_interface>
  (const allcaps_t&, const char* surface);

extern template
 /*explicit*/ void draw<my_interface>
  (const reverse_t&, const char* surface);

void model_t<my_interface, my_interface2>::set_interface_data(const char* text) {
  interface_data = text;
}

void model_t<my_interface, my_interface2>::print_interface_data() {
  auto out = std::string("interface_data: ") + interface_data;
  puts(out.c_str());
}

impl_t<allcaps_t, my_interface, my_interface2>::impl_t(const allcaps_t& concrete_arg)
  : concrete(concrete_arg) {}

std::unique_ptr<model_t<my_interface, my_interface2>>
 impl_t<allcaps_t, my_interface, my_interface2>::clone() {
  // Copy-construct a new instance of impl_t on the heap.
  return std::make_unique<impl_t>(concrete);
}

bool impl_t<allcaps_t, my_interface, my_interface2>::__has_save() const {
  return false;
}

void impl_t<allcaps_t, my_interface, my_interface2>::__save(const char* filename, const char* access) {
  // TODO: noexcept
  throw std::runtime_error("allcaps_t::save not implemented");
}

/*template <typename ...Params>
void print(Params&&... args) override {
  return concrete.print(std::forward<decltype(args)>(args)...);
}*/

bool impl_t<allcaps_t, my_interface, my_interface2>::__has_print() const {
  return true;
}

void impl_t<allcaps_t, my_interface, my_interface2>::__print(const char* text) {
  return concrete.print(std::forward<decltype(text)>(text));
}

void impl_t<allcaps_t, my_interface, my_interface2>::__set_data(const char* text) {
  return concrete.set_data(std::forward<decltype(text)>(text));
}

void impl_t<allcaps_t, my_interface, my_interface2>::__print_data() {
  return concrete.print_data();
}

void impl_t<allcaps_t, my_interface, my_interface2>::__draw(const char* surface) const {
  return draw<my_interface>(concrete, surface);
}

// ====

void impl_t<forward_t, my_interface, my_interface2>::__draw(const char* surface) const {
  return draw<my_interface>(concrete, surface);
}

// ====

void impl_t<reverse_t, my_interface, my_interface2>::__draw(const char* surface) const {
  return draw<my_interface>(concrete, surface);
}

// ====

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

/*template<>
void impl_t<allcaps_t, my_interface>::draw(const allcaps_t &)
{

}*/

} // namespace cxxctp
} // namespace generated
