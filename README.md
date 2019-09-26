# About CXXCTP (CXX compile-time programming)
CXXCTP is a transpiler that extends C++ for new introspection, reflection and compile-time execution.

CXXCTP doesn`t aim to create predefined set of source code transformations. Users can share C++ scripts for source code transformation.

Suppose somebody shared to opensource community usefull scripts like `interface.cxx` and `enum_to_json.cxx`. Just place that scripts into `ctp_scripts` folder to use them in your project.

Metaprogramming is an “art” of writing programs to treat other programs as their data. This means that a program could generate, read, analyse, and transform code or even itself to achieve a certain solution.

Note: this project is provided as is, without any warranty (see License).

## Usage examples
+ enum_gen_hpp.cxtpl - (codegen) enum to string + reflection metadata.
 ```
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
 ```
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
 ```
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
 ```
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

## Features
+ C++ as compile-time scripting language (https://github.com/derofim/cling-cmake)
+ Template engine with full C++ power (transpiles template to valid C++ code, supports Cling, e.t.c.). https://github.com/blockspacer/CXTPL
+ Ability to modify source files (implement metaclasses, transpile from C++X to C++Y e.t.c.)
+ Ability to create new files (separate generated class to .hpp and .cpp, e.t.c.)
+ Ability to check source files (implement style checks, design patterns, e.t.c.)
+ Ability to compile scripts (rules for code transformations) for maximum performance, not only interpret them in Cling.

## Project status
In development, see examples

Currently supports only linux.

Note that you can run linux containers under windows/mac/e.t.c.

### Clone code
```
git submodule sync --recursive
git submodule update --init --recursive --depth 50
# or
git submodule update --force --recursive --init --remote
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
```

Install CXTPL library https://github.com/blockspacer/CXTPL

Install CXTPL_tool https://github.com/blockspacer/CXTPL#how-to-build

## How to build
```
BEFORE setup_cling.sh:
sudo apt-get update && sudo apt-get upgrade
sudo apt-get install clang libstdc++6
sudo update-alternatives --config c++
sudo update-alternatives --config cc
ldconfig
export CC=clang
export CXX=clang++
```

```
# Build Cling into `cling-build` folder
cd scripts
bash setup_cling.sh
```

Install deps as in CXTPL https://github.com/blockspacer/CXTPL#how-to-build

```
export CC=gcc
export CXX=g++
cmake -E remove_directory build
cmake -E make_directory build
cmake -E remove_directory resources/cxtpl/generated
cmake -E make_directory resources/cxtpl/generated
cmake -E chdir build cmake -E time cmake -DENABLE_CLING=FALSE -DBUILD_SHARED_LIBS=FALSE -DBUILD_EXAMPLES=FALSE -DCMAKE_BUILD_TYPE=Debug -DENABLE_CXXCTP=TRUE ..
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
```
rm -rf *generated* ; clear && clear ; gdb ./CXXCTP -ex "run" -ex "bt" -ex "q"
```

## How to build with Cling support
Use shared CXXCTP_core as SHARED library `-DBUILD_SHARED_LIBS=TRUE`.

Run bash scripts/install_folly.sh from https://github.com/blockspacer/CXTPL or patch folly manually for clang support (replace FOLLY_USE_JEMALLOC with FOLLY_ASSUME_NO_JEMALLOC) https://github.com/facebook/folly/issues/976

Use clang (NOT GCC!) before build and `-DENABLE_CLING=TRUE`:
```
export CC=clang
export CXX=clang++
cmake -E remove_directory build
cmake -E make_directory build
cmake -E remove_directory resources/cxtpl/generated
cmake -E make_directory resources/cxtpl/generated
cmake -E chdir build cmake -E time cmake -DENABLE_CLING=TRUE -DBUILD_SHARED_LIBS=TRUE -DBUILD_EXAMPLES=FALSE -DCMAKE_BUILD_TYPE=Debug -DENABLE_CXXCTP=TRUE ..
cmake -E chdir build cmake -E time cmake --build . -- -j6
# you can install CXXCTP_tool:
sudo cmake -E chdir build make install
```

