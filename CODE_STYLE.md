# About

Code style based on [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)

## Auto code formatting tool

Prefer clang-format, see `.clang-format` file.

## Code style check

Use tools like [vera++](https://bitbucket.org/verateam/vera/wiki/Home)

## Static analysis

Use any tools from the [list of tools for static code analysis]( https://en.wikipedia.org/wiki/List_of_tools_for_static_code_analysis#C.2B.2B)

## Version control

Prefer git.

## Scanning project

Scan the whole project before pushing code to version control system.

## Naming schemes

The following shortcuts are used in this section to denote naming schemes:

* CamelCased: The name starts with a capital letter, and has a capital letter for each new word, with no underscores.
* camelCased: Like CamelCase, but with a lower-case first letter
* under_scored: The name uses only lower-case letters, with words separated by underscores. (yes, I realize that under_scored should be underscored, because it's just one word).
* ALL_CAPITALS: All capital letters, with words separated by underscores.

## Bracket Style

"One True Brace Style" uses linux brackets and adds brackets to unbracketed one line conditional statements. Opening brackets are broken from namespaces, classes, and function definitions. Brackets are attached to everything else including statements within a function, arrays, structs, and enums.

```cpp
int Foo(bool isBar)
{
    if (isFoo) {
        bar();
        return 1;
    } else {
        return 0;
    }
}
```

Use attached braces: The opening brace goes on the same line as the start of the statement. If the closing brace is followed by another keyword, it goes into the same line as well.

Note: function implementations and class declarations always have the left brace on the start of a line.

## Files

Every source file should have an associated header file.
Prefer .h and .cpp extensions for C++ files.

## Header files

A header should have header guards and include all other headers it needs.
Use "#pragma once" instead of "#ifdef" guard.

## Forward declarations

Avoid using forward declarations where possible.
A "forward declaration" is a declaration of a class, function, or template without an associated definition.

## Inline Functions

Define functions inline only when they are small, say, 10 lines or fewer.
A member function defined in a class definition is implicitly inline, but prefer force inline functions where appropriate (useful for testing program with different optimisation flags).

## Order of Includes

All of a project's header files should be listed as descendants of the project's source directory without use of UNIX directory shortcuts . (the current directory) or .. (the parent directory). Within each section the includes should be ordered alphabetically. Separate the categories with empty lines.

Order of Includes (Within each section the includes should be ordered alphabetically):

* Precompiled header file or project headers necessary for containing compile unit. For example, for file "fooserver.cpp" it may be "fooserver.h".
* C system files.
* C++ system files.
* Other libraries' .h files.
* Your project's .h files.

Example:

```cpp
#include "PrecompiledHeader.h" // Precompiled header files

#include "MainProjectClass.h" // Project headers necessary for containing compile unit MainProjectClass.cpp

#include <math.h> // C system files
#include <stdarg.h>

#include <chrono> // C++ system files
#include <fstream>
#include <iomanip>

#include <lib/AlphaHeader> // lib`s libraries' .h files.
#include <lib/BettaHeader>

#include <qt/qbutton.h> // qt`s libraries' .h files.
#include <qt/qtextfield.h>

#include "ProjectHeaderUseful.h" // Project's .h files.
#include "ProjectHeaderUtils.h"
```

The first header included should be the header related to this source file, thus in position 1. This way you make sure that it includes anything it needs and that there is no "hidden" dependency: if there is, it'll be exposed right away and prevent compilation.

The order you list your includes shouldn't matter from a technical point of view. If you designed it right, you should be able to put them in any order you want and it will still work.

## Namespaces

With few exceptions, place code in a namespace.
Never use "using namespace" in Header Files.
Always use "std::", never use "using namespace std;".
Do not use using-directives (e.g. using namespace foo). Do not use inline namespaces.
Namespaces should have unique names based on the project name, and possibly its path.
Unnamed namespaces are allowed.
Don't use indentations for namespaces.
Place "{" right after namespace name.
Prefer :: prefix (refers to the global namespace).

```cpp
#pragma once

#include "Era.h"

namespace exa {
namespace era {

  using namespace ::exa::era;

  // ...

} //namespace exa::era
} //namespace exa

```

## Nonmember, Static Member, and Global Functions

Prefer placing nonmember functions in a namespace; use completely global functions rarely.

## Global variables

Prefer :: prefix for global variables (refers to the global namespace).

```cpp
::mainWindow.open()
::applicationContext.getName()
```

Global variables should almost never be used (see below for more on this). When they are used, global variables are with a leading g_ added.

```cpp
int g_Shutdown; // Good: Really need this global variable
const bool gcb_Loaded;
```

## Local Variables

Initialize variables in the declaration.

```cpp
void f(){
  int i;
  i = f();      // Bad
  int j = g();  // Good
  vector<int> v = {1, 2};  // Good
}
```

Put variable declaration before loop.

```cpp
// Inefficient implementation:
for (int i = 0; i < 1000000; ++i) {
  Foo f;  // My ctor and dtor get called 1000000 times each.
  f.DoSomething(i);
}

// It may be more efficient to declare such a variable used in a loop outside that loop:
Foo f;  // My ctor and dtor get called once each.
for (int i = 0; i < 1000000; ++i) {
  f.DoSomething(i);
}
```

## Static and Global Variables

If you need a static or global variable of a class type, consider initializing a raw pointer (not a "smart" pointer) which will never be freed.
Objects with static storage duration, including global variables, static variables, static class member variables, and function static variables, must be [Plain Old Data](http://en.cppreference.com/w/cpp/concept/PODType) (POD): only ints, chars, floats, or pointers, or arrays/structs of POD.

In C++11 the idea of a POD is to capture basically two distinct properties:

* It supports static initialization
* Compiling a POD in C++ gives you the same memory layout as a struct compiled in C.

You can check if class isPOD with "[std::is_pod](http://www.cplusplus.com/reference/type_traits/is_pod/)".

```cpp
A POD struct is a non-union class that is both a trivial class and a standard-layout class, and has no non-static data members of type non-POD struct, non-POD union (or array of such types). Similarly, a POD union is a union that is both a trivial class and a standard layout class, and has no non-static data members of type non-POD struct, non-POD union (or array of such types). A POD class is a class that is either a POD struct or a POD union.
```

## Implicit Conversions

Do not define implicit conversions. Use the explicit keyword for conversion operators and single-argument constructors.

```cpp
class Foo {
  explicit Foo(int x, double y); // Good
  ...
};

void Func(Foo f);
Func({42, 3.14});  // Error, as expected
```

One-argument constructors that are not copy or move constructors should generally be marked explicit.

## Structs vs. Classes

Use a struct only for passive objects that carry data; everything else is a class.

## Class const methods

Always make class methods ‘const’ when they do not modify any class variables.

## Declaration Order

Use the specified order of declarations within a class: "public:" before private:, methods before data members (variables), etc.
place constructors and assignment operators before other methods.

* Using-declarations
* list of friend classes
* Typedefs and Enums
* public class methods
* protected class methods
* private class methods
* public class variables
* protected class variables
* private class variables

## Parameter Ordering

When defining a function, parameter order is:

* inputs
* parameters that are both input and output
* outputs

Don't use function arguments as both input and optput. Prefer separate variable for function output and separate variable for function input.
Always use const for parameters that don't change inside function.

## Write Short Functions

Prefer small and focused functions.

## Don't write comments for obvious things

* Do not be unnecessarily verbose or state the completely obvious. Notice below that it is not necessary to say "returns false otherwise" because this is implied.

```cpp
// Returns true if the table cannot hold any more entries.
bool IsTableFull();
```

* When commenting constructors and destructors, remember that the person reading your code knows what constructors and destructors are for, so comments that just say something like "destroys this object" are not useful.
* Comments should be descriptive ("Opens the file") rather than imperative ("Open the file");
* Do not duplicate comments in both the .h and the .cc. Duplicated comments diverge.
* Tricky or complicated code blocks should have comments before them.

## Use newline for logical separation

Note: You can use tools like clang-format for automatic formatting.

Prefer code with newline between logical blocks:

Good:

```cpp
    GLuint vertexShader;
    GLuint fragmentShader;
    GLint linked = GL_FALSE; // Ok, variables separated from functions that use them

    vertexShader = LoadShader(GL_VERTEX_SHADER, vShaderStr);
    fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fShaderStr);
```

Appropriate:

```cpp
    GLuint vertexShader;
    GLuint fragmentShader;
    GLint linked = GL_FALSE; // Still ok, but may be better
    vertexShader = LoadShader(GL_VERTEX_SHADER, vShaderStr);
    fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fShaderStr);
```

Bad, total chaos:

```cpp
    GLuint vertexShader;

    GLuint fragmentShader;

    GLint linked = GL_FALSE;
    vertexShader = LoadShader(GL_VERTEX_SHADER, vShaderStr);

    fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fShaderStr);
