# About CXXCTP (CXX compile-time programming)
CXXCTP is a transpiler that extends C++ for new introspection, reflection and compile-time execution.

CXXCTP don`t use predefined set of code transformations. Users can share C++ scripts for source code transformation.

Suppose some big company shared to opensource community usefull scripts like `interface.cxx` and `enum_to_json.cxx`. Just place that scripts into `ctp_scripts` folder to use them in your project.

Metaprogramming is an “art” of writing programs to treats other programs as their data. This means that a program could generate, read, analyse, and transform code or even itself to achieve a certain solution.

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

### Clone code
```
sudo git submodule sync --recursive
sudo git submodule update --init --recursive --depth 50
# or
sudo git submodule update --force --recursive --init --remote
```

## DEPENDENCIES
```
# Boost
sudo add-apt-repository ppa:boost-latest/ppa
sudo apt-get update && sudo apt-get upgrade
aptitude search boost
sudo apt-get install libboost-dev

# MPI
sudo apt-get install openmpi-bin openmpi-common libopenmpi-dev

# CMake
bash scripts/install_cmake.sh

# Jinja
# see https://jinja2cpp.dev/docs/build_and_install.html
cd submodules/Jinja2Cpp
#sudo git checkout 0bd14188165769565d53f2bfb5c2e41a2b3a6c9c
sudo git checkout release_1_0_prep
sudo git submodule sync --recursive
sudo git submodule update --init --recursive --depth 50
rm -rf thirdparty/nonstd/expected-light/
git clone https://github.com/martinmoene/expected-lite.git thirdparty/nonstd/expected-light/
rm -rf .build
mkdir .build
cd .build
#     target_link_libraries(jinja2cpp_tests gtest gtest_main nlohmann_json ${LIB_TARGET_NAME} ${EXTRA_TEST_LIBS} boost_system )
#BOOST_ERROR_CODE_HEADER_ONLY
# target_compile_definitions(${LIB_TARGET_NAME} PUBLIC variant_CONFIG_SELECT_VARIANT=variant_VARIANT_NONSTD BOOST_SYSTEM_NO_DEPRECATED )
# -DJINJA2CPP_DEPS_MODE=external-boost -DJINJA2CPP_BUILD_TESTS=OFF -Dvariant_CONFIG_SELECT_VARIANT=variant_VARIANT_NONSTD
# BOOST_SYSTEM_NO_DEPRECATED likely makes it unnecessary to link with boost_system at all
cmake .. -DJINJA2CPP_DEPS_MODE=external-boost -DJINJA2CPP_EXTRA_LIBS=boost_system
cmake --build . --target all
sudo cmake --build . --target install
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
cd scripts
bash setup.sh
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
+ https://www.amazon.com/Getting-Started-LLVM-Core-Libraries/dp/1782166920

## About cling
CXXCTP uses cling to execute C++ at compile-time.

You can use cling for hot code reload / REPL / Fast C++ prototyping / Scripting engine / JIT / e.t.c.

Usefull links:
 + https://github.com/derofim/cling-cmake
 + https://github.com/root-project/cling/tree/master/www/docs/talks
 + https://github.com/caiorss/C-Cpp-Notes/blob/master/Root-cern-repl.org

## Similar projects

Compile-time EXecution of C++ code https://github.com/MaliusArth/cex/blob/6f6e700a253b06c7ae6801e1a3c1f3d842931d77/tool/src/MatchCallbacks/AnnotatedFunctionCallback.cpp

SaferCPlusPlus https://github.com/duneroadrunner/SaferCPlusPlus

circle https://github.com/seanbaxter/circle/blob/master/examples/README.md

SugarCpp https://github.com/curimit/SugarCpp

ExtendedCpp https://github.com/reneeichhorn/extended-cpp

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

C/C++ subset resyntaxed like Rust,+ tagged-union/Pattern-Matching, UFCS,inference; LLVM https://github.com/dobkeratops/compiler

transpiling_cpp17_to_cpp11 https://github.com/neobrain/cftf

enum_class with values auto incrementation http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/p0707r0.pdf

enum flags https://github.com/seanbaxter/circle/blob/master/gems/flag_enum.cxx

design patterns
 + https://gist.github.com/blockspacer/44fb6528d801e3149716d59bac041b45
 + https://github.com/caiorss/C-Cpp-Notes/blob/master/cpp-design-patterns.org

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

