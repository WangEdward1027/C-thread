//线程的创建4:传递函数对象
//get_id():获取线程id

#include <iostream> 
#include <thread>
using std::cout;
using std::endl;
using std::thread;

//函数对象:重载了函数调用运算符operator()的类的对象
class Example
{
public:
    void operator()(int x)
    {
        cout << "child thread id === " << std::this_thread::get_id() << endl;
        cout << "void threadFunc(int x)" << endl;
        cout << "x = " << x << endl;
    }
};

/* void threadFunc(int x){ */
/*     cout << "child thread id === " << std::this_thread::get_id() << endl; */
/*     cout << "void threadFunc(int x)" << endl; */
/*     cout << "x = " << x << endl; */
/* } */

int main()
{
    cout << "main thread id = " << std::this_thread::get_id() << endl;
    
    Example ex;
    thread th(ex, 4); //th是子线程
    
    cout << "child thread id = " << th.get_id() << endl;
    th.join(); //主线程等待子线程的退出
    
    return 0;
}