```

## Make nice columns

Indent the names of class variables and class methods to make nice columns. The variable type or method return type is in the first column and the variable name or method name is in the second column.

```cpp
class ExampleClass {
  public:
    float getLength( void ) const;
    const float * toFloatPtr( void ) const;

  public: // Good: Padding inside struct/class
    float x;
    float y;
    float z;
}
```

The * of the pointer is in the first column because it improves readability when considered part of the type.

Align assignment to make nice columns where possible.

Nice:

```cpp
foo  = "abc";
bar1 = "defDEF";
baz  = "ghi";
baz1 = "jklm";

yourveryverylongvariablenamemaybehere = "bdam"; // Notice newline separation
```

Ok, but above ? is better:

```cpp
foo = "abc";
bar1 = "defDEF";
baz = "ghi";
baz1 = "jklm";
```

Bad:

```cpp
a = array([[1,0, 0], // Forgotten spaces, needs padding [ 1, 0, 0] e.t.c.
           [0,32,0],
           [0,0, 1]])
a = array([[1,0, 0],[0,32,0],[0,0, 1]])
```

Good:

```cpp
a = array([ [ 1, 0,     0 ], // Notice padding
            [ 0, 31232, 0 ],
            [ 0, 0,     1 ] ]);
```

But don't align operators or arguments:

```cpp
abcd = hello(34, 12) +   fgh( 2,  3); // Bad
foo  =  boop( 1,  5) + thing(12, 19); // Bad
fun(123456, 7,  89,    0) // Bad
fun(    12, 3, 456, 7890) // Bad
matrix( 1, 0,
        0, 1 ); // Bad, pass array/container for matrix as argument
matrix([ 1, 0,
         0, 1 ]); // Good
```

## Reference Arguments

All parameters passed by reference must be labeled const.

```cpp
void Foo(const string &in, string *out);
```

An out argument of a function should be passed by reference except rare cases where it is optional in which case it should be passed by pointer.

```cpp
void MyClass::getSomeValue(OutArgumentType& outArgument) const // Good, bad is: doSomething(OutArgumentType* outArgument)
```

## DELETE and RELEASE (macro or functions)

Prefer the following:
SafeDelete should be used for memory allocated with new
SafeRelease should be called for com objects (like directx objects) and "under the hood" is doind something like this

```cpp
inline template< class T > void SafeDelete( T*& p )
{
    if(p != nullptr) {
        delete p;
        p = nullptr;
    }
}

inline template< class T > void SafeDeleteArray( T*& p )
{
    if(p != nullptr) {
        delete[] p;
        p = nullptr;
    }
}

inline template< class T > void SafeRelease( T*& p )
{
    if(p) {
        p->Release();
        p = nullptr;
    }
}
```

They compile down to EXACTLY the same code in the end as macro.

Macro are also allowed, but be very cautious with macros.
Prefer inline functions, enums, and const variables to macros.

Instead of

```cpp
#define SAFE_RELEASE(p) { if ( (p) ) { (p)->Release(); (p) = nullptr; } }
#define SAFE_DELETE(a) { if( (a) != nullptr ) delete (a); (a) = nullptr; }
```

use inline templates.

Also remember that ISO C++ specifies, that delete on a NULL pointer just doesn't do anything.

## Macro

Instead of using a macro to store a constant, use a const variable.
Instead of using a macro to "abbreviate" a long variable name, use a reference.

## 0 and nullptr or NULL

Use 0 for integers, 0.0 for reals, nullptr for pointers, and '\0' for chars.
Avoid using NULL.

Also remember about expressions and floating point types:

```cpp
float x = 1 / 2; // Equals 0
float x = 1 / 2.0f; // Equals 0.5
```

## Use precision specification for floating point values unless there is an explicit need for a double

```cpp
// Good:
float f = 0.5f;
float g = 1.0f;
double k = 0.1;
// Bad:
float f = 0.5;
float g = 1.f;
double k = 0.;
```

## sizeof

Prefer sizeof(varname) to sizeof(type).

## auto

"auto" is permitted, for local variables only, when it increases readability, particularly as described below. Do not use auto for file-scope or namespace-scope variables, or for class members.
Never initialize an auto-typed variable with a braced initializer list.
Programmers have to understand the difference between auto and const auto& or they'll get copies when they didn't mean to.

## Braced Initializer List

Never assign a braced-init-list to an auto local variable. In the single element case, what this means can be confusing.

```cpp
auto d = {1.23};        // d is a std::initializer_list<double>
auto d = double{1.23};  // Good -- d is a double, not a std::initializer_list.
```

## Exceptions

We do not use C++ exceptions.
Exceptions can be hard to maintain. For existing code, the introduction of exceptions has implications on all dependent code.
Emscripten don't allow them.

## Threads

Emscripten don't like them, use

```cpp
#ifdef __EMSCRIPTEN__
// thread code with browser support
#else
// thread code
#endif
```

to create threads.

## Smart pointers

Smart pointers are allowed.

## RTTI

Avoid using Run Time Type Information (RTTI): dynamic_cast, typeid.

## Tests

Use CppUnit, Google Test or any other  [testing frameworks](https://en.wikipedia.org/wiki/List_of_unit_testing_frameworks).
Unit tests and performance tests should be placed in the same directory as the functionality they're testing.
Use compile autotests to see whether a C++ feature is supported by all compilers in the test farm.
Don't forget to write regression tests.

## Continuos integration

Use jenkins, AppVeyor, Travis or any other [CI tools](https://en.wikipedia.org/wiki/Comparison_of_continuous_integration_software).

## Code analysis

Use [cppcheck](http://cppcheck.sourceforge.net/) or any other tool you want.

## Casting

Use C++-style casts like `static_cast<float>(double_value)` or brace initialization for conversion of arithmetic types like `int64 y = int64{1} << 42`. Do not use cast formats like int y = (int)x or int y = int(x) (but the latter is okay when invoking a constructor of a class type).

```cpp
  float x = 2.2;
  double y = double{ x }; // Ok
  float z = float{ y }; // Ok, but error: conversion from 'type_1' to 'type_2' requires a narrowing conversion
  int g = static_cast<int>(y); // Ok
