# Index
- [Index](#index)
- [About CXXCTP code annotations](#about-cxxctp-code-annotations)
- [How to add custom code transformation rules](#how-to-add-custom-code-transformation-rules)
- [What is `.cxtpl`](#what-is-cxtpl)
  - [How to add `.cxtpl` at compile-time (CMake)](#how-to-add-cxtpl-at-compile-time-cmake)
  - [How to use `.cxtpl` at runtime with Cling](#how-to-use-cxtpl-at-runtime-with-cling)
  - [How to use `.cxtpl` with CXXCTP](#how-to-use-cxtpl-with-cxxctp)
  - [How to use CXTPL_tool](#how-to-use-cxtpltool)
  
# About CXXCTP code annotations

You can use C++ annotations to tell CXXCTP what actions it must execute.

Suppose we want to morph class into interface:

```cpp
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

```h
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

# How to add custom code transformation rules
Create files with your function in `ctp_scripts`

Copy `custom_plugins.cmake.example` as `custom_plugins.cmake`

Append your script paths to `custom_plugins.cmake` via `add_ctp_plugin`:
```cmake
# first arg - typeclass_instance - script function name
# second arg - script source file
# third arg - script header file
# last arg - path to CMakeLists.txt used to generate script-related files
add_ctp_plugin(
  "typeclass_instance"
  ${CMAKE_CURRENT_SOURCE_DIR}/examples/simple/ctp_scripts/2_scripts/typeclass_instance/typeclass_instance.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/examples/simple/ctp_scripts/2_scripts/typeclass_instance/typeclass_instance.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/examples/simple/ctp_scripts/2_scripts/typeclass_instance
)
```

Check that your function name exists in generated file `ctp_registry.cpp` (may be skipped in Cling / dev-mode)

Function signature for code transformation must be compatable with `cxxctp_callback`:
```cpp
typedef std::function<const char*(
    const cxxctp::parsed_func& func_with_args,
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl,
    const std::vector<cxxctp::parsed_func>& all_funcs_with_args)> cxxctp_callback;
```

Detailed function signature:
+ return value (const char*) - used to replace original code, if needed.
+ func_with_args - currently executed function from list `all_funcs_with_args` (see below)
+ clang::ast_matchers::MatchFinder::MatchResult - see https://xinhuang.github.io/posts/2015-02-08-clang-tutorial-the-ast-matcher.html
+ clang::Rewriter - see https://devblogs.microsoft.com/cppblog/exploring-clang-tooling-part-3-rewriting-code-with-clang-tidy/
+ clang::Decl - found by MatchFinder, see https://devblogs.microsoft.com/cppblog/exploring-clang-tooling-part-2-examining-the-clang-ast-with-clang-query/
+ std::vector<parsed_func> - all arguments extracted from attribute. Example: $apply(interface, foo_with_args(1, "2")) becomes two `parsed_func` - `interface` and `foo_with_args`.

Think about function name as one of `__VA_ARGS__` from

```h
#define $apply(...) \
  __attribute__((annotate("{gen};{funccall};" #__VA_ARGS__)))
```

Example where `make_interface` and `make_removefuncbody` - two function names:
```h
$apply(make_interface;
  make_removefuncbody)
```

If you need code generation:
+ Create template file (`.cxtpl`). Build your file using CXTPL_tool https://github.com/blockspacer/CXTPL
+ Create all needed template arguments inside of your function. Names, types, e.t.c. for arguments must be same as in template (cause generated template is valid C++ code).
+ Create variable `std::string cxtpl_output`, that will store result of template rendering with some arguments.
+ Include file generation from template file (`.cxtpl`) inside of your function.

# What is `.cxtpl`
`.cxtpl` is file extention for C++ template engine https://github.com/blockspacer/CXTPL

Example (more below):
```html
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
```cpp
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
```cpp
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

```cpp
const auto arguments = std::any_cast<Arguments>(cxtpl_params.at("Arguments"));
std::cout << arguments.arg1;
```

See `resources/cxtpl/enum_gen_hpp.cxtpl` as example.

## How to use CXTPL_tool
CXTPL_tool wrapls libtooling to add custom command-line options.

Options related to libtooling (type -help or --help):

```sh
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