base64 Embed Resources Into Executables
 + https://github.com/caiorss/C-Cpp-Notes/blob/master/resources-executable.org#base-64-implementations

add_func_by_jinja(jinja_arg1, jinja_arg2). NOTE: jinja_arg1 - may be cling var name

C++ class state serialization (byte serialization)
 + http://ithare.com/ultra-fast-serialization-of-c-objects/
 + https://rubentorresbonet.wordpress.com/2014/08/25/an-overview-of-data-serialization-techniques-in-c/
 + https://accu.org/index.php/journals/2317
 + https://arxiv.org/pdf/1811.04556.pdf
 + https://stackoverflow.com/questions/46625279/is-it-safe-to-serialize-pod-data-by-casting-directly-to-char-array
 + Modern C++ Programming Cookbook https://books.google.ru/books?id=rHc5DwAAQBAJ&pg=PA301&lpg=PA301&dq=reinterpret_cast+const+char+serialize+C%2B%2B+POD&source=bl&ots=9DUR3KDM16&sig=ACfU3U3BoCEa14SjsJEdsQYymyqnY25kbQ&hl=ru&sa=X&ved=2ahUKEwiNpdGCkrDkAhWjs4sKHYk7BRgQ6AEwAnoECAkQAQ#v=onepage&q=reinterpret_cast%20const%20char%20serialize%20C%2B%2B%20POD&f=false
error reporting & unit tests
 + https://probablydance.com/2015/12/19/quickly-loading-things-from-disk/
 + https://github.com/voidah/archive/blob/master/archive.h
 + https://www.reddit.com/r/cpp/comments/8dpcjh/singleheader_c14_binary_serialization/

RPC
 + http://www.crazygaze.com/blog/2016/06/06/modern-c-lightweight-binary-rpc-framework-without-code-generation/
 + https://www.youtube.com/watch?v=nb1fO4H9Q8w

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

getset
 + https://habr.com/ru/post/459212/
 + https://habr.com/ru/post/121799/
 + https://github.com/tower120/cpp_property

Property (state, descr, man/max/allowed/getset/serialize/onbeforechange/onafterchange/addobserver, hierarchy/PropertyBrowser) & SetPropertyByName()
 + https://github.com/qtinuum/QtnProperty#overview
 + https://woboq.com/blog/reflection-in-cpp-and-qt-moc.html
 + https://github.com/robertknight/Qt-Inspector
 + https://stackoverflow.com/a/49230152

notifier

`has` for enum https://github.com/Manu343726/siplasplas/blob/master/examples/reflection/static/enum.cpp#L17

Determine the layout of C and C++ types, including their size, and the size, offset, and padding of each field in the type. https://github.com/joshpeterson/layout

Templates support

Macro support

Remove macro from generated src

Reactive CPP (C++React / RxCpp) https://github.com/schlangster/cpp.react

concurrency / loop vectorizin

loop for recursion

entt / DynaMix / ECS
 + https://habr.com/ru/company/pixonic/blog/413729/
 + https://ibob.github.io/dynamix/appendix.html

script / language binding

generating from comments in the code.

type from var https://github.com/pthom/cleantype

script to C++ for speed

in-code jinja with (optional) filename & args
$jinja(filename = ..., arg1 = ..., arg2 = ...)