```

The problem with C casts is the ambiguity of the operation. Do not use cast formats like int y = (int)x or int y = int(x).

* Use brace initialization to convert arithmetic types (e.g. int64{x}). This is the safest approach because code will not compile if conversion can result in information loss. The syntax is also concise.
* Use static_cast as the equivalent of a C-style cast that does value conversion, when you need to explicitly up-cast a pointer from a class to its superclass, or when you need to explicitly cast a pointer from a superclass to a subclass. In this last case, you must be sure your object is actually an instance of the subclass.
* Use "const_cast" to remove the const qualifier (see const) only if its really necessary. Avoid use of "const_cast". When object is needed to be modified, but only const versions are accessible, create a function that clearly gives an editable version of the object.
* Use reinterpret_cast to do unsafe conversions of pointer types to and from integer and other pointer types. Use this only if you know what you are doing and you understand the aliasing issues.
* Prefer the brace initialisation to in initialize objects and values of unknown type in generic code;

```cpp
template <typename T>
void func()
{
  T value = T{};
}
```

## Preincrement and Predecrement

Use preincrementation (++i) whenever possible. The semantics of postincrement (i++) include making a copy of the value being incremented, returning it, and then preincrementing the “work value”.
Use prefix form (++i) of the increment and decrement operators with iterators and other template objects.

## Use of const

Use const whenever it makes sense.
With C++11, constexpr is a better choice for some uses of const.
Prefer enums to define constants over "static const int" or "define".
Declared variables and parameters can be preceded by the keyword const to indicate the variables are not changed (e.g., const int foo).
Class functions can have the const qualifier to indicate the function does not change the state of the class member variables (e.g., class Foo { int Bar(char c) const; };).
Prefer "const int* foo" to "int const *foo" (same result).
In C++11, use constexpr to define true constants (fixed at compilation/link time) or to ensure constant initialization.

```cpp
// Good:
const int* p; // pointer to const int
int* const p; // const pointer to int
const int* const p; // const pointer to const int
// Bad:
int const *p;           // Perfer "const int *p;"
```

## Integer Types

If your variable represents a value that could ever be greater than or equal to 2^31 (2GiB), use a 64-bit type such as int64.
Don't use an unsigned type where possible (especially don't use unsigned type in loop).

## Documentation

Every source and header file must contain a license and copyright statement at the beginning of the file.

Prefer Doxygen and use [Doxygen Special Commands](https://www.stack.nl/~dimitri/doxygen/manual/commands.html).
You can [automate doxygen documentation generation in Visual Studio](http://www.mantidproject.org/Visual_Studio_Doxygen_Setup)

File documentation style example:

```cpp
/**
* @file
*
* @copyright Copyright (c) 2016 Exarion Team, Inc. All Rights Reserved.
*
* @license This file is distributed under the MIT License. See LICENSE.TXT for details.
*
* @brief This header file defines the ChronoTimer class.
*
* @author derofim@yandex.ru (Denis Trofimov).
*
* @project Exarion engine
*
**/
```

Class documentation style example:

```cpp
  /**
  * @brief Class based on std::chrono functionality to measure elapsed time.\n
  *
  * ChronoTimer allows to create pausable timer based on std::chrono.
  * Example usage:
  * -# Create timer\n
  *    exa::ChronoTimer myTimer;
  * -# Start timer\n
  *    myTimer.start();
  * -# Get timer value in seconds\n
  *    myTimer.get();
  * -# Get timer value in nanoseconds\n
  *    myTimer.get<std::chrono::nanoseconds>();
  * -# Pause timer\n
  *    myTimer.pause();
  * -# Unpause timer\n
  *    myTimer.unpause();
  * -# Stop timer (calls reset()) and get timer value\n
  *    auto timerResult = myTimer.stop();
  * -# Reuse timer for new measurements\n
  *    myTimer.start();
  **/
```

Function documentation style example:

```cpp
/** Restart timer execution.  Equals stop() and start() **/
void restart() override;
```

## 64-bit Portability

Code should be 64-bit and 32-bit friendly.
Don't use printf() where possible.

## Aliases

Prefer "using" over "typedef". The using syntax has an advantage when used within templates.
When defining a public alias, document the intent of the new name, including whether it is guaranteed to always be the same as the type it's currently aliased to, or whether a more limited compatibility is intended.

```cpp
template <typename T> using my_type = whatever<T>;
```

Local convenience aliases are allowed in function definitions, private sections of classes, explicitly marked internal namespaces, and in .cc files.

Use type aliases in classes where possible if its helps readability and maintenance:

```cpp
class Student
{
public:
  typedef std::vector<Teacher*> Teachers; // Good
  const Teachers& getTeachers();
private:
  Teachers m_teachers;
};
```

The `typedef` makes it easier to read and makes future possible modifications to what is a collection of Teachers easier (for instance, changing `std::vector<>` to `std::list<>`)

## RAII

* RAII guarantees that the resource is available to any function that may access the object (resource availability is a class invariant).
* RAII guarantees that all resources are released when the lifetime of their controlling objectends, in reverse order of acquisition.
* Never use malloc and free. Use C++'s "new" operator or smart pointers.

## Inlining

Use inline keyword (The inline keyword makes it easier for the compiler to apply this optimization, by allowing the function definition to be visible in multiple translation units, but using the keyword doesn't mean the compiler has to inline the function, and not using the keyword doesn't forbid the compiler from inlining the function).
Stop inlining virtual methods: You can't inline virtual methods under most circumstances.
Stop inlining constructors and destructors: Constructors and destructors are often significantly more complex than you think they are, especially if your class has any non-POD data members.

Inline functions must be in a .h file. If your inline functions are very short, they should go directly into your .h file (Inline functions are declared in the header because, in order to inline a function call, the compiler must be able to see the function body. For a naive compiler to do that, the function body must be in the same translation unit as the call.).

Functions declared in the header must be marked inline because otherwise, every translation unit which includes the header will contain a definition of the function.

* Access functions are to be inline.
* Forwarding functions are to be inline.
* Constructors and destructors must *not* be inline.

Move Inline Method Bodies Out of Class Definitions. Instead of inlining method bodies in a class definition, instead declare the method regularly and define it in the header file below the class definition with an inline specifier:

```cpp
class foo
{
public:
 void bar();
};

inline void foo::bar()
{
 /* do something */
}
```

## Naming variables

Use lowerCamelCase for variable names.
Use lowerCamelCase_UpperCamelCase for variable names containing "_".

Avoid short or meaningless names (e.g. "a", "rbarr", "nughdeget") and making abbreviations.
Single character variable names are only okay for counters and temporaries, where the purpose of the variable is obvious.

```cpp
int integralValue;

