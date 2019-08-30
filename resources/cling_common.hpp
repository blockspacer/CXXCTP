#pragma once

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

//#define eval_code1 \
//  printf("evalgfgbfbgbfgb\n"); \
//  #include <cling/Interpreter/Interpreter.h>

/*#define $interface \
  __attribute__((annotate("{gen};{funccall};make_interface")))

#define $removefuncbody \
  __attribute__((annotate("{gen};{funccall};make_removefuncbody")))

#define $combined \
  __attribute__((annotate("{gen};{funccall};make_interface;make_removefuncbody")))
*/

#define $apply(...) \
  __attribute__((annotate("{gen};{funccall};" #__VA_ARGS__)))
