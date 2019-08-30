# About CXXCTP (CXX compile-time programming)
CXXCTP is a transpiler that extends C++ for new introspection, reflection and compile-time execution.

CXXCTP don`t use predefined set of code transformations. Users can share C++ scripts for source code transformation.

Suppose some big company shared to opensource community usefull scripts like `interface.cxx` and `enum_to_json.cxx`. Just place that scripts into `ctp_scripts` folder to use them in your project.

Note: this project is provided as is, without any warranty (see License).

## Features
+ C++ as compile-time scripting language (https://github.com/derofim/cling-cmake)
+ Jinja support (https://github.com/jinja2cpp/Jinja2Cpp)
+ Ability to modify source files (implement metaclasses, transpile from C++X to C++Y e.t.c.)
+ Ability to create new files (separate generated class to .hpp and .cpp, e.t.c.)
+ Ability to check source files (implement style checks, design patterns, e.t.c.)

TODO:
+ DSL integration
+ Better JSON support
+ Better docs support

## Project status
In development, see test.cpp and app_loop.cpp fo usage examples

Currently supports only linux.

Note that you can run linux containers under windows/mac/e.t.c.

## in-dev now
JSON support
Safer CPP support

## ctp_scripts folder
TODO

## Run as commandline tool & compile_commands.json support / CMake integration
TODO

## Tutorials
TODO

## Generate docs website
TODO

## Integrate asan / e.t.c.
TODO

## Unit tests & CI/CD
TODO

## Benchmark (https://github.com/CathalT/Cerializer#parse--string---json-dom-object---c-struct-)
TODO

## Try it online (Jypiter/wandbox)

## Provide header with common defines
TODO

## Docker / Vagrant
TODO
https://hub.docker.com/r/codible/clang_dev/

## Better args parser & lines/spaces support ( make_interface(    outfile = filepath  ,   DISABLE   =   ${cling_var}) )
TODO

## Pass common reflected info to jinja for all decls (enum/class/e.t.c.)
TODO

## Refactor
TODO

## exception stack traces (backward-cpp, ...)
TODO

## Log & error reporting
TODO

## Change detection (watcher like https://github.com/Manu343726/siplasplas/tree/master/examples/fswatch ) & hot reload
TODO

## Articles in media (medium, twitter, reddit, ...)
TODO

## DEPENDENCIES
```
bash scripts/install_cmake.sh
# than build https://jinja2cpp.dev/docs/build_and_install.html with variant_CONFIG_SELECT_VARIANT=variant_VARIANT_NONSTD
```

### Clone code
```
git submodule sync --recursive
git submodule update --init --recursive --depth 50
# or
git submodule update --force --recursive --init --remote
```

## How to build
```
BEFORE setup.sh:
sudo apt-get update && sudo apt-get upgrade
sudo apt-get install clang libstdc++6
sudo update-alternatives --config c++
sudo update-alternatives --config cc
ldconfig
export CC=clang
export CXX=clang++
```

```
bash scripts/setup.sh
```

```
export CC=gcc
export CXX=g++
rm -rf build
mkdir build
cd build
cmake -DENABLE_CLING=TRUE -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . -- -j6
./CXXCTP
```

OR under gdb:
```
rm -rf *generated* ; clear && clear ; gdb ./CXXCTP -ex "run" -ex "bt" -ex "q"
```

## Motivation
Why wouldn't you just extend clang since it also provides some experimental features (modules for instance)?

Clang is a compiler while this project is a transpiler, that transforms code to standardized c++ code without the need to modify llvm/assembly.

Because tool output is C++ code, you can compile transpiled code using emscripten, use static code analizers, run code inside cling e.t.c.

CXXCTP allows you to create and share scripts for
+ source code check (like codestyle validation)
+ source code transformation (like alphabetical sort of all public functions inside some class)
+ compile-time programming (like retrieve source code modification rules from remote server and save them in some folder)
+ e.t.c.

## Writing code that writes code
You can write custom C++ scripts for source code transformation or use existing ones.

CXXCTP loads all C++ scripts from ctp_scripts folder.

You can use `#include`, use filesystem, access internet, e.t.c. in C++ scripts.

## About CXXCTP code annotations

You can use C++ annotations to tell CXXCTP what actions it must execute.

Suppose we want to morph class into interface:

