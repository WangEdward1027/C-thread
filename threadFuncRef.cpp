//线程的创建3:传递函数引用
//get_id():获取线程id

#include <iostream> 
#include <thread>
using std::cout;
using std::endl;
using std::thread;

void threadFunc(int x){
    cout << "child thread id === " << std::this_thread::get_id() << endl;
    cout << "void threadFunc(int x)" << endl;
    cout << "x = " << x << endl;
}

int main()
{
    cout << "main thread id = " << std::this_thread::get_id() << endl;
    
    typedef void (&pFunc)(int); //pFunc是函数引用
    pFunc f = threadFunc;
    thread th(f, 3); //th是子线程
    
    cout << "child thread id = " << th.get_id() << endl;
    th.join(); //主线程等待子线程的退出
    
    return 0;
}
