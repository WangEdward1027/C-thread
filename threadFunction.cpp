//线程的创建6:传递function对象

#include <iostream> 
#include <thread>
#include <functional>
using std::cout;
using std::endl;
using std::thread;
using std::function;
using std::bind;

//1.用function接收lambda表达式
void test1()
{
    cout << "main thread id = " << std::this_thread::get_id() << endl;

    function<void(int)> f = [](int x){
        cout << "child thread id === " << std::this_thread::get_id() << endl;
        cout << "void threadFunc(int x)" << endl;
        cout << "x = " << x << endl;
    };

    thread th(f, 6); //创建子线程

    cout << "child thread id = " << th.get_id() << endl;
    th.join(); //主线程等待子线程的退出
}


void threadFunc(int x){
    cout << "child thread id === " << std::this_thread::get_id() << endl;
    cout << "void threadFunc(int x)" << endl;
    cout << "x = " << x << endl << endl;
}

//2.用function接收bind
void test2()
{
    cout << "main thread id = " << std::this_thread::get_id() << endl;

    function<void()> f = bind(threadFunc, 7);
    thread th(f); //创建子线程
    
    thread th2(bind(threadFunc, 8));

    cout << "child thread id = " << th.get_id() << endl << endl;
    
    th.join(); 
    th2.join(); 
}


int main()
{
    /* test1(); */
    test2();
    return 0;
}
