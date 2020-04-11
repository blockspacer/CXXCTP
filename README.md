&nbsp;
<p align="center">
  <a href="https://CXXCTP.github.io">
    <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/9/91/Cpp-Francophonie.svg/512px-Cpp-Francophonie.svg.png" width="100px" alt="CXXCTP" />
  </a>
</p>
<h3 align="center">Add custom features to C++ language, like <a href="https://www.fluentcpp.com/2018/03/09/c-metaclasses-proposal-less-5-minutes/">metaclasses</a>, <a href="https://twitter.com/TartanLlama/status/1159457033441165313">Rust-like traits</a>, reflection and many more</h3>
<p align="center">A fully open source, powerful solution for modification and generation of C++ source code. Reduce the amount of boilerplate code in your C++ projects.</p>
<hr />

﻿![Open Source Love](https://img.shields.io/badge/Open%20Source-%E2%9D%A4-pink.svg)
![First Timers Only](https://img.shields.io/badge/first--timers--only-friendly-blue.svg?style=flat)
![Up For Grabs](https://img.shields.io/badge/up--for--grabs-friendly-green.svg?style=flat)
![GitHub](https://img.shields.io/github/license/blockspacer/CXXCTP.svg)
![GitHub forks](https://img.shields.io/github/forks/blockspacer/CXXCTP.svg)
![GitHub issues](https://img.shields.io/github/issues/blockspacer/CXXCTP.svg)
![GitHub pull requests](https://img.shields.io/github/issues-pr/blockspacer/CXXCTP.svg)
![GitHub contributors](https://img.shields.io/github/contributors/blockspacer/CXXCTP.svg)
![GitHub commit activity the past week, 4 weeks, year](https://img.shields.io/github/commit-activity/w/blockspacer/CXXCTP.svg)
![GitHub last commit](https://img.shields.io/github/last-commit/blockspacer/CXXCTP.svg)
![GitHub top language](https://img.shields.io/github/languages/top/blockspacer/CXXCTP.svg)
![GitHub language count](https://img.shields.io/github/languages/count/blockspacer/CXXCTP.svg)
[![Project Status: WIP - Initial development is in progress, but there has not yet been a stable, usable release suitable for the public.](http://www.repostatus.org/badges/latest/wip.svg)](http://www.repostatus.org/#wip)
[![license](https://img.shields.io/github/license/blockspacer/CXXCTP.svg?style=flat-square)](https://github.com/blockspacer/CXXCTP/master/LICENSE)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/bsamseth/cpp-project.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/blockspacer/CXXCTP/alerts/)
[![Lines of Code](https://tokei.rs/b1/github/blockspacer/CXXCTP)](https://github.com/blockspacer/CXXCTP)
[![Average time to resolve an issue](http://isitmaintained.com/badge/resolution/blockspacer/CXXCTP.svg)](http://isitmaintained.com/project/blockspacer/CXXCTP "Average time to resolve an issue")
[![Percentage of issues still open](http://isitmaintained.com/badge/open/blockspacer/CXXCTP.svg)](http://isitmaintained.com/project/blockspacer/CXXCTP "Percentage of issues still open")

# 🔗 Navigation

 - [About CXXCTP](#about)
 - [Usage Examples](#usage)
 - [Cloning and setup](#cloning)
 - [Developing with CXXCTP](#developing)
 - [Tools used by CXXCTP](#tools)
 - [How to contribute](#contribute)

# 📚 <a name="about"></a> About CXXCTP (CXX compile-time programming)

CXXCTP is a transpiler that extends C++ for new introspection, reflection and compile-time execution.

CXXCTP doesn't aim to create a predefined set of source code transformations. Users can share C++ scripts for source code transformation.

Suppose someone shared useful scripts like `interface.cxx` and `enum_to_json.cxx` to the open-source community. You can use them in your project just by placing them into the `ctp_scripts` folder.

Metaprogramming is an “art” of writing programs to treat other programs as their data. This means that a program could generate, read, analyse, and transform code or even itself to achieve a certain solution.

Note: This project is provided as it is, without any warranty (see License).

## Features

- C++ as compile-time scripting language (https://github.com/derofim/cling-cmake)
- Template engine with full C++ power (transpiles template to valid C++ code, supports Cling, etc.). https://github.com/blockspacer/CXTPL
- Ability to modify source files (implement metaclasses, transpile from C++X to C++Y etc.)
- Ability to create new files (separate generated class to .hpp and .cpp, etc.)
- Ability to check source files (implement style checks, design patterns, etc.)
- Ability to compile scripts (rules for code transformations) for maximum performance, not only interpret them in Cling.

## Motivation

Why wouldn't you just extend clang since it also provides some experimental features (modules for instance)?

Clang is a compiler while this project is a transpiler, that transforms code to standardized c++ code without the need to modify llvm/assembly.

Because the tool's output is C++ code, you can compile transpiled code using emscripten, use static code analyzers, run code inside cling etc.

CXXCTP allows you to create and share scripts for

- source code check (like codestyle validation)
- source code transformation (like alphabetical sort of all public functions inside some class)
- compile-time programming (like retrieve source code modification rules from remote server and save them in some folder) etc.

## Project status

In development, see examples. Currently supports only Linux.

Note that you can run Linux containers under Windows/Mac/etc.


# ⚙️ <a name="usage"></a>Usage examples
- enum_gen_hpp.cxtpl - (codegen) enum to string + reflection metadata.

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

- typeclass_gen_cpp.cxtpl - (codegen) typeclasses. Supports combinations of multiple typeclasses and out-of-source method definitions (data and logic separation). Supports combinations of multiple typeclasses and out-of-source method definition (data and logic separation). See examples and https://twitter.com/TartanLlama/status/1159457033441165313

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

- parse-time/compile-time code execution (see examples)

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

- metaclasses. Supports combinations of multiple metaclasses (see examples).

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

# 🖥️ <a name="cloning"></a>Cloning and setup
```bash
git submodule sync --recursive
git fetch --recurse-submodules
git submodule update --init --recursive --depth 100 --progress
# or
git submodule update --force --recursive --init --remote
```

## Install & use with Docker

Install and configure Docker: https://medium.com/@saniaky/configure-docker-to-use-a-host-proxy-e88bd988c0aa

Clone code (as above) and `cd` into cloned dir.

NOTE: You may want to build Docker image with `--build-arg NO_SSL="False"`. Read comments in Dockerfile.

```bash
# Give docker the rights to access X-server
sudo -E xhost +local:docker

# build Dockerfile
sudo -E docker build --no-cache \
  --build-arg GIT_WITH_OPENSSL="" \
  --build-arg NO_SSL="False" \
  -t cpp-docker-cxxctp .

# Now let’s check if our image has been created.
sudo -E docker images

# Run in container without leaving host terminal
sudo -E docker run -v "$PWD":/home/u/cxxctp -w /home/u/cxxctp cpp-docker-cxxctp CXXCTP_tool -version --version

# Run a terminal in container
sudo -E docker run --rm -v "$PWD":/home/u/cxxctp -w /home/u/cxxctp  -it  -e DISPLAY         -v /tmp/.X11-unix:/tmp/.X11-unix  cpp-docker-cxxctp

# type in container terminal
CXXCTP_tool -version --version
```

## Develop with Docker

```bash
# Run a terminal in container
sudo -E docker run --rm -v "$PWD":/home/u/cxxctp -w /home/u/cxxctp  -it  -e DISPLAY         -v /tmp/.X11-unix:/tmp/.X11-unix  cpp-docker-cxxctp

# An example of how to build (with Makefile generated from cmake) inside the container
# Mounts $PWD to /home/u/cxxctp and runs command
mkdir build
sudo -E docker run --rm -v "$PWD":/home/u/cxxctp -w /home/u/cxxctp/build cpp-docker-cxxctp cmake -DCONAN_AUTO_INSTALL=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=TRUE ..

# Run resulting app in host OS:
# ./build/<app>
```

## Install conan - a crossplatform dependency manager for C++

```bash
pip install --index-url=https://pypi.python.org/simple/ --trusted-host pypi.org --trusted-host pypi.python.org --trusted-host files.pythonhosted.org wheel \
  && \
  pip install --index-url=https://pypi.python.org/simple/ --trusted-host pypi.org --trusted-host pypi.python.org --trusted-host files.pythonhosted.org virtualenv \
  && \
  pip install --index-url=https://pypi.python.org/simple/ --trusted-host pypi.org --trusted-host pypi.python.org --trusted-host files.pythonhosted.org conan \
  && \
  pip install --index-url=https://pypi.python.org/simple/ --trusted-host pypi.org --trusted-host pypi.python.org --trusted-host files.pythonhosted.org conan_package_tools

conan profile new default --detect
# conan profile update settings.compiler.libcxx=libstdc++11 default

conan remote list

conan search *boost* -r all
```

Configure Proxies & cacert_path in `~/.conan/conan.conf`, see https://docs.conan.io/en/latest/reference/config_files/conan.conf.html#proxies

Configure conan clang profile to then use --profile clang:

```bash
/usr/bin/clang-6.0 -v
/usr/bin/clang++-6.0 -v

nano ~/.conan/profiles/clang

[settings]
# We are building in Ubuntu Linux
os_build=Linux
os=Linux
arch_build=x86_64
arch=x86_64

compiler=clang
compiler.version=6.0
compiler.libcxx=libstdc++11

[env]
CC=/usr/bin/clang-6.0
CXX=/usr/bin/clang++-6.0
```

And then `conan install ***** --profile clang`

```bash
/usr/bin/gcc -v
/usr/bin/g++ -v

nano ~/.conan/profiles/gcc

[settings]
# We are building in Ubuntu Linux
os_build=Linux
os=Linux
arch_build=x86_64
arch=x86_64

compiler=gcc
compiler.version=7
compiler.libcxx=libstdc++11

[env]
CC=/usr/bin/gcc
CXX=/usr/bin/g++
```

If you want to disable ssl (under proxy, etc.):

```bash
# see https://docs.conan.io/en/latest/reference/commands/misc/remote.html#conan-remote
conan remote update conan-center https://conan.bintray.com False
conan search boost* -r=conan-center

conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
conan remote update bincrafters https://api.bintray.com/conan/bincrafters/public-conan False
conan search boost* -r=bincrafters
```

If you want to set corp. cacert:

```bash
CONAN_CACERT_PATH=/path/to/ca-bundle.crt
file $CONAN_CACERT_PATH
```

Useful links:

- https://ncona.com/2019/04/dependency-management-in-cpp-with-conan/
- https://blog.conan.io/2018/06/11/Transparent-CMake-Integration.html
- Conan https://blog.conan.io/2018/06/11/Transparent-CMake-Integration.html https://blog.conan.io/2018/12/03/Using-Facebook-Folly-with-Conan.html
- CONAN_PKG::cppzmq https://github.com/chaplin89/prontocpp/blob/master/CMakeLists.txt#L42
- https://github.com/conan-io/examples

## Add conan remotes

To be able to add the list of dependency remotes please type the following command:

```bash
cmake -E time conan config install conan/remotes/
# OR:
# cmake -E time conan config install conan/remotes_disabled_ssl/
```

## Dependencies

```bash
# NOTE: don't forget to re-run `conan install` after command below
# NOTE: change `build_type=Debug` to `build_type=Release` in production
cmake -DEXTRA_CONAN_OPTS="--profile;clang;-s;build_type=Debug;--build;missing" -P tools/buildConanThirdparty.cmake
```

- type_safe

```bash
conan remote add Manu343726 https://api.bintray.com/conan/manu343726/conan-packages False

git clone http://github.com/foonathan/type_safe.git -b v0.2.1

cd type_safe

# NOTE: change `build_type=Debug` to `build_type=Release` in production
CONAN_REVISIONS_ENABLED=1 \
    CONAN_VERBOSE_TRACEBACK=1 \
    CONAN_PRINT_RUN_COMMANDS=1 \
    CONAN_LOGGING_LEVEL=10 \
    GIT_SSL_NO_VERIFY=true \
    conan create . conan/stable -s build_type=Debug --profile clang --build missing
```

- corrade

```bash
# NOTE: change `build_type=Debug` to `build_type=Release` in production
git clone http://github.com/mosra/corrade.git && cd corrade
CONAN_REVISIONS_ENABLED=1 \
    CONAN_VERBOSE_TRACEBACK=1 \
    CONAN_PRINT_RUN_COMMANDS=1 \
    CONAN_LOGGING_LEVEL=10 \
    GIT_SSL_NO_VERIFY=true \
    conan create . magnum/stable -s build_type=Debug --profile clang --build missing -tf package/conan/test_package
```

- MPI

```bash
sudo apt-get install openmpi-bin openmpi-common libopenmpi-dev
```

- CMake

```bash
sudo -E apt-get purge -y cmake
bash scripts/install_cmake.sh
```

Install CXTPL library https://github.com/blockspacer/CXTPL

Install CXTPL_tool https://github.com/blockspacer/CXTPL#how-to-build

## How to build

```bash
BEFORE install_cling.sh:
sudo apt-get update && sudo apt-get upgrade
sudo apt-get install clang-6.0 libstdc++6 libstdc++-6-dev
sudo update-alternatives --config c++
sudo update-alternatives --config cc
sudo ldconfig
export CC=clang-6.0
export CXX=clang++-6.0
```

```bash
# Build Cling into `cling-build` folder
cd scripts
bash install_cling.sh
```

Install deps as in CXTPL https://github.com/blockspacer/CXTPL#how-to-build

```bash
export CC=clang-6.0
export CXX=clang++-6.0
cmake -E remove_directory build
cmake -E make_directory build
cmake -E remove_directory resources/cxtpl/generated
cmake -E make_directory resources/cxtpl/generated
# NOTE: change `build_type=Debug` to `build_type=Release` in production
CONAN_REVISIONS_ENABLED=1 \
  CONAN_VERBOSE_TRACEBACK=1 \
  CONAN_PRINT_RUN_COMMANDS=1 \
  CONAN_LOGGING_LEVEL=10 \
  GIT_SSL_NO_VERIFY=true \
  cmake -E chdir build  \
    cmake -E time \
      conan install \
        -s build_type=Debug \
        --build=missing \
        --profile clang \
        -o enable_tests=False \
        -o openssl:shared=True \
        ..
cmake -E chdir build cmake -E time cmake -DCONAN_AUTO_INSTALL=OFF -DENABLE_CLING=TRUE -DBUILD_SHARED_LIBS=FALSE -DBUILD_EXAMPLES=FALSE -DALLOW_PER_PROJECT_CTP_SCRIPTS=TRUE  -DBUNDLE_EXAMPLE_SCRIPTS=FALSE -DCMAKE_BUILD_TYPE=Debug -DENABLE_CXXCTP=TRUE ..
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

```bash
rm -rf *generated* ; clear && clear ; gdb ./CXXCTP -ex "run" -ex "bt" -ex "q"
```

## How to build with Cling support

Use shared CXXCTP_core as SHARED library `-DBUILD_SHARED_LIBS=TRUE`.

Run bash scripts/install_folly.sh from https://github.com/blockspacer/CXTPL or patch folly manually for clang support (replace FOLLY_USE_JEMALLOC with FOLLY_ASSUME_NO_JEMALLOC) https://github.com/facebook/folly/issues/976

Use clang (NOT GCC!) before build and `-DENABLE_CLING=TRUE`:

```bash
export CC=clang-6.0
export CXX=clang++-6.0
sudo rm -rf examples/*/ctp_scripts/*/*/generated/
cmake -E remove_directory build
cmake -E make_directory build
cmake -E remove_directory resources/cxtpl/generated
cmake -E make_directory resources/cxtpl/generated
# NOTE: clang profile!
# NOTE: change `build_type=Debug` to `build_type=Release` in production
CONAN_REVISIONS_ENABLED=1 \
  CONAN_VERBOSE_TRACEBACK=1 \
  CONAN_PRINT_RUN_COMMANDS=1 \
  CONAN_LOGGING_LEVEL=10 \
  GIT_SSL_NO_VERIFY=true \
  cmake -E chdir build  \
    cmake -E time \
      conan install \
        -s build_type=Debug \
        --build=missing \
        --profile clang \
        -o enable_tests=False \
        -o openssl:shared=True \
        ..
cmake -E chdir build cmake -E time cmake -DCONAN_AUTO_INSTALL=OFF -DENABLE_CLING=TRUE -DBUILD_SHARED_LIBS=TRUE -DALLOW_PER_PROJECT_CTP_SCRIPTS=TRUE -DBUILD_EXAMPLES=FALSE -DBUNDLE_EXAMPLE_SCRIPTS=FALSE -DCLEAN_CXXCTP_GEN=TRUE -DCMAKE_BUILD_TYPE=Debug -DENABLE_CXXCTP=TRUE ..
# OR cmake -E chdir build cmake -E time cmake -DCONAN_AUTO_INSTALL=OFF -DENABLE_CLING=TRUE -DBUILD_SHARED_LIBS=TRUE -DALLOW_PER_PROJECT_CTP_SCRIPTS=FALSE -DBUILD_EXAMPLES=FALSE -DBUNDLE_EXAMPLE_SCRIPTS=TRUE -DCLEAN_CXXCTP_GEN=TRUE -DCMAKE_BUILD_TYPE=Debug -DENABLE_CXXCTP=TRUE ..
cmake -E chdir build cmake -E time cmake --build . -- -j6
# you can install CXXCTP_tool:
sudo cmake -E chdir build make install
# check supported plugins
/usr/local/bin/CXXCTP_tool --plugins
```

If you installed CXXCTP_tool - you can run examples:

```bash
# requires CXXCTP_tool
sudo cmake -E chdir build make install

# use -DBUILD_EXAMPLES=TRUE
rm ./build/examples/simple/CXXCTP_tool_for_CXXCTP_example.log
cmake -E chdir build cmake -E time cmake -DCONAN_AUTO_INSTALL=OFF -DENABLE_CLING=TRUE -DBUILD_SHARED_LIBS=TRUE -DBUILD_EXAMPLES=TRUE -DBUNDLE_EXAMPLE_SCRIPTS=FALSE -DALLOW_PER_PROJECT_CTP_SCRIPTS=TRUE -DCMAKE_BUILD_TYPE=Debug -DENABLE_CXXCTP=TRUE ..
cmake -E chdir build cmake -E time cmake --build . -- -j6
cat ./build/examples/simple/CXXCTP_tool_for_CXXCTP_example.log

Check that `.log` find doesn`t contain errors

# run examples
build/bin/CXXCTP_example
```

Don't forget to set Cling include paths by`-extra-arg=-I\$PWD/include`and library paths by`-extra-arg=-L\$PWD/build`and .so/.dll libs by`-extra-arg=-lCXXCTP_core`:

```bash
# NOTE: runs CXXCTP_tool on multiple files and adds include paths by `-extra-arg=-I`
cmake -E chdir build ./tool/CXXCTP_tool --ctp_scripts_paths=$PWD -L .=DBG9 -extra-arg=-I$PWD/include -extra-arg=-L$PWD/build -extra-arg=-lCXXCTP_core -extra-arg=-I../resources ../resources/ReflShapeKind.hpp ../resources/test_typeclass_base1.hpp ../resources/test_typeclass_instance1.hpp ../resources/test.cpp
```

## How to add include paths or definitions for Cling

Use `-extra-arg` option of `CXXCTP_tool`:

```bash
-extra-arg=-I$PWD/include -extra-arg=-I$PWD/include/foo -extra-arg=-DMY_DEFINITION=1 -extra-arg=-DONE_MORE_DEFINITION=1
```

Example:

```bash
cmake -E chdir build ./tool/CXXCTP_tool --ctp_scripts_paths=$PWD -L .=DBG9 -extra-arg=-I$PWD/include -extra-arg=-I../resources ../resources/ReflShapeKind.hpp ../resources/test_typeclass_base1.hpp ../resources/test_typeclass_instance1.hpp ../resources/test.cpp
```

# ⌨️ <a name="developing"></a>Developing with CXXCTP
The following sections cover usage, custom rules and debugging for CXXCTP.
## Writing code that writes code

You can write custom C++ scripts for source code transformation or use existing ones.

CXXCTP loads all C++ scripts from ctp_scripts folder in lexicographical order.

Example contents of ctp_scripts:

- 1_utils
  - CXTPL_STD
    - CXTPL_STD.hpp
    - CXTPL_STD.cpp
  - CXXCTP_STD
    - CXXCTP_STD.hpp
    - CXXCTP_STD.cpp
- 2_scripts
  - make_interface
    - make_interface.hpp
    - make_interface.cpp
  - typeclass
    - typeclass.hpp
    - typeclass.cpp

Utils must load before scripts (Cling related), so we added `1_`, `2_`, ... before folder names (see above).

You can use `#include`, use filesystem, access the internet, etc. in C++ scripts.

## Got error `libcling.so.5: cannot open shared object file: No such file or
directory`

Install with `-DENABLE_CLING=TRUE -DINSTALL_CLING=TRUE` and set `LD_LIBRARY_PATH`

```bash
export LD_LIBRARY_PATH=/usr/local/lib/:$LD_LIBRARY_PATH
sudo ldconfig
```

## About CXXCTP code annotations

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

We can use `funccall` action to run C++ scripts for source code transformation. Let's suppose that script names are `make_interface` and `make_removefuncbody` (name as you want).

```cpp
__attribute__((annotate("{gen};{funccall};make_interface;make_removefuncbody")))
```

`{gen};` - keyword used in every CXXCTP annotation.

`{funccall};` - keyword used to tell CXXCTP what it must execute C++ scripts with cling.

`make_interface;make_removefuncbody` - two scripts what CXXCTP will execute.

Scripts will be executed from left (`make_interface`) to right (`make_removefuncbody`).

Usually you don't need to write long C++ annotations, just use C++ `#define` (or include built-in header with common defines):

```cpp
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

Using a similar approach you can apply multiple source code transformation steps to the same `class` / `struct` / etc.

## How to add custom code transformation rules

Create files with your function in `ctp_scripts`

Copy `custom_plugins.cmake.example` as `custom_plugins.cmake`

Append your script paths to `custom_plugins.cmake` via `add_ctp_plugin`:

```bash
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

Function signature for code transformation must be compatible with `cxxctp_callback`:

```cpp
typedef std::function<const char*(
    const cxxctp::parsed_func& func_with_args,
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl,
    const std::vector<cxxctp::parsed_func>& all_funcs_with_args)> cxxctp_callback;
```

Detailed function signature:

- return value (const char\*) - used to replace original code, if needed.
- func_with_args - currently executed function from list `all_funcs_with_args` (see below)
- clang::ast_matchers::MatchFinder::MatchResult - see https://xinhuang.github.io/posts/2015-02-08-clang-tutorial-the-ast-matcher.html
- clang::Rewriter - see https://devblogs.microsoft.com/cppblog/exploring-clang-tooling-part-3-rewriting-code-with-clang-tidy/
- clang::Decl - found by MatchFinder, see https://devblogs.microsoft.com/cppblog/exploring-clang-tooling-part-2-examining-the-clang-ast-with-clang-query/
- std::vector<parsed_func> - all arguments extracted from attribute. Example: \$apply(interface, foo_with_args(1, "2")) becomes two `parsed_func` - `interface` and `foo_with_args`.

Think about function name as one of `__VA_ARGS__` from

```cpp
#define $apply(...) \
  __attribute__((annotate("{gen};{funccall};" #__VA_ARGS__)))
```

Example where `make_interface` and `make_removefuncbody` - two function names:

```cpp
$apply(make_interface;
  make_removefuncbody)
```

If you need code generation:

- Create template file (`.cxtpl`). Build your file using CXTPL_tool https://github.com/blockspacer/CXTPL
- Create all needed template arguments inside of your function. Names, types, etc. for arguments must be the same as in template (cause generated template is valid C++ code).
- Create variable `std::string cxtpl_output`, that will store result of template rendering with some arguments.
- Include file generation from template file (`.cxtpl`) inside of your function.

## What is `.cxtpl`

`.cxtpl` is the file extension for the C++ template engine https://github.com/blockspacer/CXTPL

## How to add `.cxtpl` at compile-time (CMake)

Add your `.cxtpl` file into `Codegen_files.cmake`

NOTE:
In dev mode (like cling mode) it may be a good idea to generate files from templates using CXTPL_tool https://github.com/blockspacer/CXTPL
You can add generation rules into `Codegen_files.cmake` later in the release build.

NOTE:
Don't forget to provide both `.cxtpl`and`.cxtpl.h` files with shared codegen rules (add to version control system).

## How to use `.cxtpl` at runtime with Cling

You have two options:

- Generate a file from your `.cxtpl`, then include it into Cling C++ script. Similar to compile-time, but you can re-generate or change files without program recompilation. Note that it is possible to generate files and include them in your script; just split script into multiple includes.
- Generate a string from your `.cxtpl`, then run it in a separate Cling interpreter. In most cases you will use the first option.

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

See `resources/cxtpl/enum_gen_hpp.cxtpl` as an example.

## How to use CXXCTP_tool

CXXCTP_tool wraps libtooling to add custom command-line options.

Options related to libtooling (type -help or --help):

```bash
Generic Options:

  -help                      - Display available options (-help-hidden for more)
  -help-list                 - Display list of available options (-help-list-hidden for more)
  -version                   - Display the version of this program

Use override options:

  -extra-arg=<string>        - Additional argument to append to the compiler command line
  -extra-arg-before=<string> - Additional argument to prepend to the compiler command line
  -p=<string>                - Build path
```

Options related to CXXCTP_tool (type --help, not -help):

`ctp_scripts_paths` - list of paths where toll will search for ctp_scripts subfolder

NOTE: `ctp_scripts_paths` requires `-DENABLE_CLING=TRUE`

`-L .=DBG9` is log configuration in format https://github.com/facebook/folly/blob/master/folly/logging/docs/Config.md

Example of log configuration that writes both into the file and console stream:

```bash
./build/bin/CXXCTP_tool -L ".:=INFO:default:console; default=file:path=y.log,async=true,sync_level=DBG9;console=stream:stream=stderr"
```

`--srcdir` to change current filesystem path for input files.

`--resdir` to change current filesystem path for output files.

Example (custom output dir):

```bash
# Remove old generated files
rm -rf gen
rm -rf build/*generated*

`--version` to get tool version

`-version` to get clang version

# Build files to `gen/out` dir
mkdir -p gen/out
cmake -E chdir gen ../build/bin/CXXCTP_tool --resdir=$PWD/gen/out --ctp_scripts_paths=$PWD -L .=DBG9 -extra-arg=-I$PWD/include -extra-arg=-I../resources ../resources/ReflShapeKind.hpp ../resources/test_typeclass_base1.hpp ../resources/test_typeclass_instance1.hpp ../resources/test.cpp
```

## How to debug `ctp_scripts`

Remove old build artifacts and generated files.

Bundle your scripts with `CXXCTP_tool` via `-DBUNDLE_EXAMPLE_SCRIPTS=TRUE`.

Make sure that your scripts (plugins) are added to `CXXCTP_tool` via `custom_plugins.cmake.example`.

Disable per-project scripts `-DALLOW_PER_PROJECT_CTP_SCRIPTS=FALSE`.

Check that your scripts (plugins) are in `build/tool/CXXCTP_tool --plugins`

Check that the system-installed version of `CXXCTP_tool` is the same as `build/tool/CXXCTP_tool` (by date/file hash)

Run `CXXCTP_tool` manually under `gdb`:

```bash
gdb -ex "r" -ex "bt" --args build/tool/CXXCTP_tool .........
```

Check that all needed paths are in `-extra-arg=`.

Make a log to file in `DBG9` mode and check `.log` files.

# 🔧 <a name="tools"></a>Tools used by CXXCTP

## About libtooling

CXXCTP uses LibTooling to parse and modify C++.

LibTooling is a library to support writing standalone tools based on Clang.

Useful links:

- https://clang.llvm.org/extra/clang-rename.html
- Clang Tooling I (add override keyword) https://medium.com/@chichunchen844/clang-tooling-i-add-override-keyword-ddfdf6113b24
- llvm-clang-samples https://github.com/eliben/llvm-clang-samples/blob/master/src_clang/tooling_sample.cpp
- https://chromium.googlesource.com/chromium/src/+/master/tools/clang/rewrite_to_chrome_style/RewriteToChromeStyle.cpp
- http://www.dreamlandcoder.com/system-security/how-i-learned/clang-libtool/
- https://jonasdevlieghere.com/understanding-the-clang-ast/
- http://swtv.kaist.ac.kr/courses/cs453-fall13/Clang%20tutorial%20v4.pdf
- https://meetingcpp.com/mcpp/slides/2019/Teaching%20Old%20Compilers%20New%20Tricks_%20Transpiling%20C++17%20to%20C++11.pdf
- https://gist.github.com/riyadparvez/a2c157b24579c6552466
- https://devblogs.microsoft.com/cppblog/exploring-clang-tooling-part-3-rewriting-code-with-clang-tidy/
- http://blog.audio-tk.com/2018/03/20/writing-custom-checks-for-clang-tidy/
- https://meetingcpp.com/mcpp/slides/2018/Reflection2.pdf
- https://s3.amazonaws.com/connect.linaro.org/yvr18/presentations/yvr18-223.pdf
- https://kevinaboos.wordpress.com/2013/07/30/clang-tips-and-tricks/
- https://eli.thegreenplace.net/tag/llvm-clang
- http://www.goldsborough.me/c++/clang/llvm/tools/2017/02/24/00-00-06-emitting_diagnostics_and_fixithints_in_clang_tools/
- https://www.amazon.com/Getting-Started-LLVM-Core-Libraries/dp/1782166920
- https://variousburglarious.com/tag/clang/

## About cling

CXXCTP uses cling to execute C++ at compile-time.

You can use cling for hot code reload / REPL / Fast C++ prototyping / Scripting engine / JIT / etc.

Useful links:

- (how to add Cling into CMake project) https://github.com/derofim/cling-cmake
- https://github.com/root-project/cling/tree/master/www/docs/talks
- https://github.com/caiorss/C-Cpp-Notes/blob/master/Root-cern-repl.org

### clang-format

```bash
sudo apt install clang-format
```

Run based on `.clang-format` file:

```bash
find . -regex '.*\.\(cpp\|hpp\|cu\|c\|h\)' -exec clang-format -style=file -i {} \;
```

Useful links:

- Create & use `.clang-format` file https://leimao.github.io/blog/Clang-Format-Quick-Tutorial/
- Integrate with your IDE ( QT instructions http://doc.qt.io/qtcreator/creator-beautifier.html ) Import .clang-format rules to IDE settings.

# ⭐️ <a name="contribute"></a>How to Contribute

Please read our [contributing](CONTRIBUTING.md) guidelines before making your pull request.

## Code of Conduct

Please note that this project is released with a [Code of Conduct](CODE_OF_CONDUCT.md). By participating in this project, you agree to abide by its terms.

### Contributors List: Example Profile

- I'm an example that you can copy, if you want :)
- I work on many things like...
- My hobbies include...
- [![twitter-alt][twitter-img]](https://twitter.com/example)
  [![facebook-alt][facebook-img]](https://facebook.com/example)
  [![google-img][google-img]](https://plus.google.com/+Example)
  [![tumblr-alt][tumblr-img]](https://example.tumblr.com)
  [![dribbble-alt][dribbble-img]](https://dribbble.com/example)
  [![github-alt][github-img]](https://github.com/example)
  [![freeCodeCamp](imgs/freecodecamp.png)](https://www.freecodecamp.org/example)
  [<img src="imgs/linkedin.svg" width="20" height="20">](https://www.linkedin.com/in/example/)

### Contributors List 👌

#### A

##### Anindita Basu

- Technical writer
- [![twitter-alt][twitter-img]](https://twitter.com/anindita_basu)
  [![github-alt][github-img]](https://github.com/AninditaBasu)

##### Anna Hayhurst

- Junior Developer
- [![github-alt][github-img]](https://github.com/annahayhurst)

#### C

##### Cássio Espíndola

- Analyst Developer
- [![github-alt][github-img]](https://github.com/cassioesp)

#### D

##### Denis trofimov

- C++ Developer
- [![github-alt][github-img]](https://github.com/blockspacer)
- [![github-alt][github-img]](https://github.com/derofim)
- [<img src="imgs/linkedin.svg" width="20" height="20">](https://www.linkedin.com/in/denis-trofimov-4335bb13b/)

#### M

##### Mohib Qureshi

- Software Development Enthusiast
- [![github-alt][github-img]](https://github.com/mohibqureshi)

#### Y

##### Yousif Alebyary

- Web/Mobile Developer.
- [![github-alt][github-img]](https://github.com/yousifm)

##### Yves Mancera

- Software Engineer
- [![github-alt][github-img]](https://github.com/yvesmh)

## Standing on the Shoulders of Giants

That project possible because of [flexferrum's `autoprogrammer`](https://github.com/flexferrum/autoprogrammer).

Articles about flexferrum's `autoprogrammer` in media:

- [RUS] метаклассах по-русски https://habr.com/ru/article/448466/
- [RUS] Метаклассы в C++17 Фантастика? Реальность! https://assets.ctfassets.net/oxjq45e8ilak/55bGdX2PnYzmrpM8rwCjcE/791e7eee3236c2023e86e169faca8a0e/Sergei_Sadovnikov_Metaclasses_in_C___dream_Reality.pdf

## LICENSE for open source components

All the open source components are used under their associated open source licences.

Used open source components:
* icu
* ced
* boost
* harfbuzz
* boost.outcome
* chromium (base)
* libevent
* modp_b64
* tcmalloc
* xdg_mime
* xdg_user_dirs
* dynamic_annotations
* (Facebook) Folly
* (Microsoft) GSL

See LICENSE files

### CMake Code style

CMake files pass style checks, can be fixed by running run-cmake-format.py from the root of the repository. This requires Python 3 and [cmake_format](https://github.com/cheshirekow/cmake_format) (note: this currently does not work on Windows)

Use autoformatter `cmake-format.py` and `run-cmake-format.py`

```bash
pip3 install cmake_format
python3 run-cmake-format.py
```

To use cmake-format on a specific CMakeLists.txt file in the command line run

```bash
python3 -m cmake_format -c cmake-format.py -i CMakeLists.txt
```

There is an official Visual Studio extension, details of which can be found [here](https://marketplace.visualstudio.com/items?itemName=cheshirekow.cmake-format).

Follow CMake StyleGuide https://github.com/ruslo/0

## Projects that use `.cxtpl`

- [SKG](https://github.com/blockspacer/skia-opengl-emscripten) C++ HTML/CSS UI.

# 📋 Similar projects

- https://github.com/cppreflect/metapp
- https://github.com/flexferrum/autoprogrammer/blob/8c9867d357450b99202dac81730851ffc8faa891/src/generators/pimpl_generator.cpp
- Clava https://github.com/specs-feup/clava
- Compile-time EXecution of C++ code https://github.com/MaliusArth/cex/blob/6f6e700a253b06c7ae6801e1a3c1f3d842931d77/tool/src/MatchCallbacks/AnnotatedFunctionCallback.cpp
- circle https://github.com/seanbaxter/circle/blob/master/examples/README.md
- SugarCpp https://github.com/curimit/SugarCpp
- ExtendedCpp https://github.com/reneeichhorn/extended-cpp
- https://github.com/dobkeratops/compiler
- transpiling_cpp17_to_cpp11 https://github.com/neobrain/cftf
- https://github.com/llvm-mirror/clang-tools-extra/blob/388528d/clang-tidy/add_new_check.py
- https://github.com/aantron/better-enums
- https://github.com/Neargye/magic_enum
- https://github.com/foonathan/standardese
- https://github.com/Leandros/metareflect/blob/0208fdd4fc0ea1081ae2ff4c3bfce161305a7423/README.md#run-the-metareflect-tool
- https://github.com/qtinuum/QtnProperty#overview
- https://github.com/p-ranav/pprint
- https://github.com/google/draco/blob/master/CMakeLists.txt#L715
- https://github.com/goto40/rpp/blob/ec8a4c4a3ac32dccee8c4e8ba97be8c2ba1c8f88/src/parser/common_parser.cpp#L21
- More https://gist.github.com/blockspacer/6f03933de4f9a6c920649713b056ba4a

[twitter-alt]: Twitter
[facebook-alt]: Facebook
[google-alt]: Google+
[tumblr-alt]: Tumblr
[dribbble-alt]: Dribbble
[github-alt]: GitHub
[twitter-img]: https://i.imgur.com/wWzX9uB.png
[facebook-img]: https://i.imgur.com/fep1WsG.png
[google-img]: https://i.imgur.com/VlgBKQ9.png
[tumblr-img]: https://i.imgur.com/jDRp47c.png
[dribbble-img]: https://i.imgur.com/Vvy3Kru.png
[github-img]: https://i.imgur.com/9I6NRUm.png
