#include "example_make_reflect.hpp"

#include "cxxctp_macros.hpp"

#include <vector>
#include <string>
#include <iostream>

struct
$apply(make_reflect)
SomeStructName {
 public:
  SomeStructName() {
    // ...
  };
  $attr(someattr1;reflectable;someattr3) int foo() {
    int i = 123;
    return i;
  }
 private:
  int bar() {
    int i = 123;
    return i;
  }
  $attr(someattr1;reflectable;someattr3) inline const int baz() {
    int i = 123;
    return i;
  }
 public:
  $attr(someattr1;reflectable) int m_foo;
  const int* m_bar = nullptr;
  $attr(reflectable;someattr2) std::vector<std::string> m_VecStr1{};
 private:
  const int m_bar2 = 2;
  $attr(reflectable) std::vector<std::string> m_VecStr2;
};