If you installed CXXCTP_tool - you can run examples:
```
# requires CXXCTP_tool
sudo cmake -E chdir build make install

# use -DBUILD_EXAMPLES=TRUE
cmake -E chdir build cmake -E time cmake -DENABLE_CLING=TRUE -DBUILD_SHARED_LIBS=TRUE -DBUILD_EXAMPLES=TRUE -DCMAKE_BUILD_TYPE=Debug -DENABLE_CXXCTP=TRUE ..
cmake -E chdir build cmake -E time cmake --build . -- -j6

# run examples
build/examples/simple/CXXCTP_example
```

Don`t forget to set Cling include paths by `-extra-arg=-I$PWD/include` and library paths by `-extra-arg=-L$PWD/build` and .so/.dll libs by `-extra-arg=-lCXXCTP_core`:

```

# NOTE: runs CXXCTP_tool on multiple files and adds include paths by `-extra-arg=-I`
cmake -E chdir build ./tool/CXXCTP_tool --ctp_scripts_paths=$PWD -L .=DBG9 -extra-arg=-I$PWD/include -extra-arg=-L$PWD/build -extra-arg=-lCXXCTP_core -extra-arg=-I../resources ../resources/ReflShapeKind.hpp ../resources/test_typeclass_base1.hpp ../resources/test_typeclass_instance1.hpp ../resources/test.cpp
```

## How to add include paths or definitions for Cling
Use `-extra-arg` option of `CXXCTP_tool`:

```
-extra-arg=-I$PWD/include -extra-arg=-I$PWD/include/foo -extra-arg=-DMY_DEFINITION=1 -extra-arg=-DONE_MORE_DEFINITION=1
```

Example:
```
cmake -E chdir build ./tool/CXXCTP_tool --ctp_scripts_paths=$PWD -L .=DBG9 -extra-arg=-I$PWD/include -extra-arg=-I../resources ../resources/ReflShapeKind.hpp ../resources/test_typeclass_base1.hpp ../resources/test_typeclass_instance1.hpp ../resources/test.cpp
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

## How to add custom code transformation rules
Create files with your function in `ctp_scripts`

Add your function name into `ctp_registry.cpp` (may be skipped in Cling / dev-mode)

function signature must be compatable with:
```
typedef std::function<const char*(
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl,
    const std::vector<parsed_func>& args)> cxxctp_callback;
```

Detailed function signature:
+ return value (const char*) - used to replace original code, if needed.
+ clang::ast_matchers::MatchFinder::MatchResult - see https://xinhuang.github.io/posts/2015-02-08-clang-tutorial-the-ast-matcher.html
+ clang::Rewriter - see https://devblogs.microsoft.com/cppblog/exploring-clang-tooling-part-3-rewriting-code-with-clang-tidy/
+ clang::Decl - found by MatchFinder, see https://devblogs.microsoft.com/cppblog/exploring-clang-tooling-part-2-examining-the-clang-ast-with-clang-query/
+ std::vector<parsed_func> - arguments extracted from attribute. Example: $apply(interface, foo_with_args(1, "2")) becomes two `parsed_func` - `interface` and `foo_with_args`.

Think about function name as one of `__VA_ARGS__` from

```
#define $apply(...) \
  __attribute__((annotate("{gen};{funccall};" #__VA_ARGS__)))
```

Example where `make_interface` and `make_removefuncbody` - two function names:
```
$apply(make_interface;
  make_removefuncbody)
```

If you need code generation:
+ Create template file (`.cxtpl`). Build your file using CXTPL_tool https://github.com/blockspacer/CXTPL
+ Create all needed template arguments inside of your function. Names, types, e.t.c. for arguments must be same as in template (cause generated template is valid C++ code).
+ Create variable `std::string cxtpl_output`, that will store result of template rendering with some arguments.
+ Include file generation from template file (`.cxtpl`) inside of your function.

## What is `.cxtpl`
`.cxtpl` is file extention for C++ template engine https://github.com/blockspacer/CXTPL

Example (more below):
```
<div> some template string here </div>
[[~ int valid_cpp_code_block_here = 0; ~]]
[[~]] int and_valid_cpp_code_line_here = 0;
<div> another template string here </div>
<div> and_valid_cpp_code_line_here = [[* valid_cpp_code_block_here *]] </div>
```

