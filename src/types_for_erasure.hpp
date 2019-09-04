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

template<typename S, typename A>
struct template_interface {
  // @gen(extern_func)
  virtual void draw(const char* surface) const = 0;

  ///\note generate function args based on struct template arg names
  // @gen(member_func)
  //S drawTo(A str);

  // @gen(required)
  virtual void print(const char* text) const = 0;

  // @gen(required)
  virtual void print_data() const = 0;

  //virtual void save(const char* filename, const char* access) = 0;
  virtual void save(const char* filename, const char* access) {
    printf("default (unimplemented) save called for %s %s \n", filename, access);
  }

  virtual void set_data(const char* text) = 0;

  /// \note same for all types
  // TODO: pseudo inheritance by code injection
  // @gen(inject_to_all)
  void set_interface_data(const char* text);/* {
    interface_data = text;
  }*/

  /// \note same for all types
  // @gen(inject_to_all)
  void print_interface_data() const;/* {
    puts(interface_data.c_str());
  }*/

  /// \note same for all types
  // @gen(inject_to_all)
  std::string interface_data = "interface_data";
};

struct my_interface2 {
  // @gen(required)
  virtual void do_job(const char* filename, const char* access) = 0;

  // TODO: inject_to_all + static combo
  /// \note expands to accept extra typename
  // @gen(static)
  template <typename T>
  static std::string show(T const &) = delete;

  // TODO:
  //template <typename T, typename A, typename B>
  //static std::string templated_args_show(T const &, A const &, B const &) = delete;

  // @gen(extern_member)
  std::string test_zoo(const std::string& arg);

  // @gen(setter)
  // generates set_get_bar(std::function<std::string()>& func)
  // also add to name switch in set_func<std::string()>(name, [](){})
  std::function<std::string()> get_bar;

  // @gen(setter)
  // generates set_set_bar(std::function<std::string()>& func)
  // also add to name switch in set_func<std::string()>(name, [](){})
  std::function<void(const std::string&)> set_bar;
};

// Print the text in forward order.
// @gen(typeclass_instance(my_interface, my_interface2))
struct forward_t {
  void print_2(const char* text) const {
    puts("print2: ");
    puts(text);
  }

  void print(const char* text) const {
    puts(text);
  }

  void save(const char* filename, const char* access);/* {
    puts("forward_t::save called");
  }*/

  void set_data(const char* text);/* {
    forward_t_data = text;
  }*/

  void print_data() const;/* {
    puts(forward_t_data.c_str());
  }*/

  void do_job(const char* filename, const char* access) {
    printf("do_job %s %s \n", filename, access);
  }

  std::string forward_t_data = "forward_t_data";

  std::string forward_t_bar = "forward_t bar unset";
};

// Print the text in reverse order.
// @gen(typeclass_instance(my_interface<int, std::string>, my_interface2))
struct reverse_t {
  void print_2(const char* text) const {
    puts("print2: ");
    puts(text);
  }

  void print(const char* text) const;/* {
    int len = strlen(text);
    for(int i = 0; i < len; ++i)
      putchar(text[len - 1 - i]);
    putchar('\n');
  }*/

  void set_data(const char* text);/* {
    reverse_t_data = text;
  }*/

  void print_data() const;/* {
    puts(reverse_t_data.c_str());
  }*/

  /*void do_job(const char* filename, const char* access) {
    printf("do_job %s %s \n", filename, access);
  }*/

  std::string reverse_t_data = "reverse_t_data";

  std::string reverse_t_bar = "reverse_t bar unset";
};

// Print the text with caps.
// @gen(typeclass_instance(my_interface<std::string, std::string>, my_interface2))
struct allcaps_t {
  void print_2(const char* text) const {
    puts("print2: ");
    puts(text);
  }

  void print(const char* text) const;/* {
    while(char c = *text++)
      putchar(toupper(c));
    putchar('\n');
  }*/

  void set_data(const char* text);/* {
    allcaps_t_data = text;
  }*/

  void print_data() const;/* {
    puts(allcaps_t_data.c_str());
  }*/

  /*void do_job(const char* filename, const char* access) {
    printf("do_job %s %s \n", filename, access);
  }*/

  std::string allcaps_t_data = "allcaps_t_data";

  std::string allcaps_t_bar = "allcaps_t bar unset";
};