fix args split, don`t separate based on args in quotes

in-class jinja placeholder attrs & make_jinja_placeholders attr

http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p0707r3.pdf

Defer and Finally
 + https://github.com/curimit/SugarCpp#defer-and-finally
 + https://oded.blog/2017/10/05/go-defer-in-cpp/
 + https://www.gingerbill.org/article/2015/08/19/defer-in-cpp/

ERROR HANDLING
 + https://blog.panicsoftware.com/error-handling-now-and-tomorrow/

operator_in
 + https://habr.com/ru/post/419579/

Class Types
 + https://wiki.hsr.ch/PeterSommerlad/files/NDC2018_sane_class_types.pdf

Dependency_Injection
 + https://github.com/boostcon/cppnow_presentations_2019/blob/master/05-06-2019_monday/Dependency_Injection_a_25-dollar_Term_for_a_5-cent_Concept__Kris_Jusiak__cppnow_05062019.pdf

Allocator-Aware (AA) Software
 + https://github.com/boostcon/cppnow_presentations_2019/blob/master/05-06-2019_monday/Value_Proposition_Allocator-Aware_(AA)_Software__John_Lakos__cppnow_05062019.pdf

std::unique_resource
 + https://github.com/okdshin/unique_resource
 + https://habr.com/ru/company/pt/blog/255487/
 + https://www.reddit.com/r/cpp/comments/3upl42/dive_into_c14_3_generic_unique_resource_wrapper/
 + https://stackoverflow.com/questions/24611215/one-liner-for-raii-on-non-pointer
 + https://stackoverflow.com/a/24759558

State_Machines
 + https://github.com/boostcon/cppnow_presentations_2019/blob/master/05-07-2019_tuesday/Rise_of_the_State_Machines__Kris_Jusiak__cppnow_05072019.pdf

Type Erasure
 + https://github.com/seanbaxter/circle/blob/master/erasure/type_erasure.cxx
 + https://twitter.com/TartanLlama/status/1159445548417634324
 + https://www.youtube.com/watch?v=OtU51Ytfe04
 + https://github.com/italiancpp/meetup-milano-2014/blob/300013def6f2182c0b0bce7b3d511613581a437f/cpp_typeclass/presentation/Types%2C%20classes%20and%20concepts%20(updated).pdf
 + http://www.goldsborough.me/cpp/2018/05/22/00-32-43-type_erasure_for_unopinionated_interfaces_in_c++/
 + https://quuxplusone.github.io/blog/2019/03/18/what-is-type-erasure/
 + https://www.codeproject.com/Articles/1208983/Generic-Algorithms-on-Runtime-Types-in-Cplusplus-T
 + https://www.modernescpp.com/index.php/c-core-guidelines-type-erasure-with-templates
 + https://github.com/TartanLlama/typeclasses
 + https://github.com/nicuveo/CppTypeclasses
 + https://github.com/arbrk1/typeclasses_cpp
 + http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p1717r0.pdf
 + https://channel9.msdn.com/Events/GoingNative/2013/Inheritance-Is-The-Base-Class-of-Evil
 + https://www.modernescpp.com/index.php/concepts-lite
 + https://cdn2-ecros.pl/event/codedive/files/presentations/2017/code%20dive%202017%20-%20Michal%20Dominiak%20-%20Customization%20points%20that%20suck%20less.pdf
 + https://github.com/italiancpp/meetup-milano-2014/blob/300013def6f2182c0b0bce7b3d511613581a437f/cpp_typeclass/cpp11/typeclass-example.cpp#L37
 + https://functionalcpp.wordpress.com/2013/08/16/type-classes/

Monoids
 + https://www.youtube.com/watch?v=INnattuluiM
 + https://github.com/boostcon/cppnow_presentations_2019/blob/master/05-09-2019_thursday/Identifying_Monoids_Exploiting_Compositional_Structure_in_Code__Ben_Deane_cppnow_05092019.pdf
 + https://deque.blog/2017/09/13/monoids-what-they-are-why-they-are-useful-and-what-they-teach-us-about-software/
 + https://habr.com/ru/post/205026/
 + http://stepanovpapers.com/notes.pdf
 + https://bartoszmilewski.com/2014/04/21/getting-lazy-with-c/

recursion
 + https://deque.blog/2016/11/30/open-recursion-c/

open multi-methods
 + https://www.youtube.com/watch?v=xkxo0lah51s
 + https://github.com/jll63/yomm2/blob/master/examples/synopsis.cpp

DSL
 + https://deque.blog/2017/01/30/catamorph-your-dsl-c-port/ & https://deque.blog/2017/03/31/paramorph-you-dsl-c/

How supporting reflection, being able to manipulate the AST of the language inside the language, and perform any computation at compile time can greatly improve and simplify your code. LISP META-PROGRAMMING FOR C++ DEVELOPERS SERIES https://deque.blog/posts/

A Revisited Command Pattern https://www.oreilly.com/library/view/practical-c-metaprogramming/9781492042778/#toc-start

strong types
 + https://www.youtube.com/watch?v=BtA92KmcECQ
 + https://github.com/boostcon/cppnow_presentations_2019/blob/master/05-06-2019_monday/How_I_Learned_to_Stop_worrying_and_Love_the_Cpp_Type_System__Peter_Sommerlad__cppnow_05062019.pdf

## Misc
https://medium.com/fluence-network/porting-redis-to-webassembly-with-clang-wasi-af99b264ca8
