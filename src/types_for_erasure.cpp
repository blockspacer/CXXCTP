// A Circle implementation of the type erasure tactic implemented here:
// https://github.com/TartanLlama/typeclasses/blob/master/typeclass.hpp

//#include "../gems/util.hxx"
#include "types_for_erasure.hpp"

template<>
void template_interface<int, const std::string&>::set_interface_data(const char* text) noexcept {
    interface_data = text;
}

template<>
void template_interface<int, const std::string&>::print_interface_data() const noexcept {
  puts(interface_data.c_str());
}

/*void my_interface2::set_interface_data(const char* text) {
    interface_data = text;
}

void my_interface2::print_interface_data() {
  puts(interface_data.c_str());
}*/

void forward_t::save(forward_t&, const char* filename, const char* access) noexcept {
  puts("forward_t::save called");
}

void forward_t::set_data(forward_t&, const char* text) noexcept {
  forward_t_data = text;
}

void forward_t::print_data(const forward_t&) const noexcept {
  puts(forward_t_data.c_str());
}

void reverse_t::print(const reverse_t&, const char* text) const noexcept {
  int len = strlen(text);
  for(int i = 0; i < len; ++i)
    putchar(text[len - 1 - i]);
  putchar('\n');
}

void reverse_t::set_data(reverse_t&, const char* text) noexcept {
  reverse_t_data = text;
}

void reverse_t::print_data(const reverse_t&) const noexcept {
  puts(reverse_t_data.c_str());
}

void allcaps_t::print(const allcaps_t&, const char* text) const noexcept {
  while(char c = *text++)
    putchar(toupper(c));
  putchar('\n');
}

void allcaps_t::set_data(allcaps_t&,const char* text) noexcept {
  allcaps_t_data = text;
}

void allcaps_t::print_data(const allcaps_t&) const noexcept {
  puts(allcaps_t_data.c_str());
}