You can pass C++ variables by pointers into cxtpl, that is very usefull if you want to use complex data structures as template parameters.

C++ template engine transpiles template into C++ code, so you will gain VERY good performance and full power of C++.

C++ template engine may run in two modes:
+ compile-mode: compile cxtpl code into C++ file or std::string, then `#include` generated code & compile app as usual. Best performance.
+ cling-mode (C++ JIT executed at runtime): compile cxtpl code into C++ file or std::string, then run generated code in Cling interpreter (no need to recompile app, usefull in dev-mode or for php-style apps).

Again: Think about `.cxtpl` as lambda-function returning std::string. Prefer not to use `#include` from `.cxtpl`, just create `.cxtpl.h` file. Then `#include` both generated `.cxtpl.cpp` and created `.cxtpl.h` in your app code.

Code generated from `.cxtpl` must create variable with name `cxtpl_output`, so structure your code as below:
```
/// \note header is NOT generated, it includes stuff for other generated file
#include "../../resources/cxtpl/typeclass_instance_gen_hpp.cxtpl.h"

// ...

void somefunc() {
  std::string cxtpl_output;

  /// \note this is generated .cpp file, it must not use #include
  #include "../../resources/cxtpl/generated/typeclass_instance_gen_hpp.cxtpl.cpp"

  writeToFile(cxtpl_output, gen_hpp_name);
}
```

You need to `#include` all headers used by template generator in your app code. It is good practice to create separate `.cxtpl.h` file near to your `.cxtpl`. Separation of include files allows to use same includes/logic both in compile-mode (just `#include` your `.cxtpl.h`) and cling-mode (pass contents of your `.cxtpl.h` as function argument). See `enum_gen_hpp.cxtpl.h` and `CXTPL_STD.h` as example.

cxtpl uses approach similar to `How to write a template engine in less than 30 lines of code` from https://bits.theorem.co/how-to-write-a-template-library/

+ `[[~` means `start execution of C++ code while parsing template`. Requires `~]]` as closing tag.
+ `~]]` means `end execution of C++ code while parsing template`
+ `[[~]]` means `start execution of C++ code while parsing template`. Requires newline (`\n`) as closing tag.
+ `[[+` means `add result of execution of C++ code to output while parsing template`. Result must be string. Requires `+]]` as closing tag.
+ `[[*` means `add result of execution of C++ code to output while parsing template`. Result will be converted to string (just wrapped in std::to_string). Requires `*]]` as closing tag.

Example before template parsing/transpiling:
```
[[~ // parameters begin

const std::string generator_path = "somepath";

std::vector<std::string> generator_includes{"someinclude"};

// parameters end
/* no newline, see CX=l */ ~]][[~]]
// This is generated file. Do not modify directly.
// Path to the code generator: [[+ generator_path +]].

[[~]] for(const auto& fileName: generator_includes) {
[[+ fileName /* CX=r used to append to cxtpl_output */ +]]
[[~]] } // end for
```

Example after template parsing/transpiling:
```
// This is generated file. Do not modify directly.
// Path to the code generator: somepath.

someinclude
```

Usefull links:
+ https://bits.theorem.co/how-to-write-a-template-library/
+ https://lambda.xyz/blog/maud-is-fast/
+ https://dzone.com/articles/modern-type-safe-template-engines
+ http://www.wilxoft.com/
+ https://github.com/djc/askama
+ https://www.reddit.com/r/rust/comments/b06z9m/cuach_a_compiletime_html_template_system/

## How to add `.cxtpl` at compile-time (CMake)
Add your `.cxtpl` file into `Codegen_files.cmake`

NOTE:
  In dev mode (like cling mode) it may be good idea to generate files from templates using CXTPL_tool https://github.com/blockspacer/CXTPL
  You can add generation rules into `Codegen_files.cmake` later, in release build.

