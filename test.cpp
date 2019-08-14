
#include <iostream>
#include <string>
#include <thread>
#include <deque>

#include "lazy_closure.h"

using namespace std;

// 测试函数1
void function1(int){
    printf("function1\n");
}

// 测试函数2
void* function2(int,double){
    printf("function2\n");
    return NULL;
}

// 测试函数3
std::string function3(int,double, std::string){
    printf("function3\n");
    return "";
}

// 测试函数4
int function4(int,double, std::string,std::string){
    printf("function4\n");
    return 0;
}

class Test{
public:
    // 测试函数5
    int run(int,double,std::string){
        printf("Test::run\n");
        return 0;
    }
};



int main()
{
    int v1 = 0;
    double v2 = 0;
    const char* v3 = "";
    std::string v4 = "";
    Test test;

    // 创建闭包
    lazy::Closure f1,f2,f3,f4,f5;
    f1 = lazy::CreateClosure(lazy::Bind(function1,v1));
    f2 = lazy::CreateClosure(lazy::Bind(function2,v1,v2));
    f3 = lazy::CreateClosure(lazy::Bind(function3,v1,v2,v3));
    f4 = lazy::CreateClosure(lazy::Bind(function4,v1,v2,v3,v4));
    f5 = lazy::CreateClosure(lazy::Bind(&Test::run,&test,v1,v2,v3));

    // 闭包执行
    f1();
    f2();
    f3();
    f4();
    f5();

    return 0;
}