```
// Source
class SomeInterfaceName {
  int foo1() {
    // ...
  };
  int foo();
  virtual void foobar(int& arg1) = 0;
  virtual void zoobar(int& arg2);
  virtual ~SomeInterfaceName() = 0;
};

// <== will be changed into ==>

// Result
class SomeInterfaceName {
  virtual int foo1() = 0;
  virtual int foo() = 0;
  virtual void foobar(int& arg1) = 0;
  virtual void zoobar(int& arg2) = 0;
  virtual ~SomeInterfaceName() = 0;
};
```

We can use `funccall` action to run C++ scripts for source code transformation. Lets suppose that script names are `make_interface` and `make_removefuncbody` (name as you want).

```
__attribute__((annotate("{gen};{funccall};make_interface;make_removefuncbody")))
```

`{gen};` - keyword used in every CXXCTP annotation.

`{funccall};` - keyword used to tell CXXCTP what it must execute C++ scripts with cling.

`make_interface;make_removefuncbody` - two scripts what CXXCTP will execute.

Scripts will be executed from left (`make_interface`) to right (`make_removefuncbody`).

Usually you don't need to write long C++ annotations, just use C++ `#define` (or include built-in header with common defines):

```
#define $apply(...) \
  __attribute__((annotate("{gen};{funccall};" #__VA_ARGS__)))

class
$apply(make_interface;
  make_removefuncbody)
SomeInterfaceName {
  virtual ~SomeInterfaceName() = 0;
  int foo();
  virtual void foobar(int& arg1) = 0;
  virtual void zoobar(int& arg2);
};
```

Using similar approach you can apply multiple soure code transformation steps to same `class` / `struct` / e.t.c.

## About libtooling
CXXCTP uses LibTooling to parse and modify C++.

LibTooling is a library to support writing standalone tools based on Clang.

Usefull links:
+ https://clang.llvm.org/extra/clang-rename.html
+ Clang Tooling I (add override keyword) https://medium.com/@chichunchen844/clang-tooling-i-add-override-keyword-ddfdf6113b24
+ llvm-clang-samples https://github.com/eliben/llvm-clang-samples/blob/master/src_clang/tooling_sample.cpp
+ https://chromium.googlesource.com/chromium/src/+/master/tools/clang/rewrite_to_chrome_style/RewriteToChromeStyle.cpp
+ http://www.dreamlandcoder.com/system-security/how-i-learned/clang-libtool/
+ https://jonasdevlieghere.com/understanding-the-clang-ast/
+ http://swtv.kaist.ac.kr/courses/cs453-fall13/Clang%20tutorial%20v4.pdf
+ https://meetingcpp.com/mcpp/slides/2019/Teaching%20Old%20Compilers%20New%20Tricks_%20Transpiling%20C++17%20to%20C++11.pdf
+ https://gist.github.com/riyadparvez/a2c157b24579c6552466
+ https://devblogs.microsoft.com/cppblog/exploring-clang-tooling-part-3-rewriting-code-with-clang-tidy/
+ http://blog.audio-tk.com/2018/03/20/writing-custom-checks-for-clang-tidy/
+ https://meetingcpp.com/mcpp/slides/2018/Reflection2.pdf
+ https://s3.amazonaws.com/connect.linaro.org/yvr18/presentations/yvr18-223.pdf
+ https://kevinaboos.wordpress.com/2013/07/30/clang-tips-and-tricks/
+ https://eli.thegreenplace.net/tag/llvm-clang
+ http://www.goldsborough.me/c++/clang/llvm/tools/2017/02/24/00-00-06-emitting_diagnostics_and_fixithints_in_clang_tools/

## About cling
CXXCTP uses cling to execute C++ at compile-time.

You can use cling for hot code reload / REPL / Fast C++ prototyping / Scripting engine / JIT / e.t.c.

Usefull links:
+ https://github.com/derofim/cling-cmake
+ https://github.com/root-project/cling/tree/master/www/docs/talks

## Similar projects

Compile-time EXecution of C++ code https://github.com/MaliusArth/cex/blob/6f6e700a253b06c7ae6801e1a3c1f3d842931d77/tool/src/MatchCallbacks/AnnotatedFunctionCallback.cpp

SaferCPlusPlus https://github.com/duneroadrunner/SaferCPlusPlus

circle https://github.com/seanbaxter/circle/blob/master/examples/README.md

