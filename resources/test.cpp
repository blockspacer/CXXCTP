//#pragma annotate my {gen};{funccall};make_interface

#include <vector>
#include <string>

#pragma comment(user, "user defined pragma comment")

#define GEN_CAT(a, b) GEN_CAT_I(a, b)
#define GEN_CAT_I(a, b) GEN_CAT_II(~, a ## b)
#define GEN_CAT_II(p, res) res

#define GEN_UNIQUE_NAME(base) GEN_CAT(base, __COUNTER__)

#define $attr(...) \
  __attribute__((annotate("{gen};{attr};" #__VA_ARGS__ )))

// eval executes code
// unlike exec, eval may use `#include` e.t.c.
// no return value
#define $eval(...) \
  /* generate definition required to use __attribute__ */ \
  __attribute__((annotate("{gen};{eval};" __VA_ARGS__))) \
  int GEN_UNIQUE_NAME(__gen_tmp);

// embed executes code and
// returns (optional) source code modification
#define $embed(...) \
  /* generate definition required to use __attribute__ */ \
  __attribute__((annotate("{gen};{embed};" #__VA_ARGS__))) \
  int GEN_UNIQUE_NAME(__gen_tmp);

// shortened embed syntax
// param1 - returns (optional) source code modification
#define $set_embed(RETVAL, ...) \
  /* generate definition required to use __attribute__ */ \
  __attribute__((annotate( \
      "{gen};{embed};" \
      "[&clangMatchResult, &clangRewriter, &clangDecl]() {" \
        #__VA_ARGS__ \
        "return new llvm::Optional<std::string>{" \
          #RETVAL \
          "};" \
      "}();" \
    ))) \
  int GEN_UNIQUE_NAME(__gen_tmp);

#ifdef CLANG_ENABLED
// eval that
// replaces itself with passed arguments
#define $export(...) \
  __VA_ARGS__ \
  __attribute__((annotate("{gen};{export};" #__VA_ARGS__ ))) \
  int GEN_UNIQUE_NAME(__gen_tmp);
#else
#define $export(...) __VA_ARGS__
#endif

// TODO
/*#define $genonly(...) \
  __VA_ARGS__ \
  __attribute__((annotate("{gen};{export};" #__VA_ARGS__ ))) \
  int GEN_UNIQUE_NAME(__gen_tmp);
$genonly()*/

  $export (
static int resultSomeInt = 2345;
  )

$export(
  static int getSomeInt() {
    return resultSomeInt;
  }
)

static int someInt = getSomeInt();

// exec is similar to embed,
// but returns empty source code modification
#define $exec(...) \
  /* generate definition required to use __attribute__ */ \
  __attribute__((annotate( \
      "{gen};{embed};" \
      "[&clangMatchResult, &clangRewriter, &clangDecl]() {" \
        #__VA_ARGS__ \
        "return new llvm::Optional<std::string>{\"\"};" \
      "}();" \
    ))) \
  int GEN_UNIQUE_NAME(__gen_tmp);

/*$exec(
  printf("getSomeInt = %i\n", getSomeInt());
)*/

//#define eval_code1 \
//  printf("evalgfgbfbgbfgb\n"); \
//  #include <cling/Interpreter/Interpreter.h>

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
      SourceLocation startLoc = clangDecl->getLocStart();
      SourceLocation endLoc = clangDecl->getLocEnd();
      if( startLoc.isMacroID() ) {
          // Get the start/end expansion locations
          std::pair< SourceLocation, SourceLocation > expansionRange =
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

/*#define $interface \
  __attribute__((annotate("{gen};{funccall};make_interface")))

#define $removefuncbody \
  __attribute__((annotate("{gen};{funccall};make_removefuncbody")))

#define $combined \
  __attribute__((annotate("{gen};{funccall};make_interface;make_removefuncbody")))
*/

#define $apply(...) \
  __attribute__((annotate("{gen};{funccall};" #__VA_ARGS__)))

class
$apply(make_interface;
  make_removefuncbody)
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
