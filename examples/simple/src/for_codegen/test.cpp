/*#pragma comment(user, "user defined pragma comment")
void foo() {
#pragma omp parallel
{
  while(true){};
}
#pragma omp parallel for
   for(;;){}
}*/

//#pragma annotate my {gen};{funccall};make_interface

#include "test.hpp"
#include "cxxctp_macros.hpp"

#include <vector>
#include <string>
#include <iostream>

//#pragma comment(user, "user defined pragma comment")

  $export (
static int resultSomeInt = 2345;
  )

$export(
  static int getSomeInt() {
    return resultSomeInt;
  }
)

static int someInt = getSomeInt();

$exec(
  printf("getSomeInt() == resultSomeInt %i\n",
    getSomeInt() == resultSomeInt);
  //assert(getSomeInt() == resultSomeInt);
  if(getSomeInt() != resultSomeInt) {
    throw "throwed getSomeInt() != resultSomeInt";
  }
  printf("getSomeInt() != resultSomeInt %i\n",
    getSomeInt() != resultSomeInt);
)

/*$exec(
  printf("getSomeInt = %i\n", getSomeInt());
)*/

$eval("printf(\"asdasdasdasdasdds\\n\");printf(\"sggdfgdfg\\n\");")

$eval("#include <cling/Interpreter/Interpreter.h>")

$eval("#include <optional>")

$eval("auto globVar = "
      "std::optional<std::string>"
      "{\"asdasdcout123123\\n\"};")

$eval("std::cout << globVar.value();")

$exec(
  printf("execkjljlk\n");
  printf("execasdasd\n");
)

$set_embed("set_embed103",
  printf("set_embed101\n");
  printf("set_embed102\n");
)

$embed(
  [&clangMatchResult, &clangRewriter, &clangDecl]() {
    printf("embed01\n");
    printf("embed02\n");
    return new llvm::Optional<std::string>{"embed03"};
  }();
)

void fooboo() {
  $embed(
    []() {
      printf("embed001\n");
      printf("embed002\n");
      return new llvm::Optional<std::string>{"embed003"};
    }();
  )
}

void foozoo() {
  $embed(
    [&clangMatchResult, &clangRewriter, &clangDecl]() {
      printf("embed2001\n");
      printf("embed2002\n");
      clang::SourceLocation startLoc = clangDecl->getLocStart();
      clang::SourceLocation endLoc = clangDecl->getLocEnd();
      if( startLoc.isMacroID() ) {
          // Get the start/end expansion locations
          std::pair< clang::SourceLocation, clang::SourceLocation > expansionRange =
                   clangRewriter.getSourceMgr().getImmediateExpansionRange( startLoc );

          // We're just interested in the start location
          startLoc = expansionRange.first;
          endLoc = expansionRange.second;
      }
      clangRewriter.ReplaceText(
        clang::SourceRange(startLoc, endLoc),
        "embed2003");

      return new llvm::Optional<std::string>();
    }();
  )
}

/*class __attribute__((annotate("{gen};{eval};"))) tryIt
{

};*/
//#pragma clang attribute push(__attribute__((annotate("{gen};{eval};"))), apply_to=function)
//void g() {}
//#pragma clang attribute pop

//#pragma clang attribute push(__attribute__((annotate("{gen};{eval};"))), apply_to=function)
//#pragma clang attribute pop

class
  $apply(
    make_interface;
    make_removefuncbody;make_reflect
  )
SomeInterfaceName {
  virtual ~SomeInterfaceName() = 0;
  /*int    f   (   )   {     // {}
    int i = 6;
    {
      // {
      // }
    }
    return i;
  };*/
  int foo();
  virtual void foobar(int& arg1) = 0;
  virtual inline void zoobar(int& arg2);
  //int m_bar;
  //int m_bar2 = 2;
};

struct
  $apply(
    make_reflect
  )
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

enum Color : uint16_t { RED = 2, BLUE = 4, GREEN = 8 };

enum class ColorClass { RED = 2, BLUE = 4, GREEN = 8 };

enum ShapeKindSimple {

  // Convex shapes, see ConvexBegin and ConvexEnd below.
  Box = 0,
  Sphere = 1,

  // Non-convex shapes.
  Donut = 2,
  Banana = 3,

  COUNT = Banana + 1,

  // Non-reflected aliases.
  ConvexBegin = Box,
  ConvexEnd = Sphere + 1,

  // TODO: generate TOTAL
};

/*class EnumValue {
public:
  virtual const char* ToString() = 0;
  virtual ~EnumValue() {}
  virtual operator int() = 0;
};*/

// https://www.reddit.com/r/gamedev/comments/3lh0ba/using_clang_to_generate_c_reflection_data/
/*class MetaProperty {
public:
  //virtual const char* ToString(EnumValue value) = 0;
  virtual ~MetaProperty() {}

  //static const char* const* _names() = 0;
  //static const int* _values() = 0;
  virtual const char* ToString() = 0;
  virtual const MetaProperty& operator =(int dummy)  = 0;
  //virtual operator int() = 0;
  //virtual MetaProperty& operator =() = 0;
};*/
