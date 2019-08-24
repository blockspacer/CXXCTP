## C++ & Cling & CMake
Shows how to build Cling and integrate it into CMake project.

For integration you just:
* link with Cling and ClingInterpreter
* include cling/
* include llvm/ (from cling sources)
* include clang/ (from cling sources)
* Set paths to llvm/ when creating cling::Interpreter (at runtime)

Cling may be used for:
* Hot code reload / REPL / Fast C++ prototyping like https://blog.qt.io/blog/2018/06/15/scripting-in-c/
* ROOT – ACLiC https://mightynotes.wordpress.com/2019/06/27/how-fast-is-root-comparing-its-jit-to-real-compilers/
* Scripting engine / JIT like https://www.phoronix.com/scan.php?page=news_item&px=Facebook-JIT-Cpp-Scripting
* Debugging (https://github.com/inspector-repl/inspector)
* Interactive coding (https://github.com/0xfd000000/qling and https://github.com/galsasson/ClingOFPlayground)
* Serializer / Reflection at runtime
* Extend C++ syntax (for example - new unit test framework that can run tests both while you change C++ using Cling or compile code as usual / fuzzier support )
* Language binding (C++ to Python like PyROOT e.t.c.)
* Jupyter C++ Notebook like https://github.com/QuantStack/xeus-cling / Web C++ IDE / sandboxed code testing (like in online coding challenges)
* IDE integration / Tab Completion like https://github.com/esakellari/TabCompletionCling
* Learn C++ faster.
* Code checkers / beautifiers / Static Analysis / Runtime Analysis / e.t.c.
* e.t.c.

## Notes
* Don`t create main() twice! Don`t create main() in Cling scripts!
* This example uses modular architecture. Each module owns separate cling::Interpreter. On module reload you will lose state (variables) only for that module. So, you can create app that allows to change code at runtime (by changing only stateless modules or by saving data on code reload).
* You must wrap old main(), so it will be compatable with Cling`s main().
  > In this example you must create functions for each Module (cling::Interpreter) *_cling_prepare/*_cling_run/*_cling_shutdown. You can use *_cling_run to imitate main loop.
* You must stop some threads, free memory e.t.c. on code reload. See *_cling_shutdown.
* Prefer async operations. Otherwise you will not be able to cancel sync http server after Cling code reload (and hanged operation will crash on use because of changed code).

# About Cling
* https://root.cern.ch/root/htmldoc/guides/users-guide/Cling.html
* https://root.cern.ch/cling-brief
* https://root.cern.ch/cling
* https://root.cern.ch/guides/users-guide
* https://caiorss.github.io/C-Cpp-Notes/Root-cern-repl.html

## Supported platforms
Linux
> Tested, must work. Uses gcc.

TODO: Windows / WSL
> May work fine, not tested

TODO: Mac
> NOTE: on MAC set -stdlib=libstdc++
> May work fine, not tested

## SETUP

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

see:
```
bash scripts/setup.sh
```

If tou use cusom build paths, than change paths in
```
cmake/modules/FindCling.cmake
```

# BUILD with CLING

If you want debug build with hot reload (use interpreter, slow speed) - just change ENABLE_CLING to TRUE:

```
# export CC=clang-7
# export CXX=clang++-7
export CC=gcc
export CXX=g++
rm -rf build
mkdir build
cd build
cmake -DENABLE_CLING=TRUE -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . -- -j6
./cling-demo
```

# BUILD without CLING

If you want release build without hot reload (ordinary native build, max speed) - just change ENABLE_CLING to FALSE:
```
cmake -DENABLE_CLING=FALSE -DCMAKE_BUILD_TYPE=Debug ..
```

# Found Issues
* undo is buggy, avoid it now (As possible workaround - you may just change variables or change callbacks or store app state). Hope it will be fixed - Unloading (needed for reloading) will be an awesome feature:
 > undo works fine only for small & simple code snippets. Can`t unload includes like <iostream> multiple times, may go into strange state after raising error e.t.c.
 > https://root-forum.cern.ch/t/cling-reload-unload-doesnt-work/15797/5
 > https://root-forum.cern.ch/t/understanding-undo-and-interpreter-unload/20601/10
 > https://github.com/vgvassilev/cling/issues/161

# TODO: HOT reload
possible approaches:
* store app state
* fix cling undo for files
> https://root-forum.cern.ch/t/loading-unloading-class-as-interpreted-macro-in-cling-multiple-times/32976/2
* execute cling code to change callbacks & variables
* nested cling::Interpreter with multiple cling::MetaProcessor
 > IDK how to do it, but you can create child cling::Interpreter

# TODO: switch between native / cling in CMAKE
ability to turn cling off and use normal conpilation

# TODO: serializer / Reflection at runtime
> https://github.com/PDelak/cintent/blob/c8cdb4f66f2fb701d388984fd4c1cce54ef91316/tools/driver/basicserializer.cpp
> https://github.com/pypyjs/pypy/blob/2c2c5c73d780ff71f03adc2f1bf2c1c4bb7cc031/pypy/module/cppyy/src/clingcwrapper.cxx
> https://github.com/vgvassilev/cling/blob/master/test/Lookup/template.C
> https://github.com/root-project/cling/blob/master/test/Lookup/named.C
> https://github.com/search?l=C%2B%2B&q=%22getQualifiedNameAsString%22+%22getLookupHelper%22&type=Code

# TODO: dll & cling

# TODO: docker / vagrant
> https://github.com/nikhedonia/docker-cling

# TODO: new unit test framework that can run tests both while you change C++ using Cling or compile code as usual
 > tests in same file similar to https://github.com/onqtam/doctest
 > fuzzier support like http://lcamtuf.coredump.cx/afl/ ( https://habr.com/ru/post/332076/ )