NOTE:
  Don`t forget to provide both `.cxtpl` and `.cxtpl.h` files with shared codegen rules (add to version control system).

## How to use `.cxtpl` at runtime with Cling
You have two options:
+ Generate file from your `.cxtpl`, than include it into Cling C++ script. Similar to compile-time, but you can re-generate/change files without program recompilation. Note that it is possible to generate files and include them in your script, just split script into multiple includes.
+ Generate string from your `.cxtpl`, than run it in separate Cling interpreter. In most cases you will need first option.

## How to use `.cxtpl` with CXXCTP
Pass reflection data into template engine.

Generate files from templates using CXTPL_tool https://github.com/blockspacer/CXTPL

In CXXCTP script (`.cpp`):
```
// see ReflectAST.cpp
reflection::NamespacesTree m_namespaces;
// `node` from AST parser (libtooling)
reflection::ClassInfoPtr structInfo = reflector.ReflectClass(node, &m_namespaces);

// ...

stuct Arguments {
  // any custom arguments here ...
  std::string arg1 = "arg1...";
  std::string arg2 = "arg2...";
  // reflection data here (ClassInfoPtr) ...
};

// ...

std::map<std::string, std::any> cxtpl_params;
{
    cxtpl_params["Arguments"] =
        std::make_any<Arguments>(Arguments{});
    cxtpl_params["generator_path"] =
        std::make_any<std::string>("enum_gen_hpp.cxtpl");
    cxtpl_params["generator_includes"] =
        std::make_any<std::vector<std::string>>(
            std::vector<std::string>{});

    std::string cxtpl_output;

#include "../../resources/cxtpl/generated/enum_gen_hpp.cxtpl.cpp"

    writeToFile(cxtpl_output, gen_hpp_name);
}
```

In `.cxtpl` template:

```
const auto arguments = std::any_cast<Arguments>(cxtpl_params.at("Arguments"));
std::cout << arguments.arg1;
```

See `resources/cxtpl/enum_gen_hpp.cxtpl` as example.

## How to use CXTPL_tool
CXTPL_tool wrapls libtooling to add custom command-line options.

Options related to libtooling (type -help or --help):

```
Generic Options:

  -help                      - Display available options (-help-hidden for more)
  -help-list                 - Display list of available options (-help-list-hidden for more)
  -version                   - Display the version of this program

Use override options:

  -extra-arg=<string>        - Additional argument to append to the compiler command line
  -extra-arg-before=<string> - Additional argument to prepend to the compiler command line
  -p=<string>                - Build path