// private class members:
Timepoint m_StartMark;
bool mb_Paused;
const bool mcb_Debug;
```

## Type Names

Type names start with a capital letter and have a capital letter for each new word, with no underscores: MyExcitingClass, MyExcitingEnum.

```cpp
exa::ChronoTimer fpsTimer;
```

## File and directory names

Use CamelCase for source file names and lowerCamelCase for directory names.

## Useful class names

For "Writer" class with `<name>` use as:
`<name>Writer`

```cpp
class Tool; // Bad: Doesn't describe anything. A tool which does what?
class AbstractTool; // Good
class ToolInterface; // Good
class DebugTool; // Good
```

Prefer class naming convention:

* Abstract // (prefix) Class with virtual methods that can be overridden, and some code, but at least one pure virtual method that makes the class not instantiable
* Interface // (suffix) Class with only pure virtual methods (i.e. without any code)
* Writer
* Reader
* Handler
* Helper
* Container
* Protocol
* Controller
* Converter
* View
* Factory
* Entity
* Attribute
* Provider
* Service
* Element
* Manager
* Node
* Option
* Context
* Item
* Base
* Editor
* Designer

```cpp
class ToolInterface
{
  public:
  // Empty virtual destructor for proper cleanup
  virtual ~ToolInterface() {}

  virtual void Method1() = 0;
  virtual void Method2() = 0;
};


class AbstractTool
{
  public:
  virtual ~AbstractTool();

  virtual void Method1();
  virtual void Method2();
  void Method3();

  virtual void Method4() = 0; // make not instantiable
};
```

## Inheritance

Prefer composition over inheritance as it is more malleable / easy to modify later, but do not use a compose-always approach.
When using inheritance, make it public.

Inheritance:

```cpp
class Manager : Person, Employee { // The Manager object is inherited from Employee and Person.
   ...
}
```

Composition:

```cpp
Class Manager { // The Manager object is composed as an Employee and a Person.
   private m_Title;
   private m_Employee;
   ...
   public Manager(Person p, Employee e)
   {
      m_Title = e.Title;
      m_Employee = e;
      ...
   }
}
```

Use multiple inheritance only when at most one of the base classes has an implementation and all other base classes must be pure interface classes tagged with the Interface suffix.

## Class Data Members

Data members of classes, both static and non-static, are named like ordinary nonmember variables, but with a leading "m_".

```cpp
  private:
    /** The timepoint stored when the timer was paused last time **/
    timepoint m_PausedMark;

    /**  Is timer running **/
    bool m_Running;

    /** Is timer paused **/
    bool m_Paused;
```

## Constant Names

Variables declared constexpr or const, and whose value is fixed for the duration of the program, are named with a leading "c_" followed by mixed case. All such variables with static storage duration (i.e. statics and globals, see Storage Duration for details) should be named this way. For example:

```cpp
const int c_DaysInAWeek = 7;
// In class:
class FooClass {
  public:
    c_MyConstValue;
  private:
    mc_MyConstPrivateValue;
};
```

## Function Names

Use lowerCamelCase

```cpp
    /** Set duration elapsed when the timer was running and not paused **/
    void setTotalRunning(const Duration& duration);
```

One of the reasons for this is the range-based for-loop (since C++11). If you want to make your class work with the range-for, you have to define functions called begin and end for that class. The names must be exactly begin and end, so e.g. Begin and End are not supported.

Function declaration order should match function definition order.

Use the override specifier on all derived from a base class overriding functions.

You may use final keyword when overriding the virtual method and requiring that no further subclasses can override it.

Don't annotate a method with more than one of the virtual, override, or final keywords.

## Namespace Names

Namespace names are all lowerCamelCase. Prefer lowercase namespaces by creting inner namespaces instead of longLowerCamelCaseNamespace.

```cpp
namespace chronics; // Good
namespace fastElectronics; // Good
namespace exaTiming; // Bad, may split into "exa" and "timing".
namespace exa { // Good
namespace timing {
}
}
```

## Macro Names

Macro should be named with all capitals and underscores.

## Enumerator Names

Enumerators (for both scoped and unscoped enums) should be named like macros.

```cpp
enum AlternateUrlTableErrors {
  OK = 0,
  OUT_OF_MEMORY = 1,
  MALFORMED_INPUT = 2,
};
```

Prefix is allowed, but prefer enum without prefix:

```cpp
// Good, use as Color::RED e.t.c.
enum Color {
  RED,
  GREEN,
  BLUE
};
// Allowed
enum Color {
  COLOR_RED,
  COLOR_GREEN,
  COLOR_BLUE
};
```

## Comment Style

Use either the ```//, /** **/ or /* */``` syntax, as long as you are consistent.
Code that is not used (commented out) and not part of an explanation shall be deleted.

## Output arguments

Output arguments to methods / functions (i.e., variables that the function can modify) are passed by pointer, not by reference. E.g.:

```cpp
int exampleMethod(FooThing input, BarThing* output);
```

## Deprecation code

You can use [[deprecated]] on separate line:

```cpp
[[deprecated]]
void foo() {
    // ...
}
```

## ToDo code

Use doxygen @todo comment style.

## Function Argument Comments

Prefer

```cpp
ProductOptions options;
options.setPrecision(7);
options.setCache(ProductOptions::c_DontUseCache);
const DecimalNumber product = calculateProduct(values, options, /*completion_callback=*/nullptr);
```

to

```cpp
const DecimalNumber product = CalculateProduct(values, 7, false, nullptr); // Bad: What are these arguments?
```

## Tabulation

