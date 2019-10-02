# TODO
- [ ] No predefined set of code transformations, move exaples to separate repos
  - https://stackoverflow.com/questions/24062989/clang-fails-replacing-a-statement-if-it-contains-a-macro
- [ ] Codstyle rules
  - https://github.com/gmarpons/Crisp/blob/master/prolog/Rules/SomeHICPPrules.pl
- [ ] Http routes
  - https://github.com/leechiryo/mvcpp/blob/e98237bdd8d01dc8a78537799a17c77720b37900/tools/astparser/main.cpp
- [ ] String to/from hash (to use in switch e.t.c.)
  - https://stackoverflow.com/questions/48896142/is-it-possible-to-get-hash-values-as-compile-time-constants
- [ ] .template
  - https://github.com/mlomb/MetaCPP/blob/8eddde5e1bf4809ad70a68a385b9cbcc8e237370/MetaCPP-CLI/templates/source.template
- [ ] $gen(import) for compile-time testing
- [ ] compile_commands.json
  - https://github.com/Leandros/metareflect/blob/0208fdd4fc0ea1081ae2ff4c3bfce161305a7423/README.md#run-the-metareflect-tool
- [ ] ability to embed rules for speed (run without cling)
- [ ] base64 Embed Resources Into Executables
  + https://github.com/caiorss/C-Cpp-Notes/blob/master/resources-executable.org#base-64-implementations
- [ ] C++ class state serialization (byte serialization)
  + http://ithare.com/ultra-fast-serialization-of-c-objects/
  + https://rubentorresbonet.wordpress.com/2014/08/25/an-overview-of-data-serialization-techniques-in-c/
  + https://accu.org/index.php/journals/2317
  + https://arxiv.org/pdf/1811.04556.pdf
  + https://stackoverflow.com/questions/46625279/is-it-safe-to-serialize-pod-data-by-casting-directly-to-char-array
  + Modern C++ Programming Cookbook 
    + https://books.google.ru/books?id=rHc5DwAAQBAJ&pg=PA301&lpg=PA301&dq=reinterpret_cast+const+char+serialize+C%2B%2B+POD&source=bl&ots=9DUR3KDM16&sig=ACfU3U3BoCEa14SjsJEdsQYymyqnY25kbQ&hl=ru&sa=X&ved=2ahUKEwiNpdGCkrDkAhWjs4sKHYk7BRgQ6AEwAnoECAkQAQ#v=onepage&q=reinterpret_cast%20const%20char%20serialize%20C%2B%2B%20POD&f=false
- [ ] error reporting & unit tests
  + https://probablydance.com/2015/12/19/quickly-loading-things-from-disk/
  + https://github.com/voidah/archive/blob/master/archive.h
  + https://www.reddit.com/r/cpp/comments/8dpcjh/singleheader_c14_binary_serialization/
- [ ] RPC
  + http://www.crazygaze.com/blog/2016/06/06/modern-c-lightweight-binary-rpc-framework-without-code-generation/
  + https://www.youtube.com/watch?v=nb1fO4H9Q8w
- [ ] recursive refletor / serializer
  - [ ] Prefer comparison using epsilon for floating point types like: https://gist.github.com/derofim/df604f2bf65a506223464e3ffd96a78a#comparison-and-boolean-check

- [ ] enum classes as type-safe bitmasks
  + https://gist.github.com/derofim/0188769131c62c8aff5e1da5740b3574

- [ ] flag_set: Type-safe, hard to misuse bitmask
  + https://foonathan.net/blog/2017/03/16/implementation-challenge-bitmask.html
  + operator- Remove an element https://dxr.mozilla.org/mozilla-central/source/mfbt/EnumSet.h

- [ ] DISALLOW_COPY_AND_ASSIGN + check that we should delete the methods in the public: section.
  + https://chromium.googlesource.com/chromium/src/base/+/master/macros.h#23
  + https://github.com/chromium/chromium/blob/b9982d8b12286491af4dd8eef12e77b3af9a61d7/ui/views/examples/scroll_view_example.cc#L69
  + https://stackoverflow.com/a/20026657
  + https://github.com/google/styleguide/issues/255

- [ ] enum parser https://github.com/goto40/rpp/blob/ec8a4c4a3ac32dccee8c4e8ba97be8c2ba1c8f88/src/parser/enum_parser.cpp

- [ ] .tmpl 
  - https://github.com/feed57005/librfl/blob/master/example/generator/example/templates/package_header.tmpl

- [ ] $_class(SomeVisitor, Visitor<bool, A, B, C>, Interface)
{
public:
 void TestMethod1();
 std::string TestMethod2(int param) const;
};

- [ ] disable make_pure_virtual for some methods via annotation

- [ ] GUID generator for class/e.t.c.

- [ ] add_custom_command 
  - https://github.com/flexferrum/autoprogrammer/blob/1d246b809f916b0aa06388b985b17cc6f6b9e842/test/pimpl/CMakeLists.txt#L17

- [ ] getCommentForDecl 
  - https://github.com/mogemimi/negicco/blob/da829f8c76fff20692b4d5aa6004e12333fb7bdb/05-enum-classes/main.cpp#L106

- [ ] gen-only comments
  - https://github.com/mogemimi/negicco/blob/da829f8c76fff20692b4d5aa6004e12333fb7bdb/03-comments/main.cpp

- [ ] protoc 
  - https://github.com/feed57005/librfl/blob/master/rfl/CMakeLists.txt#L18

- [ ] dynamically calling functions by name with the runtime library 
  - https://www.reddit.com/r/gamedev/comments/3lh0ba/using_clang_to_generate_c_reflection_data/

- [ ] separate hpp & cpp: move decl/impl to file/cling var/tpl

- [ ] editor support? #include generated files?

- [ ] NamedType 
  - https://github.com/joboccara/NamedType

- [ ] magic_get 
  - https://github.com/apolukhin/magic_get

- [ ] getset
  + https://habr.com/ru/post/459212/
  + https://habr.com/ru/post/121799/
  + https://github.com/tower120/cpp_property

- [ ] Property (state, descr, man/max/allowed/getset/serialize/onbeforechange/onafterchange/addobserver, hierarchy/PropertyBrowser) & SetPropertyByName()
  + https://github.com/qtinuum/QtnProperty#overview
  + https://woboq.com/blog/reflection-in-cpp-and-qt-moc.html
  + https://github.com/robertknight/Qt-Inspector
  + https://stackoverflow.com/a/49230152

- [ ] notifier

- [ ] `has` for enum 
  - https://github.com/Manu343726/siplasplas/blob/master/examples/reflection/static/enum.cpp#L17

- [ ] Determine the layout of C and C++ types, including their size, and the size, offset, and padding of each field in the type. 
  - https://github.com/joshpeterson/layout

- [ ] Templates support

- [ ] Macro support

- [ ] Remove macro from generated src

- [ ] Reactive CPP (C++React / RxCpp)
  + http://reactivex.io/intro.html
  + https://github.com/schlangster/cpp.react

- [ ] concurrency / loop vectorizin

- [ ] loop for recursion

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