```

Options related to CXTPL_tool (type --help, not -help):

`ctp_scripts_paths` - list of paths where toll will search for ctp_scripts subfolder

NOTE: `ctp_scripts_paths` require `-DENABLE_CLING=TRUE`

`-L .=DBG9` is log configuration in format https://github.com/facebook/folly/blob/master/folly/logging/docs/Config.md

Example of log configuration which writes both into the file and console stream:
```
./build/tool/CXTPL_tool -L ".:=INFO:default:console; default=file:path=y.log,async=true,sync_level=DBG9;console=stream:stream=stderr"
```

`--srcdir` to change current filesystem path for input files.

`--resdir` to change current filesystem path for output files.

Example (custom output dir):
```
# Remove old generated files
rm -rf gen
rm -rf build/*generated*

`--version` to get tool version

`-version` to get clang version

# Build files to `gen/out` dir
mkdir -p gen/out
cmake -E chdir gen ../build/tool/CXXCTP_tool --resdir=$PWD/gen/out --ctp_scripts_paths=$PWD -L .=DBG9 -extra-arg=-I$PWD/include -extra-arg=-I../resources ../resources/ReflShapeKind.hpp ../resources/test_typeclass_base1.hpp ../resources/test_typeclass_instance1.hpp ../resources/test.cpp
```

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

## TODO
no predefined set of code transformations, move exaples to separate repos

https://stackoverflow.com/questions/24062989/clang-fails-replacing-a-statement-if-it-contains-a-macro

codstyle rules https://github.com/gmarpons/Crisp/blob/master/prolog/Rules/SomeHICPPrules.pl

http route https://github.com/leechiryo/mvcpp/blob/e98237bdd8d01dc8a78537799a17c77720b37900/tools/astparser/main.cpp

string to/from hash (to use in switch e.t.c.) https://stackoverflow.com/questions/48896142/is-it-possible-to-get-hash-values-as-compile-time-constants

.template https://github.com/mlomb/MetaCPP/blob/8eddde5e1bf4809ad70a68a385b9cbcc8e237370/MetaCPP-CLI/templates/source.template

$gen(import) for compile-time testing

compile_commands.json
https://github.com/Leandros/metareflect/blob/0208fdd4fc0ea1081ae2ff4c3bfce161305a7423/README.md#run-the-metareflect-tool

ability to embed rules for speed (run without cling)

base64 Embed Resources Into Executables
 + https://github.com/caiorss/C-Cpp-Notes/blob/master/resources-executable.org#base-64-implementations

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

enum classes as type-safe bitmasks
 + https://gist.github.com/derofim/0188769131c62c8aff5e1da5740b3574

flag_set: Type-safe, hard to misuse bitmask
 + https://foonathan.net/blog/2017/03/16/implementation-challenge-bitmask.html
 + operator- Remove an element https://dxr.mozilla.org/mozilla-central/source/mfbt/EnumSet.h

DISALLOW_COPY_AND_ASSIGN + check that we should delete the methods in the public: section.
 + https://chromium.googlesource.com/chromium/src/base/+/master/macros.h#23
 + https://github.com/chromium/chromium/blob/b9982d8b12286491af4dd8eef12e77b3af9a61d7/ui/views/examples/scroll_view_example.cc#L69
 + https://stackoverflow.com/a/20026657
 + https://github.com/google/styleguide/issues/255

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

separate hpp & cpp: move decl/impl to file/cling var/tpl

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

Reactive CPP (C++React / RxCpp)
 + http://reactivex.io/intro.html
 + https://github.com/schlangster/cpp.react

concurrency / loop vectorizin

loop for recursion

[
  I have been reading articles on data oriented design
  and noticed they often mention how object oriented program is bad
  because of inheritance, virtual calls and cache misses.
  Cache misses seem to occur frequently
  from pointer hopping, virtual calls, and large data structures.
  https://www.reddit.com/r/gamedev/comments/apct0b/looking_for_tips_on_the_entity_component_system/
]
entt / DynaMix / ECS
 + https://www.reddit.com/r/gamedev/comments/3nv8uz/implementation_of_a_componentbased_entity_system/
 + https://habr.com/ru/company/pixonic/blog/413729/
 + https://ibob.github.io/dynamix/appendix.html
[
TODO:
Data-oriented ECS
 + http://bitsquid.blogspot.se/2014/08/building-data-oriented-entity-system.html
]

DOD
 + https://meetingcpp.com/mcpp/slides/2018/Data-oriented%20design%20in%20practice_Nikolov_MeetingCpp18.pdf

script / language binding

generating from comments in the code.

type from var https://github.com/pthom/cleantype

script to C++ for speed

in-code cxtpl with (optional) filename & args
$cxtpl(filename = ..., arg1 = ..., arg2 = ...)

fix args split, don`t separate based on args in quotes

in-class cxtpl placeholder attrs & make_cxtpl_placeholders attr

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

shared pointer that uses a copy-on-write strategy, meaning that you can make an infinite number of copies without copying the actual data
 + https://dragly.org/2018/04/21/value-container-with-copy-by-value-semantics/

[
With inheritance in C++, it is easy to introduce new types,
but hard to extend with new functionality
(all existing types will need to implement any new functions).
Further, it is hard to add functionality after-the-fact.
If a library has defined length() as a function of Vector3,
but you need lengthSquared() for performance reasons,
there is no easy way to add this to the Vector3 class.
You will typically have to make lengthSquared(Vector3 v)
a free function, which makes it awkward,
because you are now calling v.length() for the length,
but lengthSquared(v) for the length squared.
https://dragly.org/2018/04/21/rust-like-traits-in-cpp/
]
[
cache miss?
https://stackoverflow.com/questions/43609682/runtime-overhead-of-shared-ptr-for-subclass-destruction-compared-to-virtual-dest/43610886#43610886
]
Type Erasure
 + When to use type erasure, and when to avoid it. Hands-On Design Patterns with C++
 + https://github.com/seanbaxter/circle/blob/master/erasure/type_erasure.md
 + https://www.reddit.com/r/cpp/comments/8a8iu7/c20conceptsexperiment_using_typeerasure_interface/
 + 2.7 Type Erasure Pattern https://caiorss.github.io/C-Cpp-Notes/cpp-design-patterns.html
 + https://www.reddit.com/r/cpp/comments/5nod8r/will_concepts_replace_polymorphism/
 + https://github.com/andyprowl/virtual-concepts/blob/master/draft/Dynamic%20Generic%20Programming%20with%20Virtual%20Concepts.pdf
 + https://dragly.org/2018/04/21/rust-like-traits-in-cpp/
 + https://github.com/seanbaxter/circle/blob/master/erasure/type_erasure.cxx
 + https://twitter.com/TartanLlama/status/1159445548417634324
 + https://www.youtube.com/watch?v=OtU51Ytfe04
 + https://www.youtube.com/watch?v=QGcVXgEVMJg
 + http://ldionne.com/accu-2017-rust-traits-in-cpp/#/
 + https://locka99.gitbooks.io/a-guide-to-porting-c-to-rust/content/porting_from_cpp/multiple_inheritance.html
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
 + https://www.reddit.com/r/cpp/comments/6sl1hl/customization_point_idea/
 + http://missingfaktor.blogspot.com/2014/02/so-how-much-of-inheritance-criticism.html
 + https://gieseanw.wordpress.com/2018/12/29/stop-reimplementing-the-virtual-table-and-start-using-double-dispatch/
 + https://mropert.github.io/2017/11/30/polymorphic_ducks/
[
Possible problems:
 + b = (cast b to super-type A) then cast back to sub-type https://users.rust-lang.org/t/how-to-do-c-like-inheritance/20545
 + Rust prefers composition over inheritance, so instead of saying a Rectangle is-a Drawable object, you might say it has-a thing which is Drawable https://users.rust-lang.org/t/how-to-do-c-like-inheritance/20545/4
 + 2.2.2. Reference sematics https://github.com/andyprowl/virtual-concepts/blob/master/draft/Dynamic%20Generic%20Programming%20with%20Virtual%20Concepts.pdf
]
[
TODO
 + http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p0957r0.pdf & https://github.com/wmx16835/my-stl/tree/master/src/main/p0957
 + When to use type erasure, and when to avoid it. Hands-On Design Patterns with C++
]
Uniform call syntax in C++ today
 + https://dragly.org/2017/03/31/uniform-call-syntax/

Monoids
 + https://www.youtube.com/watch?v=INnattuluiM
 + https://github.com/boostcon/cppnow_presentations_2019/blob/master/05-09-2019_thursday/Identifying_Monoids_Exploiting_Compositional_Structure_in_Code__Ben_Deane_cppnow_05092019.pdf
 + https://deque.blog/2017/09/13/monoids-what-they-are-why-they-are-useful-and-what-they-teach-us-about-software/
 + https://habr.com/ru/post/205026/
 + http://stepanovpapers.com/notes.pdf
 + https://bartoszmilewski.com/2014/04/21/getting-lazy-with-c/

Double dispatch
 + https://gieseanw.wordpress.com/2018/12/29/stop-reimplementing-the-virtual-table-and-start-using-double-dispatch/
 + https://gieseanw.wordpress.com/2018/12/29/reuse-double-dispatch/

recursion
 + https://deque.blog/2016/11/30/open-recursion-c/

open multi-methods
 + https://www.youtube.com/watch?v=xkxo0lah51s
 + https://github.com/jll63/yomm2/blob/master/examples/synopsis.cpp

DSL
 + https://deque.blog/2017/01/30/catamorph-your-dsl-c-port/ & https://deque.blog/2017/03/31/paramorph-you-dsl-c/

How supporting reflection, being able to manipulate the AST of the language inside the language, and perform any computation at compile time can greatly improve and simplify your code. LISP META-PROGRAMMING FOR C++ DEVELOPERS SERIES https://deque.blog/posts/

A Revisited Command Pattern https://www.oreilly.com/library/view/practical-c-metaprogramming/9781492042778/#toc-start

TODO: Rust++
 + http://mainisusuallyafunction.blogspot.com/2017/06/a-rust-view-on-effective-modern-c.html
 + "Learning Rust With Entirely Too Many Linked Lists" https://rust-unofficial.github.io/too-many-lists/ https://news.ycombinator.com/item?id=16442743
strong types
 + https://www.youtube.com/watch?v=BtA92KmcECQ
 + https://github.com/boostcon/cppnow_presentations_2019/blob/master/05-06-2019_monday/How_I_Learned_to_Stop_worrying_and_Love_the_Cpp_Type_System__Peter_Sommerlad__cppnow_05062019.pdf
 + https://www.slideshare.net/corehard_by/rust-vs-c

pattern matching + YOU CAN MATCH ON FUCKING STRINGS.
+ http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1260r0.pdf
+ https://habr.com/ru/post/282630/
+ https://github.com/mpark/patterns
+ https://github.com/dobkeratops/compiler
+ https://people.gnome.org/~federico/blog/rust-things-i-miss-in-c.html
[
before generator:
int a = 5;
bool b = true;
std::string c = "sasd";
match(a, b, c) {
  case (true, true, true): {
    //...
    break;
  }
  default: {
    //...
    break;
  }
}
after generator:
enum BoolCombos { true_true_true, true_true_false, false_true_true, ... };
// use bitmask enum https://stackoverflow.com/questions/27719098/java-permutation-and-combination-of-boolean-flags
// use bitmask loop https://stackoverflow.com/a/12488907
BoolCombos bc = MakeBoolCombos((bool)a, (bool)b, (bool)c);
switch(bc)
{
case 0: // true_true_true
    //...
    break;
case 1:
    //...
    break;
case 2:
    // ...
    break;
    // ...
};
]

FileID != SourceManager.getMainFileID()
 + https://xinhuang.github.io/posts/2014-10-19-clang-tutorial-finding-declarations.html

TODO: mutable/ref/box traits as in
 + https://habr.com/ru/post/322208/
 + https://github.com/jamboree/polytail

Use codegen & data serialization (restore state on reload) for REPL

templated traits / Associated types
+ https://people.gnome.org/~federico/blog/rust-things-i-miss-in-c.html

state machine

https://manu343726.github.io/2019-07-14-reflections-on-user-defined-attributes/
https://manu343726.github.io/2019-04-18-more-fun-with-user-defined-attributes/
```
    [[math::range(0.0f, 1.0f)]]
    float x;
```

file organization of generated code
+ https://arne-mertz.de/2017/07/generated-code/
+ https://arne-mertz.de/2017/07/organizing-dependencies-generated-code/

unittest.mock.patch https://manu343726.github.io/2019-04-18-more-fun-with-user-defined-attributes/

session types
+ http://simonjf.com/2016/05/28/session-type-implementations.html

TypePrinter:
+ #[derive(Debug)] will know how to automatically print that type's contents for debug output.

TODO: span<T> can prevent at least some classes of memory safety issues
+ https://msrc-blog.microsoft.com/2019/07/18/we-need-a-safer-systems-programming-language/

cpp dangers
+ https://gist.github.com/blockspacer/c44b00fa355c920efcb2abfa84e3990f

Pretty Printer & reflection of structs
+ https://github.com/p-ranav/pprint

TODO: CMake integration

emscripten webidl_binder.py
 > https://github.com/google/draco/blob/master/CMakeLists.txt#L715

TODO: UNIT TESTING AN AST MATCHER https://variousburglarious.com/2017/01/19/unit-testing-an-ast-matcher/

TODO: https://github.com/goto40/rpp/blob/ec8a4c4a3ac32dccee8c4e8ba97be8c2ba1c8f88/src/parser/common_parser.cpp#L21


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
https://www.mkdocs.org/user-guide/configuration/
https://github.com/modm-io/modm/tree/e748b1c3688e753c1e49354ad1cef25f447f9ff6/docs

## Integrate asan / e.t.c.
TODO

## Unit tests & CI/CD
TODO

like https://github.com/Manu343726/unittest#unittest

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

## Misc
https://medium.com/fluence-network/porting-redis-to-webassembly-with-clang-wasi-af99b264ca8