Use 4 spaces for tabulation.
Set editor settings to use 4 spaces. Instructions for VS2015 [Options, Text Editor, All Languages, Tabs](https://msdn.microsoft.com/en-us/library/7sffa753.aspx).
No whitespace at the end of a line.

In all cases, prefer spaces to tabs in source files. People have different preferred indentation levels, and different styles of indentation that they like; this is fine. What isn’t fine is that different editors/viewers expand tabs out to different tab stops. This can cause your code to look completely unreadable, and it is not worth dealing with.

## Line Length

Each line of text in your code should be at most 100 characters long.
Example 100 characters text generated with [blindtextgenerator](http://www.blindtextgenerator.com/lorem-ipsum):

```cpp
Far far away, behind the word mountains, far from the countries Vokalia and Consonantia, there live.
```

## Classes

Never specify public or protected member data in a class.
Use getters and setters ([example snippet](https://gist.github.com/derofim/579bba8b7bfb28e1c107c9d3e0d3ddc5#file-encapsulate-cpp)).
Visual Assist allows automatic creation of getters and setters (Refactor (VA X) -> Encapsulate Field). ou can customise the format by modifying Refactor Encapsulate Field snippet. You can find more on customising snippets [here](https://docs.wholetomato.com/default.asp?W171).

[Useful VA snippets](https://gist.github.com/derofim/579bba8b7bfb28e1c107c9d3e0d3ddc5) and [snippet guide](https://docs.wholetomato.com/default.asp?W262).

## Use compute, find, initialize in function names

If function just calculates/changes something, then prefer compute as part of function name.

```cpp
void computeDuration();
valueSet->computeAverage();
matrix->computeInverse()
```

If function just finds something, then prefer find as part of function name.

```cpp
vertex.findNearestVertex();
matrix.findMinElement();
```

If function just initializes something, then prefer initialize as part of function name.

```cpp
engine.initialize();
```

## Conditionals

* Any spaces inside parentheses
* If and else keywords belong on separate lines
* Proper space after if and before.
* Always prefer braces

```cpp
if ( condition ) {  // Good - proper space after IF and before {.
} else {          // Spaces around else.
}
```

* Pad parenthesized expressions with spaces

```cpp
// Good:
if ( x ) {
}
x = ( y * 0.5f + (y * 0.5f) ); // Note padding for inner parentheses
// Bad:
if (x) {
}
x = (y * 0.5f + (y * 0.5f));
```

## Loops and Switch Statements

* Proper space after Loop/Switch and before
* Don’t use default labels in fully covered switches over enumerations.
* Not fully covered switch statements should always have a default case.  If the default case should never execute, simply assert:

```cpp
switch (var) {
  case 0: {t
    ...
    break;
  }
  case 1: {
    ...
    break;
  }
  default: {
    assert(false);
    break;
  }
}
```

Every case must have a break (or return) statement at the end or a comment to indicate that there's intentionally no break, unless another case follows immediately.

* Always prefer braces

Prefer

```cpp
while (condition) continue;
```

over

```cpp
while (condition);
```

Prefer no spaces inside parentheses in loops.

```cpp
for (int i = 0; i < 5; ++i) {
for (auto x : counts) {
```

## Pointer and Reference Expressions

Use space preceding:

```cpp
x = *p;
p = &x;
x = r.y;
x = r->y;
char *c;
const string &str;
```

Always define pointer variables on new line:

```cpp
int *pp, *pt; // Bad (and worse is int *pp, pt)
```

Good:

```cpp
int *pp;
int *pt;
```

## Boolean Expressions

When you have a boolean expression that is longer than the standard line length, be consistent in how you break up the lines.
Start operators at the beginning of the new lines. Commas go at the end of wrapped lines.

```cpp
if (this_one_thing > this_other_thing
    && a_third_thing == a_fourth_thing
    && not_yet_another
    && last_one) {
  ...
}
```

Prefer operators before statemant inside condition:

```cpp
// Bad: "&&" at the end, hard to read.
if (this_one_thing > this_other_thing &&
    a_third_thing == a_fourth_thing &&
    not_yet_another &&
    last_one == "itsString") {
    call_function(a, b, c);
}

// Good: "&&" at the beginning
if (this_one_thing > this_other_thing
    && a_third_thing == a_fourth_thing
    && not_yet_another
    && last_one == "itsString") {
    call_function(a, b, c);
}

// Best: condition splited to meaningful "const bool" variables.
const bool cb_OneBiggerOther = this_one_thing > this_other_thing;
const bool cb_ThirdEqualsFourth = a_third_thing == a_fourth_thing;
const bool cb_LastEqualsItsString = last_one == "itsString";
// Also use "!yet_another" instead of "not_yet_another".
const bool cb_OneThirdAnother = cb_OneBiggerOther && cb_ThirdEqualsFourth && !yet_another;
const bool isCallAvailable = cb_OneThirdAnother && cb_LastEqualsItsString;
if ( isCallAvailable ) {
    call_function(a, b, c);
}
```

## Return Values

Use parentheses in "return expr;" only where you would use them in "x = expr;".

```cpp
return (some_long_condition &&
        another_condition);
return (now() - m_StartMark);
return defaultDuration;
```

Don't use else after return. So use:

```cpp
  if (foo) {
    return 1;
  }
  return 2;
```

instead of:

```cpp
  if (foo) {
    return 1;
  } else {
    return 2;
  }
```

## Preprocessor Directives

The hash mark that starts a preprocessor directive should always be at the beginning of the line. Even when preprocessor directives are within the body of indented code, the directives should start at the beginning of the line!

```cpp
// Good - directives at beginning of line
  if (lopsided_score) {
#if THAT_IS_NICE      // Correct -- Starts at beginning of line
    DropEverything();
#endif
    BackToNormal();
  }
// Bad - indented directives
  if (lopsided_score) {
    #if DISASTER_PENDING  // Wrong!  The "#if" should be at beginning of line
    DropEverything();
    #endif                // Wrong!  Do not indent "#endif"
    BackToNormal();
  }
```

## Class Format

* Any base class name should be on the same line as the subclass name, subject to the 80-column limit.
* The public:, protected:, and private: keywords should be indented 2 space.
* Except for the first instance, these keywords should be preceded by a blank line. This rule is optional in small classes.
* Do not leave a blank line after these keywords.
* The public section should be first, followed by the protected and finally the private section (methods first, then members, see Declaration Order).

```cpp
    class ChronoTimer : public ATimer<ticks> {
     public:
        ChronoTimer();

        ~ChronoTimer();

        /** Start timer execution **/
        void start() override;
    protected:
        /** Recalculate timer durations and states **/
        void update();
    private:
        /** The duration elapsed when the timer was running and not paused **/
        duration m_TotalRunning;
    };
```

## Constructor Initializer Lists

Prefer constructor initializer lists be all on one line when everything fits on one line.  When the list spans multiple lines, put each member on its own line and align them:

```cpp
// When everything fits on one line:
MyClass::MyClass(int var) : m_someVar(var) {
  doSomething();
}

// When the list spans multiple lines, put each member on its own line and align them:
MyClass::MyClass(int var)
    : m_someVar(var),        // 4 space indent
      m_otherVar(var + 1) {  // lined up
  doSomething();
}

```

## Namespace Formatting

The contents of namespaces are not indented.
Namespaces do not add an extra level of indentation.

```cpp
namespace foo {
namespace bar {
} // namespace foo
} // namespace bar
```

## Anonymous Namespaces

Make anonymous namespaces as small as possible, and only use them for class declarations.

Anonymous namespaces are a great language feature that tells the C++ compiler that the contents of the namespace are only visible within the current translation unit, allowing more aggressive optimization and eliminating the possibility of symbol name collisions.

Good:

```cpp
namespace {
class StringSort {
...
public:
  StringSort(...)
  bool operator<(const char *RHS) const;
};
} // anonymous namespace
```

Bad:

```cpp
namespace {

class StringSort {
...
public:
  StringSort(...)
  bool operator<(const char *RHS) const;
};

void runHelper() {
  ...
}

bool StringSort::operator<(const char *RHS) const {
  ...
}

} // end anonymous namespace
```

## Operators

```cpp
// Assignment operators always have spaces around them.
x = 0;
// No spaces separating unary operators and their arguments.
x = -5;
++x;
// Other binary operators usually have spaces around them
v = w * x + y / z;
// Inner parentheses should have no internal padding.
v = ( w * (x + z) ); // Good
v = (w * (x + z)); // Bad
v = (w * ( x + z )); // Bad
g = ( v + ((x + (x + z)) + z) ); // Good
```

## Templates

UpperCamelCase (no underscore separation) for template arguments.
Place "template" on separate line.
Use padding after "template" (before "<>").
Use the brace initialisation to in initialise objects and values of unknown type in generic code;

```cpp
template <typename T>
void func()
{
  T value = T{};
}
```

Prefer "typename" instead of "class" (the difference is "nothing") [where possible](http://stackoverflow.com/a/11311432).

```cpp
template <typename T>     // Good: Padding after "template"; T is UpperCamelCase; "typename" used instead of "class".
class CompressionUtil     // Good: Class name is UpperCamelCase and meaningful.
{                         // Good: "{" on new line.
...
};
```

## Casts

```cpp
// No spaces inside the angle brackets
vector<string> x;
y = static_cast<char*>(x);
// Spaces between type and pointer are OK, but be consistent.
vector<char *> x;
set<list<string>> x;        // Permitted in C++11 code.
```

Avoid C-style casts when possible:

```cpp
// Wrong
char* blockOfMemory = (char* ) malloc(data.size());

// Correct
char *blockOfMemory = reinterpret_cast<char *>(malloc(data.size()));
```

## Windows and Visual Studio

* Keep as close as you can to the underlying C++ types. For example, use "const TCHAR *" instead of "LPCTSTR".
* When compiling with Microsoft Visual C++, set the compiler to warning level 3 or higher, and treat all warnings as errors.
* "#pragma once" is pretty widely [supported](https://en.wikipedia.org/wiki/Pragma_once#Portability), you can use it.

## Boolean variables

Use "b" prefix for boolean variables.

```cpp
        /**  Is timer running **/
        bool mb_Running;

        bool bError; // Don't use isError/isNotError
```

## Abbreviations

Abbreviations must use lowerCamelCase (in the start of variable name) or UpperCamelCase (in the middle of variable name).

```cpp
exportHtmlSource(); // Bad: exportHTMLSource();
openDvdPlayer();    // Good: openDVDPlayer();
dvdReader();         // Good
```

## Types to use

* Do not use unsigned types to mean “this value should never be < 0”. For that, use assertions or run-time checks (as appropriate).
* Use size_t for object and allocation sizes, object counts, array and pointer offsets, vector indices, and so on. The signed types are incorrect and unsafe for these purposes (e.g. integer overflow behavior for signed types is undefined in the C and C++ standards, while the behavior is defined for unsigned types.) The C++ STL is a guide here: they use size_t and foo::size_type for very good reasons.
* Use size_t directly in preference to std::string::size_type and similar.
* In cases where the exact size of the type matters (e.g. a 32-bit pixel value, a bitmask, or a counter that has to be a particular width), use one of the sized types.

## Type name

Prefer UpperCamelCase type names.

## Paramater name

Prefer lowerCamelCase for paramater name based on its type.

```cpp
void setTopic(Topic* topic)
void connect(Database* database)
```

## Use "n, s and Id" in variable name where possible

```cpp
vector<Point>  points;
int            values[];
```

```cpp
nPoints, nLines
```

```cpp
tableId, clientId
```

## Use  i, j, k... in loops where possible

```cpp
for (int i = 0; i < nTables); i++) {
}
```

## Prefer "is" in boolean function name

```cpp
        /** Is timer paused **/
        inline const bool isPaused() const {
            return  mb_Paused;
        }
```

If "is" not appropriate use has/an/should e.t.c.

```cpp
  bool hasLicense();
  bool canEvaluate();
  bool shouldSort();
```

## Prefer symmetric names

* get/set
* add/remove
* create/destroy
* start/stop
* insert/delete
* increment/decrement
* old/new
* begin/end
* first/last
* up/down
* min/max
* next/previous
* old/new
* open/close
* show/hide
* suspend/resume
* e.t.c.

## Prefer full names

```cpp
int maximumAverage = computeAverage() / c_CurrentAverage;   // Don't use compAvg(), maxAvg or c_cntAvg
```

cmd    <->    command
cp     <->    copy
pt     <->    point
comp   <->    compute
init   <->    initialize
max    <->    maximum
cnt    <->    current

Don't use that rule for abbrevations (html, cpu)

## Don't use "p" or "ptr" prefix for pointers/parameters

Line* line; // Don't use Line* pLine; or Line* linePtr;

## Initialize variables

* Prefer "char buffer[32] = {};" to "char buffer[32] = { 0 };"
* Always initialize variables

```cpp
  char x, *y, z; // Bad
  char x = '\0', *y = nullptr, z = '\0'; // Good
```

## Language

Use English language in source code. All code is ascii only (7-bit characters only).

## Comparison and boolean check

* Prefer if (bSomething) to if (bSomething == true) for boolean values.
* Prefer if (something) to if (something != 0) for int values.
* Prefer if (myPtr) to myPtr != nullptr.
* Prefer "bool result = condition ? true : false;" to "bool result = condition != false;" for variable declaration (same for int, double e.t.c.).
* Prefer (foo == 0) to (0 == foo).
* Prefer comparison using epsilon for floating point types like:

```cpp
template<class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
almostEquals(T a, T b)
{
    if(!std::isfinite(a) || !std::isfinite(b)) return false;
    T maximum = std::max( { T{1.0}, std::fabs(a) , std::fabs(b) } );
    return std::fabs(a - b) < std::numeric_limits<T>::epsilon() * maximum;
}
```

[Usage example](https://gist.github.com/derofim/b03cb371688bccbb37cead77b5f8f053#file-source-cpp)

## Avoid "using namespace std;" e.t.c

Use "using" only where it's necessary.

## Include Units in Names

If a variable represents time, weight, or some other unit then include the unit in the name so developers can more easily spot problems. For example:
uint32 x;
uint32 y;

## Avoid "magic numbers"

Prefer constexpr or const variable to "magic number".

## Floating point constants

```cpp
double total = 0.0;    // Bad:  double total = 0;
double speed = 3.0e8;  // Bad:  double speed = 3e8;
double total = 0.5;    // Bad:  double total = .5;
```

## Containers

Prefer 1D (one-dimensional approach) to 2D (two-dimensional approach) [for 2D array representation](http://stackoverflow.com/a/17260533). For dense matrices, the 1D approach is likely to be faster since it offers better memory locality and less allocation and deallocation overhead. Dynamic-1D consumes less memory than the 2D approach. The latter also requires more allocations.

Two-dimensional approach (Bad):

```cpp
int **ary = new int*[sizeY]; // Bad
for(int i = 0; i < sizeY; ++i) { // Create
    ary[i] = new int[sizeX];
}
// May be used as ary[i][j]
for(int i = 0; i < sizeY; ++i) { // Cleanup
    delete[] ary[i];
}
delete[] ary;
// ... You could also declare array as:
auto array = new double[M][N](); // Bad
```

One-dimensional approach (Good):

```cpp
int *ary = new int[sizeX*sizeY]; // Good
// May be used as ary[i*sizeY+j]
delete[] ary;
```

If you want to have a matrix class that's always, say, 4x4, prefer container [like std::array<float, 4*4>](http://cpp.sh/2tqe) or std::dynarray:

```cpp
  constexpr int sizeX = 4;
  constexpr int sizeY = 4;

  // Fill with identity matrix
  std::array<float, 4*4> m_array{ 1, 0, 0, 0,
                                  0, 1, 0, 0,
                                  0, 0, 1, 0 ,
                                  0, 0, 0, 1 };

  // Prints identity matrix
  for(size_t i = 0; i < sizeX; ++i) {
    for(size_t j = 0; j < sizeY; ++j) {
        std::cout << m_array.at(i*sizeY+j) <<  " ";
    }
    std::cout << "\n";
  }
```

## Lambda

Format Lambdas Like Blocks Of Code:

```cpp
std::sort(foo.begin(), foo.end(), [&](Foo a, Foo b) -> bool { // Good
  return a.bam < b.bam;
});
std::sort(foo.begin(), foo.end(), [&](Foo a, Foo b) -> bool { return a.bam < b.bam; }); // Bad
```

Always write parentheses for the parameter list, even if the function does not take parameters.

```cpp
[]() { doSomething(); } // Good, bad is: [] { doSomething(); }
```

You have to explicitly specify the return type, if the lambda contains more than a single expression.

## Braced Initializer Lists

Act as-if the braces were parentheses in a function call.

```cpp
foo({a, b, c}, {1, 2, 3});

llvm::Constant *Mask[] = {
    llvm::ConstantInt::get(llvm::Type::getInt32Ty(getLLVMContext()), 0),
    llvm::ConstantInt::get(llvm::Type::getInt32Ty(getLLVMContext()), 1),
    llvm::ConstantInt::get(llvm::Type::getInt32Ty(getLLVMContext()), 2)};
```

## Language and Compiler Issues

* Treat Compiler Warnings Like Errors.
Any Compiler warning that annoys you can be fixed by massaging the code appropriately:

```cpp
if (V = getValue()) { // Bad: warning about == operator.
  ...
}
if ((V = getValue())) { // Dood: no warning
  ...
}
```

On Visual C++, I use /W4 and /WX (treat warnings as errors). VC also has /Wall. Use some [set of extra-paranoid flags](http://stackoverflow.com/a/401276).

* Write Portable Code
* Do not use RTTI or Exceptions
* Do not use Static Constructors.
Static constructors and destructors (e.g. global variables whose types have a constructor or destructor) should not be added to the code base:
  * Order of initialization is undefined between globals in different source files.
  * ["static initialization order fiasco"](http://yosefk.com/c++fqa/ctors.html#fqa-10.12)
* As a rule of thumb, struct should be kept to structures where all members are declared public.
* Do not use Braced Initializer Lists to Call a Constructor
* #include as Little as Possible
* Use the “assert” macro from `<cassert>` to it's fullest (assert is good for checking a case during run-time). Use static assert to make assertions at compile time.

```cpp
inline Value *getOperand(unsigned I) {
  assert(I < Operands.size() && "getOperand() out of range!"); // Good, prints message.
  return Operands[I];
}
```

Note: You should never depend on assert to do anything because the code can be compiled with NDEBUG defined and then assert does nothing. Production code is often times compiled with NDEBUG defined to ensure that those assert statements disappear.

* Use #ifdef with platfom dependant code
* Don’t evaluate end() every time through a loop.

```cpp
BasicBlock *BB = ...
for (BasicBlock::iterator I = BB->begin(); I != BB->end(); ++I) { // Bad
  ... use I ...
}
BasicBlock *BB = ...
for (BasicBlock::iterator I = BB->begin(), E = BB->end(); I != E; ++I) { // Good, added E = BB->end()
  ... use I ...
}
```

It may be less efficient than evaluating it at the start of the loop. Also if you write the loop in the second form, it is immediately obvious without even looking at the body of the loop that the container isn’t being modified.

* Avoid #include `<iostream>`, because many common implementations transparently inject a static constructor into every translation unit that includes it.
* Avoid std::endl because most of the time, you probably have no reason to flush the output stream, so it’s better to use a literal '\n'.
* Spaces Before Parentheses in control flow statements, but not in normal function call expressions and function-like macros.

```cpp
if (X) ... // Good, bad is: if(X)
for (I = 0; I != 100; ++I) ... // Good, bad is: for(I = 0; I != 100; ++I) ...
while (condition) ... // Good, bad is: while(condition) ...

somefunc(42); // Good, bad is: somefunc (42);
assert(3 != 4 && "laws of math are failing me"); // Good, bad is: assert (3 != 4 && "laws of math are failing me");

A = foo(42, 92) + bar(X); // Good, bad is: A = foo (42, 92) + bar (X);
```

* Use UTF-8 file encodings.
* Avoid putting project’s header files into the [precompiled header file](http://www.cygnus-software.com/papers/precompiledheaders.html). Put only headers that’ll not change in your precompiled headers – like windows.h, STL headers and header only implementations like rapid json..
* Use LF line endings: Unix-style linebreaks ('\n'), not Windows-style ('\r\n').
* Be careful about your accessors. Always provide the const version, the non-const version is optional. Return by value should be avoided as you will copy the content of your object.

```cpp
inline int count() const { return count_; } // Ok, int is small type
inline MyType getData() { return m_data; } // Bad, m_data is big struct
inline MyType const & MyClass::getMyType() const { return mMyType; } // Ok, used refference
```

* Do place spaces around binary and ternary operators.

```cpp
y = m * x + b; // Good, bad is: y=m*x+b;
f(a, b); // Good, bad is: f(a,b);
c = a | b; // Good, bad is: c = a|b;
return condition ? 1 : 0; // Good, bad is: return condition ? 1:0;
```

* Place spaces around the colon in a range-based for loop.

```cpp
for (auto& plugin : plugins) // Good, bad is: for (auto& plugin: plugins)
```

* Each statement should get it's own line, so do not put multiple statements on one line.

Good:

```cpp
x++;
y++;
if (condition)
    doIt();
```

Bad:

```cpp
x++; y++;
if (condition) doIt();
```

* An else statement should go on the same line as a preceding close brace if one is present, else it should line up with the if statement.

Good:

```cpp
if (condition) {
    ...
} else {
    ...
}
```

Bad:

```cpp
if (condition) {
    ...
}
else {
    ...
}
```

* An else if statement should be written as an if statement when the prior if concludes with a return statement.

Good:

```cpp
if (condition) {
    return someValue;
}
if (condition) {
    return someOtherValue;
}
```

Bad:

```cpp
if (condition) {
    return someValue;
} else if (condition) {
    ...
}
```

* Function definitions: place each brace on it's own line. Other braces: place the open brace on the line preceding the code block; place the close brace on it's own line.

Good:

```cpp
int main()
{
    ...
}

class MyClass {
    ...
};

namespace webcore {
    ...
}

for (int i = 0; i < 10; ++i) {
    ...
}
```

Bad:

```cpp
int main() {
    ...
}

class MyClass
{
    ...
};
```

* One-line control clauses should use braces (simplifies further editing and prevents bugs).

```cpp
if (condition) {
    doIt();
}
```

* Prefer Using Directive (using std::vector;) over Using Declaration (using namespace std;).
* Prefer variable names in function declarations. Remove only meaningless variable names out of function declarations if its really neccesary.

```cpp
void setCount(size_t count); // Good, bad is: void setCount(size_t count);

void doSomething(ScriptExecutionContext* context); // Good, bad is: void doSomething(ScriptExecutionContext* context);
```

* Avoid “using” statements in namespace (or global) scope of header files.
* Singleton pattern

Use a static member function named “instance()” to access the instance of the singleton.

```cpp
class MySingleton {
public:
    static MySingleton& instance();
```

* Use parentheses to group expressions.
* Avoid 64-bit enum values. Not all compilers support them.
enum class Enum2 : __int64 {Val1, Val2, val3}; // Avoid
* The binary operators = (assignment), [] (array subscription), -> (member access), as well as the n-ary () (function call) operator, must always be implemented as member functions, because the syntax of the language requires them to. Other operators can be implemented either as members or as non-members.For all operators where you have to choose to either implement them as a member function or a non-member function, use the following [rules of thumb to decide](http://stackoverflow.com/a/4421729) where possible:
  * If it is a unary operator, implement it as a member function.
  * If a binary operator treats both operands equally (it leaves them unchanged), implement this operator as a non-member function.
  * If a binary operator does not treat both of its operands equally (usually it will change it's left operand), it might be useful to make it a member function of it's left operand’s type, if it has to access the operand's private parts.
Also don't forget about ["self assignment"](http://yosefk.com/c++fqa/assign.html):

```cpp
MyClass& MyClass::operator=(const MyClass& other)  // copy assignment operator
{
    if(this != &other) // <-- self assignment check
    {
        // copy some stuff
    }
    return *this;
}
```

* Don't shadow variables
  * avoid things like this->x = x;
  * don't give variables the same name as functions declared in your class
* Always check whether a preprocessor variable is defined before probing its value

```cpp
#if Foo == 0  // Bad
#if defined(Foo) && (Foo == 0) // Good
```

* Avoid varargs. Especially inline variadic functions. Use containers like `std::initializer_list<T>` instead.

```cpp
template<typename T, typename... Args>
void func(T t, Args... args) // Avoid, its recursive variadic function.
{
    std::cout << t <<std::endl ;
    func(args...) ;
}
```

* Write only one statement per line.
* Always declare a copy constructor and assignment operator
Many classes shouldn't be copied or assigned. If you're writing one of these, the way to enforce your policy is to declare a deleted copy constructor as private and not supply a definition. While you're at it, do the same for the assignment operator used for assignment of objects of the same class:

```cpp
class Foo {
  ...
  private:
    Foo(const Foo& x) = delete;
    Foo& operator=(const Foo& x) = delete;
};
```

Any code that implicitly calls the copy constructor will hit a compile-time error. That way nothing happens in the dark. When a user's code won't compile, they'll see that they were passing by value, when they meant to pass by reference (oops).

* Don't use identifiers that start with an underscore (according to the C++ Standard):
  * Each name that contains a double underscore (__) or begins with an underscore followed by an uppercase letter (2.11) is reserved to the implementation for any use.
  * Each name that begins with an underscore is reserved to the implementation for use as a name in the global namespace.
* Don't write an #include inside an #ifdef if you could instead put it outside.
* Every .cpp source file should have a unique name: Avoid generic names like Module.cpp and instead use PlacesModule.cpp.
* Avoid declaring a class data member with explicit size, in bits (Bit field).

```cpp
struct { // Following struct might have a size of 8 bytes, even though it would fit in 1:
  char ch : 1;
  int i : 1;
};
```

* Prefer [enum classes as type-safe bitmasks](http://blog.bitwigglers.org/using-enum-classes-as-type-safe-bitmasks/), see [example here](https://gist.github.com/derofim/0188769131c62c8aff5e1da5740b3574)
* Never place constants in header files like:
  * const int foo = 12; // Bad, inclues on every cpp file
  * #define foo 12 // Bad, macros

UInstead use "constexpr" or ["extern const"](http://www.cplusplus.com/faq/beginners/multiple-sources/).

## Function overloading

Function overloading should be avoided in most cases.  For example, instead of:

```cpp
// Good:
    const Anim* GetAnimByIndex( int index ) const;
    const Anim* GetAnimByName( const char *name ) const;
    const Anim* GetRandomAnim( float randomDiversity ) const;
// Bad:
    const Anim* GetAnim( int index ) const;
    const Anim* GetAnim( const char *name ) const;
    const Anim* GetAnim( float randomDiversity ) const;
```

Explicitly named functions tend to be less prone to programmer error and inadvertent calls to functions due to wrong data types being passed in as arguments.  Example:

Anim = GetAnim( 0 );

This could be meant as a call to get a random animation, but the compiler would interpret it as a call to get one by index.

## STL inculdes

* Prefer Use C++ includes, not C includes where possible.

```cpp
#include <cstdio> // Instead of #include <stdio.h>
#include <cstring> // Instead of #include <string.h>
```

* Prefer `<library>` to `library.h` for STL and library headers.
* Prefer unique_ptr instead of shared_ptr where possible. Unique pointers are way more lightweight than shared one.
* For COM objects like Direct3D objects, you should use the smartpointer like "Microsoft::WRL::ComPtr" instead of std smartpointers like "std::unique_ptr".
* Use smartpointers judiciously, prefer raw pointers over smartpointers in most cases. Remember that passing variables by reference was enough in most places. Non-library code should, however, generally prefer smart pointers over raw.
* Avoid std::auto_ptr (its copy semantic is screwed).
* Smartpointer overhead:
std::unique_ptr (cannot be copied, can be moved) / std::scoped_ptr (cannot be copied or moved): Has memory overhead only if you provide it with some non-trivial deleter. Has time overhead only during constructor (if it has to copy the provided deleter) and during destructor (to destroy the owned object).
std::shared_ptr (can be copied): Has memory overhead for reference counter, though it is very small. Has time overhead in constructor (to create the reference counter), in destructor (to decrement the reference counter and possibly destroy the object) and in assignment operator (to increment the reference counter).

## See Also

* The  C++ Programming Language, 4th Edition by Bjarne Stroustrup (2013).
* Effective Modern C++ by Scott Meyers (2014).
* Large-Scale C++ Software Design by John Lakos (1996).
* C++  Coding Standards: 101 Rules, Guidelines, and Best Practices by Herb Sutter and Andrei Alexandrescu (2004).
* C++ FQA Lite: [C++ frequently questioned answers](http://yosefk.com/c++fqa/index.html)

## Binary and Source Compatibility

* Definitions:
  * 4.0.0 is a major release, 4.1.0 is a minor release, 4.1.1 is a patch release
  * Backward ? binary compatibility: Code linked to an earlier version of the library keeps working
  * Forward ? binary compatibility: Code linked to a newer version of the library works with an older library
  * Source code compatibility: Code compiles without modification
* Keep backward ? binary compatibility + backward ? source code compatibility in minor releases
* Keep backward and forward binary compatibility + forward and backward source code compatibility in patch releases
  * Don't add/remove any public API (e.g. global functions, public/protected/private methods)
  * Don't reimplement methods (not even inlines, nor protected/private methods)
* Info on binary compatibility: [https://community.kde.org/Policies/Binary_Compatibility_Issues_With_C++](https://community.kde.org/Policies/Binary_Compatibility_Issues_With_C%2B%2B)

## ToDo

Argument naming
const bool mcb_Running or const bool  m_cbRunning
Project types  like UINT32, INT8 e.t.c.
parentheses padding
forward declarations
include guard path
inlining member functions
align variable labels
extern C
remove c_ for const
place boolean "b" before name m_bVar
precompiled headers
VS directory or filters
Method separation in realisation aka:

```cpp
//-----------------------------------------------------------------------
INLINE MouseButton getMouseButton(uint8_t state)
{
  switch ( state )
  {
  case SDL_BUTTON_LMASK: return MouseButton::Left;
  case SDL_BUTTON_RMASK: return MouseButton::Right;
  case SDL_BUTTON_MMASK: return MouseButton::Middle;
  }
  return MouseButton::None;
}
//-----------------------------------------------------------------------
WindowDesc::WindowDesc()
{
  Pos = Point2D(CW_USEDEFAULT, CW_USEDEFAULT);
}
```

## Useful links

* [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
* [LLVM coding standards](http://llvm.org/docs/CodingStandards.html)
* [Chromium’s style guide](http://www.chromium.org/developers/coding-style)
* [Mozilla’s style guide](https://developer.mozilla.org/en-US/docs/Developer_Guide/Coding_Style)
* [WebKit’s style guide](http://www.webkit.org/coding/coding-style.html)
* [Qt Coding Style](http://wiki.qt.io/Qt_Coding_Style)
* [Qt - API Design Principles](https://wiki.qt.io/API_Design_Principles)
* [Unreal Engine Coding Standard](https://docs.unrealengine.com/latest/INT/Programming/Development/CodingStandard/)
* [C++ Best Practices](http://codergears.com/QACenter/index.php?qa=questions)
* [Blender Coding Style](http://wiki.blender.org/index.php/Dev:Doc/Code_Style)
* [Blink Coding Style Guidelines](http://www.chromium.org/blink/coding-style)
* [Inkscape Coding Style](https://inkscape.org/en/develop/coding-style/)
* [CppCoreGuidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md)
* [klayge](http://www.klayge.org/wiki/index.php/C%2B%2B_style_guide)
