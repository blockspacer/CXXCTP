# CXXCTP (CXX Compile-Time Programming)
`CXXCTP` is a transpiler that extends C++ for new introspection, reflection and compile-time execution.

`CXXCTP` doesn't aim to create a predefined set of source code transformations. Users can share C++ scripts for source code transformation.

Suppose somebody shared usefull scripts like `interface.cxx` and `enum_to_json.cxx` to the open source community, placing such scripts into the `ctp_scripts` folder enables them to be used in your project.

Metaprogramming is an “art” of writing programs to treat other programs as their data. This means that a program could generate, read, analyse, and transform code or even itself to solve certain problems.

Note: this project is provided as is, without any warranty (see [License](LICENSE.md)).

- [CXXCTP (CXX Compile-Time Programming)](#cxxctp-cxx-compile-time-programming)
- [Usage](#usage)
- [Core Features](#core-features)
- [Project status](#project-status)
- [Setup Project](#setup-project)
  - [Cloning repository](#cloning-repository)
  - [Install dependencies](#install-dependencies)
    - [Install template engine](#install-template-engine)
  - [Build project](#build-project)
    - [Build with Cling support](#build-with-cling-support)
      - [How to add include paths or definitions for Cling](#how-to-add-include-paths-or-definitions-for-cling)
- [Debugging `ctp_scripts`](#debugging-ctpscripts)
- [Examples](#examples)
- [Motivation](#motivation)
    - [Writing code that writes code](#writing-code-that-writes-code)
- [More information](#more-information)
  - [About libtooling](#about-libtooling)
  - [About cling](#about-cling)
  - [Similar projects](#similar-projects)
- [License](#license)
- [Contributors](#contributors)
  
# Usage

- Below are usage examples of `CXXCTP` if you'd like to know more about `CXXCTP` usage and `CXTPL` go to [USAGE](USAGE.md) 
  
+ enum_gen_hpp.cxtpl - (codegen) enum to string + reflection metadata.
 ```cpp
 // usage example from ReflShapeKind.hpp
 enum class
 $apply(
   reflect_enum
 )
 ReflShapeKind0 : uint32_t {
   Box = 3,
   Sphere = 6,
 };
 ```
+ typeclass_gen_cpp.cxtpl - (codegen) typeclasses. Supports combinations of multiple typeclasses and out-of-source method definition (data and logic separation). See also https://twitter.com/TartanLlama/status/1159457033441165313
 ```cpp
 // Usage example. NOTE: no inheritance & definition outside lib.
 // in lib .h
 struct drawable {
   virtual void draw(const char* arg1) const noexcept = 0;
 };
 struct printable {
   virtual void print(const char* arg1, const char* arg2) const noexcept = 0;
 };
 struct canvas3D {
   std::string name3D;
 };
 struct canvas4D {
   std::string name4D;
 };
 // in app .cpp
 void draw<drawable>(const canvas3D& data, const char* arg1){
   std::cout << "drawing to canvas3D name = " << data.name3D << std::endl;
 }
 void draw<drawable>(const canvas4D& data, const char* arg1){
   std::cout << "drawing to canvas4D name = " << data.name4D << std::endl;
 }
 void print<printable>(const canvas3D& data, const char* arg1, const char* arg2){
   std::cout << "printing to canvas3D name = " << data.name3D << std::endl;
 }
 void print<printable>(const canvas4D& data, const char* arg1, const char* arg2){
   std::cout << "printing to canvas4D name = " << data.name4D << std::endl;
 }
 std::vector<_tc_combined_t<drawable>> vec {
  canvas3D{},
  canvas4D{},
 };
 _tc_combined_t<drawable, printable> CVS = canvas4D{};
 CVS.draw("");
 CVS.print("", "");

 canvas3D cvs3D;
 CVS = std::move(cvs3D);

 canvas4D cvs4D;
 CVS = cvs4D; // copy

 CVS = vec.at(0); // <drawable> to <drawable, printable>
 ```
+ parse-time/compile-time code execution (see test.cpp)
 ```cpp
 $export (
 static int resultSomeInt = 2345;
 )
 $eval("#include <optional>")
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
 ```
+ metaclasses. Supports combinations of multiple metaclasses (see test.cpp).
 ```cpp
 class
 $apply(make_interface;make_removefuncbody;make_reflect)
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
 ```

# Core Features
+ C++ as compile-time scripting language (https://github.com/derofim/cling-cmake)
+ Template engine with full C++ power (transpiles template to valid C++ code, supports Cling, e.t.c.). https://github.com/blockspacer/CXTPL
+ Ability to modify source files (implement metaclasses, transpile from C++X to C++Y e.t.c.)
+ Ability to create new files (separate generated class to .hpp and .cpp, e.t.c.)
+ Ability to check source files (implement style checks, design patterns, e.t.c.)
+ Ability to compile scripts (rules for code transformations) for maximum performance, not only interpret them in Cling.

# Project status
In development, see examples

Currently supports only linux.

Note that you can run linux containers under Windows/OSX and other major operating systems.

# Setup Project 
## Cloning repository
```sh
git submodule sync --recursive
git submodule update --init --recursive --depth 50
```
or
```sh
git submodule update --force --recursive --init --remote
```

## Install dependencies
```sh
# Boost
sudo add-apt-repository ppa:boost-latest/ppa
sudo apt-get update && sudo apt-get upgrade
aptitude search boost
sudo apt-get install libboost-dev

# MPI
sudo apt-get install openmpi-bin openmpi-common libopenmpi-dev

# CMake
bash scripts/install_cmake.sh
```

### Install template engine
- [CXTPL library](https://github.com/blockspacer/CXTPL)
- [CXTPL_tool](https://github.com/blockspacer/CXTPL#how-to-build)

## Build project
```sh
BEFORE install_cling.sh:
sudo apt-get update && sudo apt-get upgrade
sudo apt-get install clang libstdc++6 libstdc++-6-dev
sudo update-alternatives --config c++
sudo update-alternatives --config cc
sudo ldconfig
export CC=clang
export CXX=clang++
```

```sh
# Build Cling into `cling-build` folder
cd scripts
bash install_cling.sh
```

Make sure you've installed [CXTPL](#install-template-engine), an important pre-requisite for continuing this build process.

```sh
export CC=gcc
export CXX=g++
cmake -E remove_directory build
cmake -E make_directory build
cmake -E remove_directory resources/cxtpl/generated
cmake -E make_directory resources/cxtpl/generated
cmake -E chdir build cmake -E time cmake -DENABLE_CLING=FALSE -DBUILD_SHARED_LIBS=FALSE -DBUILD_EXAMPLES=FALSE -DALLOW_PER_PROJECT_CTP_SCRIPTS=TRUE  -DBUNDLE_EXAMPLE_SCRIPTS=FALSE -DCMAKE_BUILD_TYPE=Debug -DENABLE_CXXCTP=TRUE ..
cmake -E chdir build cmake -E time cmake --build . -- -j6

# you can install CXXCTP_tool:
sudo cmake -E chdir build make install

# NOTE: You can also use the “-p” flag with CMAKE_EXPORT_COMPILE_COMMANDS. See https://variousburglarious.com/2018/02/18/include-paths-for-clang-tools/
# cmake -E chdir build ./tool/CXXCTP_tool -p=../example_compile_commands/

# NOTE: runs CXXCTP_tool on multiple files and adds include paths by `-extra-arg=-I`
cmake -E chdir build ./tool/CXXCTP_tool -L .=DBG9 -extra-arg=-I$PWD/include -extra-arg=-I../resources ../examples/built_in/for_codegen/example_make_reflect.cpp

# check generator output
file build/example_make_reflect.cpp.generated.cpp
```

OR under gdb:
```sh
rm -rf *generated* ; clear && clear ; gdb ./CXXCTP -ex "run" -ex "bt" -ex "q"
```

### Build with Cling support
Use shared CXXCTP_core as SHARED library `-DBUILD_SHARED_LIBS=TRUE`.

Run bash scripts/install_folly.sh from https://github.com/blockspacer/CXTPL or patch folly manually for clang support (replace FOLLY_USE_JEMALLOC with FOLLY_ASSUME_NO_JEMALLOC) https://github.com/facebook/folly/issues/976

Use clang (NOT GCC!) before build and `-DENABLE_CLING=TRUE`:
```sh
export CC=clang
export CXX=clang++
sudo rm -rf examples/*/ctp_scripts/*/*/generated/
cmake -E remove_directory build
cmake -E make_directory build
cmake -E remove_directory resources/cxtpl/generated
cmake -E make_directory resources/cxtpl/generated
cmake -E chdir build cmake -E time cmake -DENABLE_CLING=TRUE -DBUILD_SHARED_LIBS=TRUE -DALLOW_PER_PROJECT_CTP_SCRIPTS=TRUE -DBUILD_EXAMPLES=FALSE -DBUNDLE_EXAMPLE_SCRIPTS=FALSE -DCMAKE_BUILD_TYPE=Debug -DENABLE_CXXCTP=TRUE ..
cmake -E chdir build cmake -E time cmake --build . -- -j6
# you can install CXXCTP_tool:
sudo cmake -E chdir build make install
# check supported plugins
/usr/local/bin/CXXCTP_tool --plugins
```

If you installed CXXCTP_tool - you can run examples:
```sh
# requires CXXCTP_tool
sudo cmake -E chdir build make install

# use -DBUILD_EXAMPLES=TRUE
rm ./build/examples/simple/CXXCTP_tool_for_CXXCTP_example.log
cmake -E chdir build cmake -E time cmake -DENABLE_CLING=TRUE -DBUILD_SHARED_LIBS=TRUE -DBUILD_EXAMPLES=TRUE -DBUNDLE_EXAMPLE_SCRIPTS=FALSE -DALLOW_PER_PROJECT_CTP_SCRIPTS=TRUE -DCMAKE_BUILD_TYPE=Debug -DENABLE_CXXCTP=TRUE ..
cmake -E chdir build cmake -E time cmake --build . -- -j6
cat ./build/examples/simple/CXXCTP_tool_for_CXXCTP_example.log

Check that `.log` find doesn`t contain errors

# run examples
build/examples/simple/CXXCTP_example
```

Don't forget to set Cling include paths by `-extra-arg=-I$PWD/include` and library paths by `-extra-arg=-L$PWD/build` and .so/.dll libs by `-extra-arg=-lCXXCTP_core`:

```sh
# NOTE: runs CXXCTP_tool on multiple files and adds include paths by `-extra-arg=-I`
cmake -E chdir build ./tool/CXXCTP_tool --ctp_scripts_paths=$PWD -L .=DBG9 -extra-arg=-I$PWD/include -extra-arg=-L$PWD/build -extra-arg=-lCXXCTP_core -extra-arg=-I../resources ../resources/ReflShapeKind.hpp ../resources/test_typeclass_base1.hpp ../resources/test_typeclass_instance1.hpp ../resources/test.cpp
```

#### How to add include paths or definitions for Cling
Use `-extra-arg` option of `CXXCTP_tool`:

```sh
-extra-arg=-I$PWD/include -extra-arg=-I$PWD/include/foo -extra-arg=-DMY_DEFINITION=1 -extra-arg=-DONE_MORE_DEFINITION=1
```

Example:
```sh
cmake -E chdir build ./tool/CXXCTP_tool --ctp_scripts_paths=$PWD -L .=DBG9 -extra-arg=-I$PWD/include -extra-arg=-I../resources ../resources/ReflShapeKind.hpp ../resources/test_typeclass_base1.hpp ../resources/test_typeclass_instance1.hpp ../resources/test.cpp
```

# Debugging `ctp_scripts`
- Remove old build artifacts and generated files.
- Bundle your scripts with `CXXCTP_tool` via `-DBUNDLE_EXAMPLE_SCRIPTS=TRUE`.
- Make sure that your scripts (plugins) added to `CXXCTP_tool` via `custom_plugins.cmake.example`.
- Disable per-project scripts `-DALLOW_PER_PROJECT_CTP_SCRIPTS=FALSE`.
- Check that your scripts (plugins) are in `build/tool/CXXCTP_tool --plugins`
- Check that installed in system version of `CXXCTP_tool` same as `build/tool/CXXCTP_tool` (by date/file hash)
  
Run `CXXCTP_tool` by hand under `gdb`:
```sh
gdb -ex "r" -ex "bt" --args build/tool/CXXCTP_tool .........
```

Check that all needed paths are in `-extra-arg=`.  
Make log to file in `DBG9` mode and check `.log` files.

# Examples

```cpp
// Metaclass
@gen(
  make_interface(),
  class IShape() {
    void my_func();
  }
)
```
OR
```cpp
@gen(make_interface())
{
  class IShape() {
    void my_func();
  }
}
```
```cpp
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
  generate_code_from_template("some/file/path_here.cxtpl");
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
```
# Motivation

Why wouldn't you just extend clang since it also provides some experimental features (modules for instance)?

Clang is a compiler while this project is a transpiler, that transforms code to standardized c++ code without the need to modify llvm/assembly.

Because tool output is `C++` code, you can compile transpiled code using emscripten, use static code analizers, run code inside cling e.t.c.

`CXXCTP` allows you to create and share scripts for
+ Source code checking (like codestyle validation)
+ Source code transformation (like alphabetical sort of all public functions inside some class)
+ Compile-time programming (like retrieve source code modification rules from remote server and save them in some folder)
+ etc.

### Writing code that writes code
You can write custom C++ scripts for source code transformation or use existing ones.

CXXCTP loads all C++ scripts from ctp_scripts folder in lexicographical order.

Example contents of ctp_scripts:
  + 1_utils
    + CXTPL_STD
      + CXTPL_STD.hpp
      + CXTPL_STD.cpp
    + CXXCTP_STD
      + CXXCTP_STD.hpp
      + CXXCTP_STD.cpp
  + 2_scripts
    + make_interface
      + make_interface.hpp
      + make_interface.cpp
    + typeclass
      + typeclass.hpp
      + typeclass.cpp

Utils must load before scripts (Cling related), so we added `1_`, `2_`, ... before folder names (see above).

You can use `#include`, use filesystem, access internet, e.t.c. in C++ scripts.

# More information

## About libtooling

CXXCTP uses LibTooling to parse and modify C++. LibTooling is a library to support writing standalone tools based on Clang.

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
+ https://www.amazon.com/Getting-Started-LLVM-Core-Libraries/dp/1782166920
+ https://variousburglarious.com/tag/clang/

## About cling

CXXCTP uses cling to execute C++ at compile-time.

You can use cling for hot code reload / REPL / Fast C++ prototyping / Scripting engine / JIT / e.t.c.

Usefull links:
 + (how to add Cling into CMake project) https://github.com/derofim/cling-cmake
 + https://github.com/root-project/cling/tree/master/www/docs/talks
 + https://github.com/caiorss/C-Cpp-Notes/blob/master/Root-cern-repl.org
  

## Similar projects

Clava
+ https://github.com/specs-feup/clava

Compile-time EXecution of C++ code https://github.com/MaliusArth/cex/blob/6f6e700a253b06c7ae6801e1a3c1f3d842931d77/tool/src/MatchCallbacks/AnnotatedFunctionCallback.cpp

SaferCPlusPlus
 + https://duneroadrunner.github.io/SaferCPlusPlus/
 + https://github.com/duneroadrunner/SaferCPlusPlus
 + https://www.codeproject.com/Articles/duneroadrunner#Article
 + https://github.com/bloodstalker/mutator/blob/dccbcf0295105f2ec1631443bb01a6d31d2b0dfb/test/testFuncs1scpp.h
 + https://github.com/duneroadrunner/SaferCPlusPlus/blob/master/msetl_example2.cpp
 + https://github.com/duneroadrunner/SaferCPlusPlus-BenchmarksGame
 + https://github.com/duneroadrunner/SaferCPlusPlus-AutoTranslation

type_safe
 + https://www.youtube.com/watch?v=iihlo9A2Ezw
 + https://www.youtube.com/watch?v=kYiEvVEh6Tw
 + https://github.com/foonathan/type_safe/
 + https://embeddedartistry.com/blog/2018/5/24/improve-type-safety-in-your-c-program-with-the-typesafe-library
 + https://foonathan.net/blog/2016/10/11/type-safe.html
 + https://foonathan.net/blog/2016/10/19/strong-typedefs.html

Opaque Typedefs aka phantom types (strong types)
 + https://nullptr.nl/2018/02/phantom-types/
 + https://github.com/doom/strong_type

translations / i18n
 + https://www.gnu.org/software/gettext/

Ironclad C++
 + https://github.com/crdelozier/ironclad
 + http://acg.cis.upenn.edu/papers/ironclad-oopsla.pdf

Checked C
 + https://duneroadrunner.github.io/SaferCPlusPlus/#safercplusplus-versus-checked-c

debug_new
 + http://nvwa.sourceforge.net/article/debug_new.htm
 + https://github.com/adah1972/nvwa

Guidelines Support Library
 + https://github.com/microsoft/GSL
 + https://www.reddit.com/r/cpp/comments/acspkq/guideline_support_library_what_a_mess/

not_null
 + https://www.bfilipek.com/2017/10/notnull.html
 + https://github.com/Microsoft/GSL/issues/89#issuecomment-280104052
 + http://nullptr.nl/2018/02/some-pointers-on-references/

circle https://github.com/seanbaxter/circle/blob/master/examples/README.md

SugarCpp https://github.com/curimit/SugarCpp

fixed_mem_pool
 + https://github.com/adah1972/nvwa

ExtendedCpp https://github.com/reneeichhorn/extended-cpp

extra libs
 + https://getstudypoint.blogspot.com/2017/07/how-to-work-in-c-from-basic-to-advance.html

modules
 + https://github.com/reneeichhorn/extended-cpp
 + https://www.modernescpp.com/index.php/c-20-modules
 + https://github.com/boostcon/cppnow_presentations_2019/blob/master/05-10-2019_friday/The_Rough_Road_Towards_Upgrading_to_Cpp_Modules__Rich%C3%A1rd_Szalay__cppnow_05102019.pdf

c++ modules backwards compatible
 + https://github.com/build2/build2/blob/master/doc/manual.cli#L6362
 + #ifndef __cpp_modules https://build2.org/doc/modules-cppcon2017.pdf
 + https://github.com/fdwr/TextLayoutSampler/blob/be81e6dbc95151f51acb1ae5ea30c7863f237387/Common.h#L8
 + https://github.com/ned14/kerneltest/blob/07491646b1c1f875d22512e0630902c142eeae5b/include/kerneltest/v1.0/kerneltest.hpp#L37
 + https://stackoverflow.com/questions/34652029/how-should-i-write-my-c-to-be-prepared-for-c-modules
 + https://build2.org/article/cxx-modules-misconceptions.xhtml
 + https://build2.org/doc/modules-cppcon2017.pdf

backports various facilities from more recent C++ Standards
 + http://ryan.gulix.cl/fossil.cgi/cxxomfort/index

Actors
 + https://github.com/italiancpp/meetup-milano-2014/tree/300013def6f2182c0b0bce7b3d511613581a437f/cpp_actor_model
 + https://github.com/actor-framework/actor-framework

C/C++ subset resyntaxed like Rust,+ tagged-union/Pattern-Matching, UFCS,inference; LLVM https://github.com/dobkeratops/compiler

transpiling_cpp17_to_cpp11 https://github.com/neobrain/cftf

enum_class with values auto incrementation http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/p0707r0.pdf

enum flags https://github.com/seanbaxter/circle/blob/master/gems/flag_enum.cxx

design patterns
 + Hands-On Design Patterns with C++
 + https://gist.github.com/blockspacer/44fb6528d801e3149716d59bac041b45
 + https://github.com/caiorss/C-Cpp-Notes/blob/master/cpp-design-patterns.org
 + https://caiorss.github.io/C-Cpp-Notes/cpp-design-patterns.html

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

# License

[MIT](LICENSE.md)

# Contributors
- [Denis Trofimov](https://github.com/derofim)
- [Youssef Mahmoud](https://github.com/yousifm)