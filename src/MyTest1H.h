#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <streambuf>
#include <iostream>

int MyPrint1_i = 0;

/*namespace MyTest1
{*/

//extern float MyTest_1();

//extern c void MyTest1();

void MyTest1H() {
    printf("MyTest1H %d\n", MyPrint1_i);
}

class Foo {
public:
    Foo() : bar(MyPrint1_i) {
                printf("Foo() bar %d\n", bar);
            };

    int bar;
};

/*}*/