SugarCpp https://github.com/curimit/SugarCpp

ExtendedCpp & modules https://github.com/reneeichhorn/extended-cpp

C/C++ subset resyntaxed like Rust,+ tagged-union/Pattern-Matching, UFCS,inference; LLVM https://github.com/dobkeratops/compiler

transpiling_cpp17_to_cpp11 https://github.com/neobrain/cftf

enum_class with values auto incrementation http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/p0707r0.pdf

enum flags https://github.com/seanbaxter/circle/blob/master/gems/flag_enum.cxx

design patterns https://gist.github.com/blockspacer/44fb6528d801e3149716d59bac041b45

pimpl_generator.cpp https://github.com/flexferrum/autoprogrammer/blob/8c9867d357450b99202dac81730851ffc8faa891/src/generators/pimpl_generator.cpp

enum2string_generator see https://github.com/flexferrum/autoprogrammer/blob/8c9867d357450b99202dac81730851ffc8faa891/src/generators/enum2string_generator.cpp#L106

custom matchers
  + https://github.com/llvm-mirror/clang-tools-extra/blob/388528d/clang-tidy/add_new_check.py
  + https://github.com/llvm-mirror/clang-tools-extra/search?q=addMatcher&unscoped_q=addMatcher

better-enums
  + https://github.com/aantron/better-enums
  + https://github.com/Neargye/magic_enum

docs generator https://github.com/foonathan/standardese

More https://gist.github.com/blockspacer/6f03933de4f9a6c920649713b056ba4a

## Examples


// Metaclass
@gen(
  make_interface(),
  class IShape() {
    void my_func();
  }
)

OR

@gen(make_interface())
{
  class IShape() {
    void my_func();
  }
}

char* print_var(context) {
  printf("my_var name %s\n", my_var, my_var);
  return "";
}

auto my_var = "val_here";
@gen(
  print_var(my_var);
)

struct myStruct {
  int a = 5;
  int b = 10;
} my_struct;

std::string out_var;

@gen(
  reflect_struct_to_file(my_struct, "my/generated/file.cpp");
)

my_struct.b = 15;

std::string out_var2;

@gen(
  generate_json_from_struct(my_struct, out_var);
)

@gen(
  embed_svg_resource("some/file/path_here.txt");
)

@gen(
  embed_code_from_file("some/file/path_here.cpp");
)

@gen(
  generate_code_from_json("some/file/path_here.json");
)

// for example: copyright comment
@gen(
  generate_code_from_jinja("some/file/path_here.jinja");
)

@gen(
  register_strict_type(circle::Width, int); // checks at compile-time that func arg match circle::Width and replaces with int
);

// decorator
// https://github.com/TheMaverickProgrammer/C-Python-like-Decorators
@gen(
  route("/shop/item/2"),
  {
    auto item_id = item.id; // item is func arg
    return response;
  }
)

@gen(import("cstdio"))

@gen(custom_parser(), {
  int main()
      a: int[2,3]
      a[1,2] = 2
})

@gen(custom_operator(), {
  Test (+) (a: const Test&, b: const Test&)
})

// https://github.com/TartanLlama/typeclasses
// https://github.com/nicuveo/CppTypeclasses
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p1717r0.pdf
@gen(type_class(), {
  type_class ex1{1, "var"};
  type_class ex2 = type_class_A{2, "foo"};
  type_class ex3 = type_class_B{3, "bar"};
})

@gen(sigslot(), {
  int myvar7 = 7;
})

@gen(getset(), {
  int myvar5 = 5;
})

// adds pimpl and checks conditions
// TODO https://github.com/flexferrum/autoprogrammer/wiki/pImpl-implementation-generator
@gen(pimpl(), {
  class myclass5{
    // ...
  };
})

@gen(template1_decl(TypeA), {
  Template1::A(){
  }
  Template1::B(){
  }
  // ...
});

@gen(template1_impl(TypeA));

@gen(
  generate_gen_timestamp(outvar);
)

@gen(
  generate_buildflag(outvar);
)

@gen(
  unit_test_func(somearg1),
  {
    @gen(
      generate_func(somearg2);
    )
  }
)

// togglable refactoring m_privateMember vs privateMember_ e.t.c.
@gen(class::members(),
  int a = 5;
  int b = 11;
)

// same as @eval ?
@genonly(
  #include <cling>
)

@matcher(
  addMatcher(...)
)

