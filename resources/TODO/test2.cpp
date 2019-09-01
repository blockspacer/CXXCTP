#include <type_traits>

#include <iostream>
using namespace std;

#define GEN_ATTR() __attribute__
#define HISSS() ((annotate("{gen};{codegen};int dgdfg = 456566;")))
#define GEN_TMP_NAME() __GENERATED_NAME ##__LINE__ //##__FILE__  // helper macro

//class GEN_ATTR() HISSS() GEN_TMP_NAME() {};

class GEN_ATTR() HISSS() GEN_TMP_NAME() {};

// after

class __attribute__((annotate("{gen};{codegen};int dgdfg = 456566;"))) CLassNameHere1 {};

// https://meetingcpp.com/mcpp/slides/2018/Reflection2.pdf
// https://github.com/Leandros/metareflect/blob/0208fdd4fc0ea1081ae2ff4c3bfce161305a7423/tooling/reflect.cpp#L36
// https://github.com/Leandros/metareflect/blob/0208fdd4fc0ea1081ae2ff4c3bfce161305a7423/tooling/reflectedclass.cpp#L158
/*#define CLASS(...) class __attribute__((annotate("bind_gen;" #__VA_ARGS__)))

CLASS(Serialized) User
{

};

CLASS(Serialized2) User2
{

};
*/

class
  __attribute__((annotate("{gen};{codegen};int dgdfg = 456566;")))
  CLassNameHere2 {};

#define $gen(CLASS_NAME, ...) \
  __attribute__((annotate("{gen};{codegen};" #__VA_ARGS__))) CLASS_NAME

class $gen(SomeClassName,
  int i = 565444;
  printf("i = %i", i);
  std::cout << std::endl;
) {};

class __attribute__((annotate("{gen};{funccall};make_interface"))) SomeInterfaceName2
{
  int foo1();
  virtual void foobar1(int& arg1) = 0;
  int m_bar1;
};

#define $interface \
  __attribute__((annotate("{gen};{funccall};make_interface")))

#define $removefuncbody \
  __attribute__((annotate("{gen};{funccall};make_removefuncbody")))

//#define $interface(CLASS_NAME) \
//  __attribute__((annotate("{gen};{funccall};make_interface"))) CLASS_NAME

class $interface $removefuncbody SomeInterfaceName {
  int    f   (   )   {     // {}
    int i = 6;
    {
      // {
      // }
    }
    return i;
  };
  int foo();

  int foo2() const;
  virtual void foobar(int& arg1) = 0;
  int m_bar;
  int m_bar2 = 2;
};

int i = 3355;

/*#define CODEGEN(...) class __attribute__((annotate("bind_gen;" #__VA_ARGS__)))
CODEGEN(
  int
  j
  asdasd 213321 asdasd;
) GENERATED_NAME_HERE {};*/

//#define GEN_EXPORT __attribute__( ( annotate( "gen" ) ) )
/*enum class
__attribute__((annotate("reflect-class;" Class)))
Color { R, G, B };*/

//__func1__();

//__func2__();

#if 0
enum class GEN_EXPORT Color { R, G, B };

// Will export the public interface only
class GEN_EXPORT Test { /* ... */ };
#endif // 0

/*void doSomething(int a) {

}

void doSomething() {

}*/

//#doSomething(1);
// #gen(1);

class Base {
public:

    // user wants to override this in
    // the derived class
    virtual void func(int a)
    {
        /*__PRETTY_FUNCTION__;
        [](){

        };*/

        cout << "I am in base" << endl;
    }
};

//#gen(as asd)
class
//__attribute__((annotate("some_important_string")))
derived : public Base {
public:

    // did a silly mistake by putting
    // an argument "int a"
    /*GEN_EXPORT*/ void func(int a) override
    {
        cout << "I am in derived class" << endl;
        //#gen(1)
    }
};

/*{
  auto i GEN_EXPORT = [](){

  };
}*/

template<typename T> 
typename std::enable_if<std::is_integral<T>::value>::type f(T& value) {
  value += 1;
  //int i GEN_EXPORT;

  /*{
    auto i GEN_EXPORT = [](){

    };
  }*/
  //#gen(3454);
  //__attribute__((annotate("some_important_string")))
}
