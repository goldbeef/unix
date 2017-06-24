/*************************************************************************
    > File Name: class.cpp
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年06月24日 星期六 16时44分05秒
 ************************************************************************/

#include <iostream>
#include "all_def.h"
using namespace std;

class TestClass
{
    static int val1;
    static int val2;
};

int TestClass::val1 = 0;
int TestClass::val2 = 0;


int main()
{
    printf("sizeof(TestClass) = %zu\n", sizeof(TestClass));
    return 0;
}