@disable_generator(interface)

int bar = className->@gen(class::member(a));
OR
int ref& = @member(className->a);
OR
int bar = className->@member(a);

## TODO
no predefined set of code transformations, move exaples to separate repos

https://stackoverflow.com/questions/24062989/clang-fails-replacing-a-statement-if-it-contains-a-macro

codstyle rules https://github.com/gmarpons/Crisp/blob/master/prolog/Rules/SomeHICPPrules.pl

http route https://github.com/leechiryo/mvcpp/blob/e98237bdd8d01dc8a78537799a17c77720b37900/tools/astparser/main.cpp

string to/from hash (to use in switch e.t.c.) https://stackoverflow.com/questions/48896142/is-it-possible-to-get-hash-values-as-compile-time-constants

.template https://github.com/mlomb/MetaCPP/blob/8eddde5e1bf4809ad70a68a385b9cbcc8e237370/MetaCPP-CLI/templates/source.template

jinja
// see https://github.com/flexferrum/autoprogrammer/blob/b391ecd178de34047e110725ece696841729492d/src/jinja2_reflection.h

$gen(import) for compile-time testing

compile_commands.json
https://github.com/Leandros/metareflect/blob/0208fdd4fc0ea1081ae2ff4c3bfce161305a7423/README.md#run-the-metareflect-tool

ability to embed rules for speed (run without cling)

add_func_by_jinja(jinja_arg1, jinja_arg2). NOTE: jinja_arg1 - may be cling var name

C++ class state serialization (byte serialization)

error reporting & unit tests

recursive refletor / serializer

Prefer comparison using epsilon for floating point types like: https://gist.github.com/derofim/df604f2bf65a506223464e3ffd96a78a#comparison-and-boolean-check

enum classes as type-safe bitmasks https://gist.github.com/derofim/0188769131c62c8aff5e1da5740b3574

enum parser https://github.com/goto40/rpp/blob/ec8a4c4a3ac32dccee8c4e8ba97be8c2ba1c8f88/src/parser/enum_parser.cpp

.tmpl https://github.com/feed57005/librfl/blob/master/example/generator/example/templates/package_header.tmpl

$_class(SomeVisitor, Visitor<bool, A, B, C>, Interface)
{
public:
 void TestMethod1();
 std::string TestMethod2(int param) const;
};

disable make_pure_virtual for some methods via annotation

GUID generator for class/e.t.c.

add_custom_command https://github.com/flexferrum/autoprogrammer/blob/1d246b809f916b0aa06388b985b17cc6f6b9e842/test/pimpl/CMakeLists.txt#L17

getCommentForDecl https://github.com/mogemimi/negicco/blob/da829f8c76fff20692b4d5aa6004e12333fb7bdb/05-enum-classes/main.cpp#L106

gen-only comments https://github.com/mogemimi/negicco/blob/da829f8c76fff20692b4d5aa6004e12333fb7bdb/03-comments/main.cpp

protoc https://github.com/feed57005/librfl/blob/master/rfl/CMakeLists.txt#L18

dynamically calling functions by name with the runtime library https://www.reddit.com/r/gamedev/comments/3lh0ba/using_clang_to_generate_c_reflection_data/

separate hpp & cpp: move decl/impl to file/cling var/jinja

editor support? #include generated files?

NamedType https://github.com/joboccara/NamedType

magic_get https://github.com/apolukhin/magic_get

`has` for enum https://github.com/Manu343726/siplasplas/blob/master/examples/reflection/static/enum.cpp#L17

Determine the layout of C and C++ types, including their size, and the size, offset, and padding of each field in the type. https://github.com/joshpeterson/layout

Templates support

Macro support

Remove macro from generated src

Reactive CPP (C++React / RxCpp) https://github.com/schlangster/cpp.react

concurrency / loop vectorizin

loop for recursion

entt / ECS

script / language binding

https://github.com/iboB/dynamix

generating from comments in the code.

type from var https://github.com/pthom/cleantype

script to C++ for speed

in-code jinja with (optional) filename & args
$jinja(filename = ..., arg1 = ..., arg2 = ...)

fix args split, don`t separate based on args in quotes

in-class jinja placeholder attrs & make_jinja_placeholders attr

## Misc
https://medium.com/fluence-network/porting-redis-to-webassembly-with-clang-wasi-af99b264ca8
