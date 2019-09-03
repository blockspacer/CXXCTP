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

struct my_interface {
  // @gen(extern)
  virtual void draw(const char* surface) const = 0;

  // @gen(required)
  virtual void print(const char* text) const = 0;

  // @gen(required)
  virtual void print_data() const = 0;

  virtual void save(const char* filename, const char* access) = 0;

  virtual void set_data(const char* text) = 0;

  // TODO: pseudo inheritance by code injection
  // @gen(inject)
  void set_interface_data(const char* text);/* {
    interface_data = text;
  }*/
  // @gen(inject)
  void print_interface_data() const;/* {
    puts(interface_data.c_str());
  }*/
  // @gen(inject)
  std::string interface_data = "interface_data";
};

struct my_interface2 {
  // @gen(required)
  virtual void do_job(const char* filename, const char* access) = 0;
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
};

// Print the text in reverse order.
// @gen(typeclass_instance(my_interface, my_interface2))
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
};

// Print the text with caps.
// @gen(typeclass_instance(my_interface, my_interface2))
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
};
